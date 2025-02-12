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
#include "cleartime.h"
#include "ui_gameguide.h"
#include "camera_game.h"
#include "pause.h"

//定数
const D3DXVECTOR3 CGame::TIME_POS = { SCREEN_WIDTH * 0.4f, 50.0f, 0.0f };
const std::string CGame::FILEPATH_MODEL = "data\\FILE\\model.bin";

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
	m_bDirectioning(false),
	m_pBarrierManager(nullptr),
	m_pEnemyBulletManager(nullptr),
	m_pDirection(nullptr),
	m_bBattle(false),
	m_bGameOver(false),
	m_bBossBattle(false),
	m_ControllerUIType(CUi_GameGuide::CONTROLLER_KEYBOARDMAUSE),
	m_bPause(false),
	m_pPause(nullptr)
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

	//ステージに配置するオブジェクト
	CSky::Create();

	//読み込み処理
	ModelLoad();
	GuideUILoad();

	//クリアタイムの初期化
	CClearTime::GetInstance()->ResetTime();
	CClearTime::GetInstance()->SetPos(TIME_POS);
	CClearTime::GetInstance()->Init(); 

	//フォグの設定
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);					//有効
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP);		//フォグモードの設定
	pDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.1f));	//色の設定
	float m_fFogDensity = 0.0005f;
	pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&m_fFogDensity));

	//BGM
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_WIND);

	//カメラを切り替え
	CManager::GetInstance()->ChangeCamera(new CCamera_Game());
	
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

	//戦闘中はクリア時間を加算
	if (m_bBattle && !m_bDirectioning && !m_bPause)
	{
		CClearTime::GetInstance()->AddTime(1.0f / 60.0f);
	}

	//エリアマネージャー更新
	CBattleAreaManager::GetInstance()->Update();

	//ロックオンの更新
	if (m_pLockon != nullptr)
	{
		m_pLockon->Update();
	}

	//演出中の処理
	DirectioningProcess();

	//表示UIの確認
	CheckGuideUI();

	//ポーズの処理
	PauseProcess();

	//次のシーンへ移行
	NextScene();
}

//============================
//演出中の処理
//============================
void CGame::DirectioningProcess()
{
	//判定
	if (!IsDeleteDirection()) return;

	//演出の破棄
	delete m_pDirection;
	m_pDirection = nullptr;
	m_bDirectioning = false;
}

//============================
//演出を破棄するか
//============================
bool CGame::IsDeleteDirection()
{
	//判定
	if (!m_bDirectioning) return false;				//演出中か確認
	if (m_pDirection == nullptr) return false;		//ヌルチェック
	if (!m_pDirection->TimeUpdate()) return false;	//更新が終わったら破棄

	return true;
}

//============================
//ガイドUIの確認
//============================
void CGame::CheckGuideUI()
{
	//マネージャーのインスタンスを取得
	CManager* pManager = CManager::GetInstance();

	//ガイドUIの確認
	//ジョイパッドを触っているか
	if (IsUsedJoipad())
	{
		//ジョイパッド用のUIに変更
		m_ControllerUIType = CUi_GameGuide::CONTROLLER_JOYPAD;
	}

	//キーボードかマウスを触っているか
	if (IsUsedKeyboardMouse())
	{
		//キーマウ用のUIに変更
		m_ControllerUIType = CUi_GameGuide::CONTROLLER_KEYBOARDMAUSE;
	}
}

//============================
//ジョイパッドを使っているか
//============================
bool CGame::IsUsedJoipad()
{
	//マネージャーのインスタンスを取得
	CManager* pManager = CManager::GetInstance();

	//判定
	if (pManager->GetJoypad()->GetAnyTrigger()) return true;													//どれかのボタンに触れたか
	if (pManager->GetJoypad()->GetStick().afTplDiameter[CInputJoypad::STICKTYPE_LEFT] > 0.0f) return true;		//左スティックを倒しているか
	if (pManager->GetJoypad()->GetStick().afTplDiameter[CInputJoypad::STICKTYPE_RIGHT] > 0.0f) return true;		//右スティックを倒しているか

	return false;
}

//============================
//キーボードマウスを使っているか
//============================
bool CGame::IsUsedKeyboardMouse()
{
	//マネージャーのインスタンスを取得
	CManager* pManager = CManager::GetInstance();

	//判定
	if (pManager->GetKeyboard()->GetAnyTrigger()) return true;	//どれかのボタンに触れたか
	if (pManager->GetMouse()->GetAnyTrigger()) return true;		//どれかのボタンをクリックしたか
	if (pManager->GetMouse()->GetMove().x > 0.0f) return true;	//マウスがX軸に動いたか
	if (pManager->GetMouse()->GetMove().y > 0.0f) return true;	//マウスがY軸に動いたか

	return false;
}

