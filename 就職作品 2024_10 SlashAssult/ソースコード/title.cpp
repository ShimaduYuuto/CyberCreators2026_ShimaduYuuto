//======================================
//
//	タイトルの処理[title.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "title.h"
#include "manager.h"
#include "title_logo.h"
#include "sky.h"
#include "title_player.h"
#include "field.h"
#include "model.h"
#include "camera_title.h"
#include "ui_gamestart.h"

//============================
//タイトルのコンストラクタ
//============================
CTitle::CTitle() :
	m_pField(nullptr),
	m_pPlayer(nullptr)
{
	
}

//============================
//タイトルのデストラクタ
//============================
CTitle::~CTitle()
{
	//フォグの設定
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
}

//============================
//タイトルの初期化
//============================
HRESULT CTitle::Init()
{
	//プレイヤーの生成
	if (m_pPlayer == nullptr)
	{
		m_pPlayer = CTitle_Player::Create();
	}

	//フィールドの生成
	if (m_pField == nullptr)
	{
		m_pField = CField::Create({ 0.0f, 0.0f, 0.0f });
		m_pPlayer->SetPos(m_pField->ConvertMeshPos(m_pPlayer->GetPos()));
	}

	//その他のオブジェクト
	CTitle_Logo::Create({ 640.0f, 200.0f, 0.0f });
	CSky::Create();
	CModel::Create({ 0.0f, 0.0f, 3.0f }, { 0.0f, D3DX_PI * 0.5f, 0.0f }, CModel::MODEL_TYPE_FENCE);
	CUi_GameStart::Create();

	//フォグの設定
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);					//有効
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP);		//フォグモードの設定
	pDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.1f));	//色の設定
	float m_fFogDensity = 0.0005f;
	pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&m_fFogDensity));

	//BGM
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_TITLE);

	//カメラを切り替え
	CManager::GetInstance()->ChangeCamera(new CCamera_Title());

	return S_OK;
}

//============================
//タイトルの終了処理
//============================
void CTitle::Uninit()
{
	//プレイヤーの破棄
	if (m_pPlayer != nullptr)
	{
		m_pPlayer = nullptr;
	}

	//フィールドの破棄
	if (m_pField != nullptr)
	{
		m_pField = nullptr;
	}

	//終了処理
	CScene::Uninit();
}

//============================
//タイトルの更新処理
//============================
void CTitle::Update()
{
	//マネージャーのインスタンスを取得
	CManager* pManager = CManager::GetInstance();

	//フェードが終わっていたら更新
	if (CManager::GetInstance()->GetFade()->GetEnd())
	{
		//エンターで画面遷移
		if (pManager->GetKeyboard()->GetTrigger(DIK_RETURN) || pManager->GetJoypad()->GetPress(CInputJoypad::JOYKEY_A) || pManager->GetJoypad()->GetPress(CInputJoypad::JOYKEY_START))
		{
			//ゲームに画面遷移
			pManager->GetFade()->SetFade(CScene::MODE_GAME);
			m_pPlayer->SetMotion(CTitle_Player::TITLE_PLAYERMOTION_STANDUP);
		}
	}
}

//============================
//タイトルの描画処理
//============================
void CTitle::Draw()
{

}