//======================================
//
//	弾の処理[enemybullet.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "enemybullet.h"
#include "manager.h"
#include "game.h"
#include "character.h"
#include "battleareamanager.h"
#include "state_bullet_normal.h"
#include "state_bullet_reflection.h"

const std::string CEnemyBullet::FILEPATH = "data\\MODEL\\enemybullet002.x";

//============================
//コンストラクタ
//============================
CEnemyBullet::CEnemyBullet(int nPriority) : CObjectX(nPriority),
	m_Move(),					//移動量
	m_fSizeRate(1.0f),			//サイズ倍率
	m_bReflection(false),		//反射判定
	m_bShooting(false),			//撃たれたかの判定
	m_pParentAction(nullptr),	//親のアクション
	m_pParentEnemy(nullptr),	//親の敵
	m_pState(nullptr)			//状態
{
	//ゲームシーンなら判定
	if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
	{
		//ゲームシーンの取得
		CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

		//マネージャーに登録
		pGame->GetEnemyBulletManager()->Regist(this);
	}

	//当たり判定の生成
	if (m_Collision == nullptr)
	{
		m_Collision = CCollision::Create(COLLISION_RADIUS, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	//状態の初期化
	m_pState = new CState_Bullet_Normal(this);

	//ゲームタグを設定
	SetTag(CObject::TAG_GAME);
}

//============================
//デストラクタ
//============================
CEnemyBullet::~CEnemyBullet()
{
	//ゲームシーンなら判定
	if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
	{
		//ゲームシーンの取得
		CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

		//マネージャーから削除
		pGame->GetEnemyBulletManager()->Erase(this);
	}

	//当たり判定の消去
	if (m_Collision != nullptr)
	{
		m_Collision->Uninit();
		m_Collision = nullptr;
	}

	//親に消えたことを伝える
	if (m_pParentAction != nullptr)
	{
		m_pParentAction->Erase(this);
		m_pParentAction = nullptr;
	}

	//状態の削除
	SafeDelete(m_pState);
}

//============================
//初期化
//============================
HRESULT CEnemyBullet::Init()
{
	//初期化
	CObjectX::Init();

	return S_OK;
}

//============================
//終了処理
//============================
void CEnemyBullet::Uninit()
{
	//初期化
	CObjectX::Uninit();

	//親に消えたことを伝える
	if (m_pParentAction != nullptr)
	{
		m_pParentAction->Erase(this);
		m_pParentAction = nullptr;
	}
}

//============================
//更新
//============================
void CEnemyBullet::Update()
{
	//位置の更新
	UpdatePos();

	//スケールの設定
	SetScale({ m_fSizeRate, m_fSizeRate , m_fSizeRate });

	//当たり判定の更新
	UpdateCollision();

	//撃たれていないなら抜ける
	if (!m_bShooting)
	{
		return;
	}

	//状態に応じて処理を変更
	if (m_pState != nullptr)
	{
		m_pState->CheckCollision(this);
	}

	//ヒット確認
	if (IsHitWall())
	{
		//ヒット時の処理
		HitProcess();
	}
}

//============================
//位置の更新
//============================
void CEnemyBullet::UpdatePos()
{
	//移動量の加算
	D3DXVECTOR3 Pos = GetPos();
	Pos += m_Move;
	SetPos(Pos);
}

//============================
//当たり判定の更新
//============================
void CEnemyBullet::UpdateCollision()
{
	//nullチェック
	if (m_Collision != nullptr)
	{
		m_Collision->SetRadius(m_fSizeRate * COLLISION_RADIUS);	//半径を設定
		m_Collision->Update(GetPos());							//位置を更新
	}
}

//============================
//壁に当たったか
//============================
bool CEnemyBullet::IsHitWall()
{
	return CBattleAreaManager::GetInstance()->GetCurrentBattleArea()->GetWall()->
		GetHit(m_Collision->GetPos(), m_Collision->GetRadius());
}

//============================
//ヒット時の処理
//============================
void CEnemyBullet::HitProcess()
{
	//カメラの処理
	CManager::GetInstance()->GetCamera()->SetShake(CAMERA_SHAKE_FRAME, CAMERA_SHAKE_VALUE);	//ヒット時カメラを揺らす

	//サウンド処理
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_BULLETHIT);

	//終了処理
	Uninit();
}

//============================
//描画
//============================
void CEnemyBullet::Draw()
{
	CObjectX::Draw(FILEPATH.c_str());
}

//============================
//クリエイト
//============================
CEnemyBullet* CEnemyBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, CEnemyBehavior_ChargeShot* action, CEnemy* enemy)
{
	//種類に応じて動的確保
	CEnemyBullet* pEnemyBullet = NULL;

	//クリエイトの処理
	pEnemyBullet = new CEnemyBullet;

	//初期化
	pEnemyBullet->Init();

	//パラメータの設定
	pEnemyBullet->SetPos(pos);				//位置
	pEnemyBullet->m_Move = move;			//移動量
	pEnemyBullet->m_pParentAction = action;	//親のアクション
	pEnemyBullet->m_pParentEnemy = enemy;	//親の敵

	//設定した情報を返す
	return pEnemyBullet;
}

//============================
//反射処理
//============================
void CEnemyBullet::Reflection(float angle)
{
	//反射していないなら反射
	if (!m_bReflection)
	{
		//移動量を反転
		m_bReflection = true;
		SafeDelete(m_pState);
		m_pState = new CState_Bullet_Reflection(this);

		//反射角度計算用の変数
		float fPlayerRot = angle;
		float fRot = atan2f(m_pParentEnemy->GetPos().x - GetPos().x, m_pParentEnemy->GetPos().z - GetPos().z);
		float fMin = fPlayerRot - D3DX_PI * 0.5f;
		float fMax = fPlayerRot + D3DX_PI * 0.5f;

		//後ろからの攻撃なら通す
		if (fRot > fMin && fRot < fMax)
		{
			m_Move *= -1.0f;
		}
		else
		{
			m_Move = D3DXVECTOR3(sinf(angle + D3DX_PI) * REFLECTION_SPEED, 0.0f, cosf(angle + D3DX_PI) * REFLECTION_SPEED);
		}
	}
}