//================================
//
//エネミー002の分身の状態処理[state_enemy002_alterego.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "state_enemy002_alterego.h"

//===============================================
//通常状態
//===============================================

//====================================
//コンストラクタ
//====================================
CState_Enemy002_AlterEgo_Normal::CState_Enemy002_AlterEgo_Normal(CEnemy* enemy)
{
	SetAction(new CEnemyActionAlterEgo_ChargeShot(enemy));
};