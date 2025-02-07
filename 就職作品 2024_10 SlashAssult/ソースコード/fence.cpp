//======================================
//
//	フェンスの描画[fence.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "fence.h"
#include "manager.h"

//定数
const std::string CFence::MODEL_PATH = "data\\model\\fence000.x";

//============================
//描画
//============================
void CFence::Draw()
{
	if ((GetPos().x < 0.0f && GetPos().x > CManager::GetInstance()->GetCamera()->GetPos().x) || (GetPos().x > 0.0f && GetPos().x < CManager::GetInstance()->GetCamera()->GetPos().x))
	{
		return;
	}

	CObjectX::Draw(MODEL_PATH.c_str());
}