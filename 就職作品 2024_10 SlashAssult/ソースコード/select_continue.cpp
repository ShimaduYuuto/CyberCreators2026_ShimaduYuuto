//======================================
//
//	ポーズの選択肢の処理[select_continue.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "select_continue.h"
#include "manager.h"
#include "game.h"

//定数
const std::string CSelect_Continue::TEXTURE_PATH =
{
	"data\\TEXTURE\\pause000.png"
};

//============================
//コンストラクタ
//============================
CSelect_Continue::CSelect_Continue(int nPriority) : CPause_Select(nPriority)
{

}

//============================
//デストラクタ
//============================
CSelect_Continue::~CSelect_Continue()
{

}

//============================
//決定時の処理
//============================
void CSelect_Continue::Decision()
{
	//ポーズの解除
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());
	pGame->SetPause();
}

//============================
//描画
//============================
void CSelect_Continue::Draw()
{
	//描画処理
	CObject2D::Draw(TEXTURE_PATH.c_str());
}