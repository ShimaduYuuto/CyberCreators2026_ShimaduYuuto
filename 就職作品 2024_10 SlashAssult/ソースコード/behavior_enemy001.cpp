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
CEnemyBehavior_Chase001::CEnemyBehavior_Chase001(CEnemy* enemy) : CEnemyBehavior_Chase(enemy)
{
	enemy->SetMotion(CEnemy001::ENEMY001MOTION_WALK);	//モーションの設定

	//固有の設定
	CEnemy001* enemy001 = dynamic_cast<CEnemy001*>(enemy);
	enemy001->SetDamageJudge(false);	//ダメージを受けない判定
}

//====================================
//行動を設定
//====================================
void CEnemyBehavior_Chase001::Action(CEnemy* enemy)
{
	//追いかける行動(基底)を設定
	CEnemyBehavior_Chase::Action(enemy);
}

//====================================
//次の行動を設定
//====================================
void CEnemyBehavior_Chase001::NextAction(CEnemy* enemy)
{
	//攻撃を設定
	SetNextAction(new CEnemyBehavior_Attack001(enemy));
}

//======================================================================
//攻撃
//======================================================================

//====================================
//コンストラクタ
//====================================
CEnemyBehavior_Attack001::CEnemyBehavior_Attack001(CEnemy* enemy) : CEnemyBehavior_Attack(enemy)
{
	//設定
	GetAttackInstanse()->SetCollisionTime(START_COLLISON_TIME);	//判定を始める時間
	GetAttackInstanse()->SetEndTime(END_TIME);					//終了時間
	GetAttackInstanse()->SetDamageValue(DAMAGE_VALUE);			//ダメージ量
	SetAttackLength(ATTACK_LENGTH);								//攻撃の距離
	enemy->SetMotion(CEnemy001::ENEMY001MOTION_ATTACK);			//モーション

	//固有の設定
	CEnemy001* enemy001 = dynamic_cast<CEnemy001*>(enemy);
	enemy001->SetDamageJudge(true);				//ダメージを受ける判定
}

//====================================
//行動を設定
//====================================
void CEnemyBehavior_Attack001::Action(CEnemy* enemy)
{
	CEnemyBehavior_Attack::Action(enemy);
}

//====================================
//次の行動を設定
//====================================
void CEnemyBehavior_Attack001::NextAction(CEnemy* enemy)
{
	//追いかける
	SetNextAction(new CEnemyBehavior_Chase001(enemy));
}