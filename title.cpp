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

//============================
//タイトルのコンストラクタ
//============================
CTitle::CTitle()
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
	CTitle_Logo::Create({ 640.0f, 200.0f, 0.0f });
	CTitle_Player::Create();
	CSky::Create();
	

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
//タイトルの終了処理
//============================
void CTitle::Uninit()
{
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
			
		}
	}
}

//============================
//タイトルの描画処理
//============================
void CTitle::Draw()
{

}