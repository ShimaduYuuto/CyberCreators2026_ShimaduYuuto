//======================================
//
//	会場の描画[venue.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "venue.h"
#include "game.h"
#include "manager.h"

//定数
const std::string CVenue::MODEL_PATH = "data\\model\\venue004.x";
const std::string CVenue::BOSSBATTLE_MODEL_PATH = "data\\model\\bossvenue000.x";

//============================
//描画
//============================
void CVenue::Draw()
{
	//ゲームシーンなら判定
	if (CManager::GetInstance()->GetScene()->GetMode() != CManager::GetInstance()->GetScene()->MODE_GAME)
	{
		return;
	}

	//ゲームシーンの取得
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//ボス戦になったらモデルを置き換える
	if (pGame->GetBossBattleJudge())
	{
		//外側から内側が見えるモデルに変更
		CObjectX::Draw(BOSSBATTLE_MODEL_PATH.c_str());
	}
	else
	{
		//通常のモデル
		CObjectX::Draw(MODEL_PATH.c_str());
	}
}