//============================
//次のシーンへ移行
//============================
void CGame::NextScene()
{
	//次のシーンへ移行できるか
	if (!CanNextScene()) return;

	//マネージャーのインスタンスを取得
	CManager* pManager = CManager::GetInstance();

	//死んでいたらタイトルに遷移
	if (m_bGameOver)
	{
		pManager->GetFade()->SetFade(CScene::MODE_TITLE);
	}
	else
	{
		//リザルトに画面遷移
		pManager->GetFade()->SetFade(CScene::MODE_RESULT);
	}
}

//============================
//次のシーンへ移行できるか
//============================
bool CGame::CanNextScene()
{
	//判定
	if (!CManager::GetInstance()->GetFade()->GetEnd()) return false; //フェードが終わっていたら更新
	if (!m_bClear && !m_bGameOver) return false;					 //クリア条件を満たしているか

	return true;
}

//============================
//ポーズの処理
//============================
void CGame::PauseProcess()
{
	//マネージャーのインスタンスを取得
	CManager* pManager = CManager::GetInstance();

	//ポーズの設定
	if ((pManager->GetKeyboard()->GetTrigger(DIK_P) || pManager->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_START)) && !m_bDirectioning && !m_bPause)
	{
		SetPause();
	}

	//ポーズの更新
	if (m_pPause != nullptr)
	{
		m_pPause->Update();
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
//ガイドUIの情報
//============================
void CGame::GuideUILoad()
{
	// ファイルの読み込み
	FILE* pFile = fopen("data\\FILE\\gameui.txt", "r");

	if (pFile == NULL)
	{// 種類毎の情報のデータファイルが開けなかった場合、
	 //処理を終了する
		return;
	}

	char aDataSearch[256];	// データ検索用
	int nDataCount = 0;		//データのカウント

	// ENDが見つかるまで読み込みを繰り返す
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch);	// 検索

		if (!strcmp(aDataSearch, "END_SCREPT"))
		{// 読み込みを終了
			fclose(pFile);
			break;
		}

		if (aDataSearch[0] == '#')
		{// 折り返す
			continue;
		}

		if (!strcmp(aDataSearch, "INFO"))
		{
			D3DXVECTOR3 Pos = { 0.0f, 0.0f, 0.0f };
			D3DXVECTOR3 Size = { 0.0f, 0.0f, 0.0f };

			while (1)
			{
				fscanf(pFile, "%s", aDataSearch);	// 検索

				//読み込みの終了
				if (!strcmp(aDataSearch, "END_INFO"))
				{
					//UIの生成
					CUi_GameGuide::Create(Pos, static_cast<CUi_GameGuide::GUIDE>(nDataCount), Size);
					nDataCount++;
					break;
				}

				//位置
				if (!strcmp(aDataSearch, "POS"))
				{
					fscanf(pFile, "%f", &Pos.x);
					fscanf(pFile, "%f", &Pos.y);
					fscanf(pFile, "%f", &Pos.z);
				}

				//サイズ
				if (!strcmp(aDataSearch, "SIZE"))
				{
					fscanf(pFile, "%f", &Size.x);
					fscanf(pFile, "%f", &Size.y);
					fscanf(pFile, "%f", &Size.z);
				}
			}
		}
	}
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
	pFile = fopen(FILEPATH_MODEL.c_str(), "rb");

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

//============================
//演出の設定
//============================
void CGame::SetDirection(CDirection::DIRECTIONTYPE type)
{
	//範囲外の種類なら弾く
	if (type < 0 && type >= CDirection::DIRECTIONTYPE_MAX)
	{
		return;
	}

	//演出があるなら弾く
	if (m_pDirection != nullptr)
	{
		return;
	}

	//演出の生成
	m_pDirection = CDirection::Create(type);
	m_bDirectioning = true;
}

//============================
//ポーズの設定
//============================
void CGame::SetPause()
{
	m_bPause = m_bPause ? false : true;

	if (m_bPause)
	{
		CObject::ChangeUpdateObject(CObject::TAG_PAUSE);

		if (m_pPause == nullptr)
		{
			m_pPause = CPause::Create();
		}
	}
	else
	{
		CObject::ChangeUpdateObject(CObject::TAG_GAME);

		if (m_pPause != nullptr)
		{
			m_pPause = nullptr;
		}
	}
}