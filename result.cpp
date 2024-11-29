//======================================
//
//	リザルトの処理[result.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "result.h"
#include "manager.h"
#include "result_bg.h"

//============================
//リザルトのコンストラクタ
//============================
CResult::CResult()
{
	
}

//============================
//リザルトのデストラクタ
//============================
CResult::~CResult()
{

}

//============================
//リザルトの初期化
//============================
HRESULT CResult::Init()
{
	CResult_Bg::Create();

	return S_OK;
}

//============================
//リザルトの終了処理
//============================
void CResult::Uninit()
{
	//全オブジェクトの開放
	CScene::Uninit();
}

//============================
//リザルトの更新処理
//============================
void CResult::Update()
{
	//マネージャーのインスタンスを取得
	CManager* pManager = CManager::GetInstance();

	//フェードが終わっていたら更新
	if (CManager::GetInstance()->GetFade()->GetEnd())
	{
		//エンターで画面遷移
		if (pManager->GetKeyboard()->GetTrigger(DIK_RETURN) || pManager->GetJoypad()->GetPress(CInputJoypad::JOYKEY_A) || pManager->GetJoypad()->GetPress(CInputJoypad::JOYKEY_START))
		{
			//タイトルに画面遷移
			pManager->GetFade()->SetFade(CScene::MODE_TITLE);
		}
	}
}

//============================
//リザルトの描画処理
//============================
void CResult::Draw()
{

}