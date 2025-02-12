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
	//描画するかを確認
	if (IsDraw())
	{
		return;
	}

	//親クラスで描画
	CObjectX::Draw(MODEL_PATH.c_str());
}

//============================
//描画をするかの判定を返す
//============================
bool CFence::IsDraw()
{
	//判定
	if ((GetPos().x < 0.0f && GetPos().x > CManager::GetInstance()->GetCamera()->GetPos().x)) return true;	//自身のX座標が-でカメラの視点より値が小さいなら描画する
	if ((GetPos().x > 0.0f && GetPos().x < CManager::GetInstance()->GetCamera()->GetPos().x)) return true;	//自身のX座標が+でカメラの視点より値が大きいなら描画する

	return false;
}