//======================================
//
//	ポーズの選択肢の処理[select_title.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "select_title.h"
#include "manager.h"
#include "game.h"

//定数
const std::string CSelect_Title::TEXTURE_PATH =
{
	"data\\TEXTURE\\pause002.png"
};

//============================
//コンストラクタ
//============================
CSelect_Title::CSelect_Title(int nPriority) : CPause_Select(nPriority)
{

}

//============================
//デストラクタ
//============================
CSelect_Title::~CSelect_Title()
{

}

//============================
//決定時の処理
//============================
void CSelect_Title::Decision()
{
	//新しいゲームシーンに移行
	CManager* pManager = CManager::GetInstance();
	pManager->GetFade()->SetFade(CScene::MODE_TITLE);
}

//============================
//描画
//============================
void CSelect_Title::Draw()
{
	//描画処理
	CObject2D::Draw(TEXTURE_PATH.c_str());
}