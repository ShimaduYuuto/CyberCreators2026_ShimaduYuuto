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

}

//============================
//タイトルの初期化
//============================
HRESULT CTitle::Init()
{
	CTitle_Logo::Create({ 640.0f, 200.0f, 0.0f });
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