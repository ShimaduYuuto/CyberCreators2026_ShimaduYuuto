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
void CEnemyBehaviorAlterEgo_ChargeShot::Action(CEnemy* enemy)
{
	CEnemyBehavior_ChargeShot::Action(enemy);
}

//====================================
//次の行動を設定
//====================================
void CEnemyBehaviorAlterEgo_ChargeShot::NextAction(CEnemy* enemy)
{
	SetNextAction(new CEnemyBehaviorAlterEgo_ChargeShot(enemy));
	enemy->Uninit();
}