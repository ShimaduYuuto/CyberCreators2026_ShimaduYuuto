//======================================
//
//	木の描画[tree.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "tree.h"

//定数
const std::string CTree::MODEL_PATH = "data\\model\\tree000.x";

//============================
//描画
//============================
void CTree::Draw()
{
	CObjectX::Draw(MODEL_PATH.c_str());
}