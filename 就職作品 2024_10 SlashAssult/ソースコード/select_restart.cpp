//======================================
//
//	ポーズの選択肢の処理[select_restart.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "select_restart.h"
#include "manager.h"
#include "game.h"

//定数
const std::string CSelect_Restart::TEXTURE_PATH =
{
	"data\\TEXTURE\\pause001.png"
};

//============================
//コンストラクタ
//============================
CSelect_Restart::CSelect_Restart(int nPriority) : CPause_Select(nPriority)
{

}

//============================
//デストラクタ
//============================
CSelect_Restart::~CSelect_Restart()
{

}

//============================
//決定時の処理
//============================
void CSelect_Restart::Decision()
{
	//新しいゲームシーンに移行
	CManager* pManager = CManager::GetInstance();
	pManager->GetFade()->SetFade(CScene::MODE_GAME);
}

//============================
//描画
//============================
void CSelect_Restart::Draw()
{
	//描画処理
	CObject2D::Draw(TEXTURE_PATH.c_str());
}