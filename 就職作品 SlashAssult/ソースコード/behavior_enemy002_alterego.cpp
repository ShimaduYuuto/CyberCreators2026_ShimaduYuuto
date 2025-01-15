//================================
//
//敵の行動まとめ[behavior_enemy000.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "behavior_enemy002_alterego.h"
#include "enemy002_alterego.h"

//======================================================================
//チャージショット
//======================================================================

//====================================
//行動を設定
//====================================
void CEnemyActionAlterEgo_ChargeShot::Action(CEnemy* enemy)
{
	CEnemyAction_ChargeShot::Action(enemy);
}

//====================================
//次の行動を設定
//====================================
void CEnemyActionAlterEgo_ChargeShot::NextAction(CEnemy* enemy)
{
	SetNextAction(new CEnemyActionAlterEgo_ChargeShot(enemy));
	enemy->Uninit();
}