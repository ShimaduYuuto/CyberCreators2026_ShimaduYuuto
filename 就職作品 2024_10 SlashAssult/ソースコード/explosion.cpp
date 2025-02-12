//======================================
//
//	爆発樽の処理[explosion.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "explosion.h"
#include "game.h"
#include "manager.h"

//定数
const std::string CExplosion::FILEPATH = "data\\TEXTURE\\SmashMesh000.png";

//============================
//コンストラクタ
//============================
CExplosion::CExplosion(int nPriority) : CObjectDome(nPriority),
	m_fLife(LIFE),
	m_pCollision(nullptr),
	m_fSizeRate(SIZE_STRAT_RATE)
{
	//ゲームシーンの取得
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//マネージャーに登録
	pGame->GetExplosionManager()->Regist(this);

	//ゲームタグを設定
	SetTag(CObject::TAG_GAME);

	//カメラを揺らす
	CManager::GetInstance()->GetCamera()->SetShake(30, 20);	//ヒット時カメラを揺らす
}

//============================
//デストラクタ
//============================
CExplosion::~CExplosion()
{
	//ゲームシーンの取得
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

	//マネージャーから削除
	pGame->GetExplosionManager()->Erase(this);
}

//============================
//初期化
//============================
HRESULT CExplosion::Init()
{
	//初期化
	CObjectDome::Init();

	if (m_pCollision == nullptr)
	{
		m_pCollision = CCollision::Create(SIZE_RADIUS, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	
	//SEの設定
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_EXPLOSION);

	return S_OK;
}

//============================
//終了処理
//============================
void CExplosion::Uninit()
{
	//当たり判定の破棄
	if (m_pCollision != nullptr)
	{
		m_pCollision->Uninit();
		m_pCollision = nullptr;
	}

	//終了処理
	CObjectDome::Uninit();
}

//============================
//更新
//============================
void CExplosion::Update()
{
	//サイズ倍率の更新
	UpdateSizeRate();

	//倍率の設定
	SetRate(m_fSizeRate);

	//寿命の更新
	m_fLife--;

	if (m_fLife <= 0.0f)
	{
		Uninit();
		return;
	}

	//ゲームオブジェクトの共通処理更新
	CObjectDome::Update();

	//当たり判定の更新
	m_pCollision->Update(GetPos());
}

//============================
//サイズ倍率の更新
//============================
void CExplosion::UpdateSizeRate()
{
	//倍率を増やすか
	if (IsIncreaseSizeRate())
	{
		//倍率を増加
		m_fSizeRate += INCREASE_VALUE;

		//最大倍率時のみ当たり判定を行う
		if (m_fSizeRate >= MAX_SIZE_VALUE)
		{
			//最大サイズに補正
			m_fSizeRate = MAX_SIZE_VALUE;

			//当たり判定の処理
			CollisionProcess();
		}
	}
	else if (IsDecreaseSizeRate())
	{
		//倍率を減少
		m_fSizeRate -= DECREASE_VALUE;

		//最小値を下回ったら補正
		if (m_fSizeRate < MIN_SIZE_VALUE)
		{
			//最小サイズに補正
			m_fSizeRate = MIN_SIZE_VALUE;
		}
	}
}

//============================
//サイズ倍率を増やすか
//============================
bool CExplosion::IsIncreaseSizeRate()
{
	//判定
	if (m_fLife <= INCREASE_RATE_LIFE) return false;	//増やす生存時間外なら抜ける
	if (m_fSizeRate >= MAX_SIZE_VALUE) return false;	//最大倍率なら抜ける
	
	return true;
}

//============================
//サイズ倍率を減らすか
//============================
bool CExplosion::IsDecreaseSizeRate()
{
	//判定
	if (m_fLife >= DECREASE_RATE_LIFE)return false;	//減らす生存時間外なら抜ける
	if (m_fSizeRate <= MIN_SIZE_VALUE) return false;//最小倍率なら抜ける

	return true;
}

//============================
//当たり判定の処理
//============================
void CExplosion::CollisionProcess()
{
	//ゲームシーンの取得
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//判定の生成
	D3DXVECTOR3 ExplosionPos = GetPos();

	//敵の周回
	for (auto& iter : pGame->GetEnemyManager()->GetList())
	{
		//敵の位置を取得
		D3DXVECTOR3 EnemyLength = iter->GetCollision()->GetPos() - ExplosionPos;

		float fXZ = sqrtf(EnemyLength.x * EnemyLength.x + EnemyLength.z * EnemyLength.z); //XZ距離を算出する
		float fXY = sqrtf(EnemyLength.x * EnemyLength.x + EnemyLength.y * EnemyLength.y); //XY距離を算出する
		float fLength = sqrtf(fXZ * fXZ + fXY * fXY);	//距離を算出

		//敵の判定内なら
		if (fLength < iter->GetCollision()->GetRadius() + m_pCollision->GetRadius())
		{
			//角度を算出
			float fAngleXZ = atan2f(EnemyLength.x, EnemyLength.z);
			float fAngleXY = atan2f(EnemyLength.x, EnemyLength.y);

			//吹き飛ばしながらダメージを与える
			iter->SetBlowDamage(DAMAGE_VALUE, fAngleXZ, BLOW_VALUE);
		}
	}
}

//============================
//描画
//============================
void CExplosion::Draw()
{
	//ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得
	
	//カリング方法を変更
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	//オブジェクトの描画
	CObjectDome::Draw(FILEPATH.c_str());

	//カリング方法を変更
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//============================
//クリエイト
//============================
CExplosion* CExplosion::Create(D3DXVECTOR3 pos)
{
	//種類に応じて動的確保
	CExplosion* pExplosion = nullptr;

	//クリエイトの処理
	pExplosion = new CExplosion;

	//パラメータの設定
	pExplosion->SetPos(pos);			//位置
	pExplosion->SetRadius(SIZE_RADIUS);	//半径
	pExplosion->SetRate(pExplosion->m_fSizeRate);

	//初期化
	pExplosion->Init();

	//設定した情報を返す
	return pExplosion;
}