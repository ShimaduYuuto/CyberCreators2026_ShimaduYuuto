//======================================
//
//	エネミースポーン処理[spawn_enemy.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "spawn_enemy.h"
#include "battleareamanager.h"

//============================
//コンストラクタ
//============================
CSpawn_Enemy::CSpawn_Enemy(int nPriority) : CObject(nPriority),
	m_nCount(0),				//カウント
	m_pPaticleManager(nullptr),	//パーティクルの制御をするポインタ
	m_EnemyType()				//出現させる敵の種類
{
	//登録する敵の数を増やす
	if (CBattleAreaManager::GetInstance()->GetCurrentBattleArea() != nullptr)
	{
		CBattleAreaManager::GetInstance()->GetCurrentBattleArea()->AddEnemyNum();
	}
}

//============================
//デストラクタ
//============================
CSpawn_Enemy::~CSpawn_Enemy()
{
	//パーティクルマネージャーの破棄
	if (m_pPaticleManager != nullptr)
	{
		delete m_pPaticleManager;
		m_pPaticleManager = nullptr;
	}
}

//============================
//初期化
//============================
HRESULT CSpawn_Enemy::Init()
{
	//パーティクルの生成
	m_pPaticleManager = CParticle_Spawn::Create(GetPos());

	return S_OK;
}

//============================
//終了
//============================
void CSpawn_Enemy::Uninit()
{
	CObject::Uninit();
}

//============================
//更新
//============================
void CSpawn_Enemy::Update()
{
	//パーティクルマネージャーの更新
	m_pPaticleManager->Update();

	//カウントアップ
	m_nCount++;

	//一定時間で敵を生成
	if (m_nCount > SPAWN_TIME)
	{
		CEnemy::Create(GetPos(), m_EnemyType);
		Uninit();
	}
}

//============================
//生成
//============================
CSpawn_Enemy* CSpawn_Enemy::Create(D3DXVECTOR3 pos, CEnemy::ENEMYTYPE type)
{
	//ポインタ用の変数
	CSpawn_Enemy* pObject;

	//メモリの確保
	pObject = new CSpawn_Enemy();

	//パラメータの設定
	pObject->SetPos(pos);		//位置の設定
	pObject->m_EnemyType = type;//種類

	//初期化
	pObject->Init();

	return pObject;
}