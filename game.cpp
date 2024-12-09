//======================================
//
//	ゲームの処理[game.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "game.h"
#include "manager.h"
#include "object2D.h"
#include "player.h"
#include "enemy.h"
#include "explodingbarrel.h"
#include "objectdome.h"
#include "spawn_enemy.h"
#include "sky.h"
#include "battleareamanager.h"
#include "model.h"

//============================
//ゲームのコンストラクタ
//============================
CGame::CGame() :
	m_pPlayer(nullptr),
	m_pField(nullptr),
	m_pTime(nullptr),
	m_pEnemyManager(nullptr),
	m_pLockon(nullptr),
	m_pGimmickManager(nullptr),
	m_pExplosionManager(nullptr),
	m_bClear(false),
	m_bDirectioning(false)
{
	
}

//============================
//ゲームのデストラクタ
//============================
CGame::~CGame()
{
	//フォグの設定
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
}

//============================
//ゲームの初期化
//============================
HRESULT CGame::Init()
{
	//プレイヤーの生成
	if (m_pPlayer == nullptr)
	{
		m_pPlayer = CPlayer::Create();
	}

	//fieldの生成
	if (m_pField == nullptr)
	{
		m_pField = CField::Create({ 0.0f, 0.0f, 0.0f });
	}

	//タイムの生成
	if (m_pTime == nullptr)
	{
		m_pTime = new CTime;
	}

	//エネミーマネージャーの生成
	if (m_pEnemyManager == nullptr)
	{
		m_pEnemyManager = new CEnemyManager;
	}

	//ギミックマネージャーの生成
	if (m_pGimmickManager == nullptr)
	{
		m_pGimmickManager = new CGimmickManager;
	}

	//爆発マネージャーの生成
	if (m_pExplosionManager == nullptr)
	{
		m_pExplosionManager = new CExplosionManager;
	}

	//エネミー弾マネージャーの生成
	if (m_pEnemyBulletManager == nullptr)
	{
		m_pEnemyBulletManager = new CEnemyBulletManager;
	}

	//結界マネージャーの生成
	if (m_pBarrierManager == nullptr)
	{
		m_pBarrierManager = new CBarrierManager;
		m_pBarrierManager->Init();
	}

	//バトルエリアの初期化
	CBattleAreaManager::GetInstance()->Init();

	//CExplodingBarrel::Create({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });
	CSky::Create();
	ModelLoad();

	//フォグの設定
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);					//有効
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP);		//フォグモードの設定
	pDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.1f));	//色の設定
	float m_fFogDensity = 0.0005f;
	pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&m_fFogDensity));
	
	return S_OK;
}

//============================
//ゲームの終了処理
//============================
void CGame::Uninit()
{
	//メモリの破棄
	if (m_pPlayer != nullptr)
	{
		m_pPlayer = nullptr;
	}

	//メモリの破棄
	if (m_pField != nullptr)
	{
		m_pField = nullptr;
	}

	//メモリの破棄
	if (m_pTime != nullptr)
	{
		m_pTime = nullptr;
	}

	//メモリの破棄
	if (m_pEnemyManager != nullptr)
	{
		m_pEnemyManager = nullptr;
	}

	//メモリの破棄
	if (m_pGimmickManager != nullptr)
	{
		delete m_pGimmickManager;
		m_pGimmickManager = nullptr;
	}

	//メモリの破棄
	if (m_pExplosionManager != nullptr)
	{
		delete m_pExplosionManager;
		m_pExplosionManager = nullptr;
	}

	//メモリの破棄
	if (m_pEnemyBulletManager != nullptr)
	{
		delete m_pEnemyBulletManager;
		m_pEnemyBulletManager = nullptr;
	}

	//メモリの破棄
	if (m_pBarrierManager != nullptr)
	{
		delete m_pBarrierManager;
		m_pBarrierManager = nullptr;
	}

	//メモリの破棄
	if (m_pLockon != nullptr)
	{
		m_pLockon = nullptr;
	}

	//バトルエリアの初期化
	CBattleAreaManager::GetInstance()->Uninit();

	//終了処理
	CScene::Uninit();
}

//============================
//ゲームの更新処理
//============================
void CGame::Update()
{
	//時間の更新
	m_pTime->Update();

	//エリアマネージャー更新
	CBattleAreaManager::GetInstance()->Update();

	//ロックオンの更新
	if (m_pLockon != nullptr)
	{
		m_pLockon->Update();
	}

	//敵の生成
#if _DEBUG
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_1))
	{
		CSpawn_Enemy::Create({ 0.0f, 10.0f, 0.0f }, CEnemy::ENEMYTYPE_ENEMY000);
	}
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_2))
	{
		CEnemy::Create({ 0.0f, 0.0f, 0.0f }, CEnemy::ENEMYTYPE_ENEMY001);
	}
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_3))
	{
		CExplodingBarrel::Create({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });
	}
#endif

	//マネージャーのインスタンスを取得
	CManager* pManager = CManager::GetInstance();

	//フェードが終わっていたら更新
	if (CManager::GetInstance()->GetFade()->GetEnd())
	{
		//エンターで画面遷移
		if (pManager->GetKeyboard()->GetTrigger(DIK_RETURN) || pManager->GetJoypad()->GetPress(CInputJoypad::JOYKEY_A) || pManager->GetJoypad()->GetPress(CInputJoypad::JOYKEY_START) || m_bClear)
		{
			//ゲームに画面遷移
			pManager->GetFade()->SetFade(CScene::MODE_RESULT);
		}
	}
	
}

//============================
//ゲームの描画処理
//============================
void CGame::Draw()
{
	
}

//============================
//ゲームの読み込み
//============================
void CGame::Load()
{

}

//============================
//ロックオンの設定
//============================
void CGame::SetLockon(bool lockon)
{
	//ロックオンの判定
	if (lockon)
	{
		//ロックオンしていないなら生成
		if (m_pLockon != nullptr)
		{
			return;
		}

		//生成
		m_pLockon = CLockon::Create();
	}
	else //消す場合
	{
		//ロックオンしてるなら消去
		if (m_pLockon == nullptr)
		{
			return;
		}

		//生成
		m_pLockon->Uninit();
		m_pLockon = nullptr;
	}
}

//============================
//モデルの読み込み
//============================
void CGame::ModelLoad()
{
	//ローカル変数宣言
	FILE* pFile;

	//ファイルを開く
	pFile = fopen("data\\FILE\\model.bin", "rb");

	//ファイルに情報を書き出す
	if (pFile != NULL)
	{
		//読み込み用の変数
		int nModelNum = 0;

		//モデルの数
		fread(&nModelNum, sizeof(int), 1, pFile);

		//配置したモデルの数だけ情報を書き出す
		for (int i = 0; i < nModelNum; i++)
		{
			//読み込み用変数
			D3DXVECTOR3 Pos;
			D3DXVECTOR3 Rot;
			CModel::MODEL_TYPE Type;

			//モデルの情報
			fread(&Pos, sizeof(D3DXVECTOR3), 1, pFile);			//位置
			fread(&Rot, sizeof(D3DXVECTOR3), 1, pFile);			//向き
			fread(&Type, sizeof(CModel::MODEL_TYPE), 1, pFile);	//種類

			//生成
			CModel::Create(Pos, Rot, Type);
		}

		//ファイルを閉じる
		fclose(pFile);
	}
}