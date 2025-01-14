//======================================
//
//	フェンスの描画[fence.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "fence.h"

//定数
const std::string CFence::MODEL_PATH = "data\\model\\fence000.x";

//============================
//描画
//============================
void CFence::Draw()
{
	CObjectX::Draw(MODEL_PATH.c_str());
}