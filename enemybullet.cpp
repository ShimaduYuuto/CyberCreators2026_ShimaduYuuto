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

const std::string CEnemyBullet::FILEPATH = "data\\MODEL\\enemybullet.x";

//============================
//コンストラクタ
//============================
CEnemyBullet::CEnemyBullet(int nPriority) : CObjectX(nPriority),
	m_Move(),
	m_fSizeRate(0.0f),
	m_bReflection(false)
{
	m_fSizeRate = 1.0f;

	//ゲームシーンなら判定
	if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
	{
		//ゲームシーンの取得
		CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

		//マネージャーに登録
		pGame->GetEnemyBulletManager()->Regist(this);
	}

	//当たり判定の生成
	if (m_Collision == nullptr)
	{
		m_Collision = CCollision::Create(COLLISION_RADIUS, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
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
		CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

		//マネージャーから削除
		pGame->GetEnemyBulletManager()->Erase(this);
	}

	//当たり判定の消去
	if (m_Collision != nullptr)
	{
		m_Collision->Uninit();
		m_Collision = nullptr;
	}
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
}

//============================
//更新
//============================
void CEnemyBullet::Update()
{
	//移動量の加算
	D3DXVECTOR3 Pos = GetPos();
	Pos += m_Move;
	SetPos(Pos);

	//スケールの設定
	SetScale({ m_fSizeRate, m_fSizeRate , m_fSizeRate });

	//当たり判定の更新
	if (m_Collision != nullptr)
	{
		m_Collision->SetRadius(m_fSizeRate * COLLISION_RADIUS);
		m_Collision->Update(Pos);
	}

	//ゲームシーンの取得
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

	//変数宣言
	D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();	//プレイヤーの位置

	//距離を計算
	float fXZ = sqrtf((m_Collision->GetPos().x - PlayerPos.x) * (m_Collision->GetPos().x - PlayerPos.x) + (m_Collision->GetPos().z - PlayerPos.z) * (m_Collision->GetPos().z - PlayerPos.z)); //距離を算出する
	float fXY = sqrtf((m_Collision->GetPos().x - PlayerPos.x) * (m_Collision->GetPos().x - PlayerPos.x) + (m_Collision->GetPos().y - PlayerPos.y) * (m_Collision->GetPos().y - PlayerPos.y)); //距離を算出する
	float fLength = sqrtf(fXZ * fXZ + fXY * fXY);	//距離を算出

	//攻撃の範囲内なら
	if (fLength < m_Collision->GetRadius() + 20.0f)
	{
		//プレイヤーにダメージを与える
		pGame->GetGamePlayer()->SetDamage(1);
		Uninit();
	}

	//ゲームオブジェクトの共通処理更新
	CObject::Update();
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
CEnemyBullet* CEnemyBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	//種類に応じて動的確保
	CEnemyBullet* pEnemyBullet = NULL;

	//クリエイトの処理
	pEnemyBullet = new CEnemyBullet;

	//初期化
	pEnemyBullet->Init();

	//パラメータの設定
	pEnemyBullet->SetPos(pos);		//位置
	pEnemyBullet->m_Move = move;	//移動量

	//設定した情報を返す
	return pEnemyBullet;
}

//============================
//反射処理
//============================
void CEnemyBullet::Reflection()
{
	//反射していないなら反射
	if (!m_bReflection)
	{
		//移動量を反転
		m_bReflection = true;

		m_Move *= -1.0f;
	}
}