//================================
//
//敵の行動まとめ[behavior_enemy001.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "behavior_enemy001.h"
#include "enemy001.h"

//======================================================================
//追いかける
//======================================================================

//====================================
//コンストラクタ
//====================================
CEnemyAction_Chase001::CEnemyAction_Chase001(CEnemy* enemy) : CEnemyAction_Chase(enemy)
{
	//モーションの設定
	enemy->SetMotion(1);
	CEnemy001* enemy001 = (CEnemy001*)enemy;
	enemy001->SetDamageJudge(false);
}

//====================================
//次の行動を設定
//====================================
void CEnemyAction_Chase001::NextAction(CEnemy* enemy)
{
	//攻撃を設定
	SetNextAction(new CEnemyAction_Attack001(enemy));
}

//======================================================================
//攻撃
//======================================================================

//====================================
//コンストラクタ
//====================================
CEnemyAction_Attack001::CEnemyAction_Attack001(CEnemy* enemy) : CEnemyAction_Attack(enemy)
{
	//設定
	GetAttackInstanse()->SetCollisionTime(45);
	GetAttackInstanse()->SetEndTime(100.0f);
	GetAttackInstanse()->SetDamageValue(1);
	SetAttackLength(50.0f);

	enemy->SetMotion(5);
	CEnemy001* enemy001 = (CEnemy001*)enemy;
	enemy001->SetDamageJudge(true);
}