//======================================
//
//	会場の描画[venue.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "venue.h"
#include "game.h"

//定数
const std::string CVenue::MODEL_PATH = "data\\model\\venue003.x";

//============================
//描画
//============================
void CVenue::Draw()
{
	CObjectX::Draw(MODEL_PATH.c_str());
}