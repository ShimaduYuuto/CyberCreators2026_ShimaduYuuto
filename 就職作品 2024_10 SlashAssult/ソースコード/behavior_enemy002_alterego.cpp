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
	//基底の行動を設定
	CEnemyBehavior_ChargeShot::Action(enemy);	//チャージショット
}

//====================================
//次の行動を設定
//====================================
void CEnemyBehaviorAlterEgo_ChargeShot::NextAction(CEnemy* enemy)
{
	SetNextAction(new CEnemyBehaviorAlterEgo_ChargeShot(enemy));	//次の行動を設定
	enemy->Uninit();												//敵を破棄
}