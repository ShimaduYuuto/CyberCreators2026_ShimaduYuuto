//================================
//
//エネミー000の状態処理[state_enemy000.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "state_enemy000.h"

//====================================
//コンストラクタ
//====================================
CState_Enemy000_Stick::CState_Enemy000_Stick(CEnemy* enemy) : CState_Enemy_Stick(enemy)
{
	SetEndTime(160);
	enemy->SetMotion(6);
}