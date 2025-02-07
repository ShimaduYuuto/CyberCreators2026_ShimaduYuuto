//================================
//
//敵の行動まとめ[behavior_enemy000.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "behavior_enemy000.h"
#include "enemy000.h"

//======================================================================
//追いかける
//======================================================================

//====================================
//コンストラクタ
//====================================
CEnemyBehavior_Chase000::CEnemyBehavior_Chase000(CEnemy* enemy) : CEnemyBehavior_Chase(enemy)
{
	enemy->SetMotion(CEnemy000::ENEMY000MOTION_WALK);
};

//====================================
//行動を設定
//====================================
void CEnemyBehavior_Chase000::Action(CEnemy* enemy)
{
	CEnemyBehavior_Chase::Action(enemy);
};	//アクション

//====================================
//次の行動を設定
//====================================
void CEnemyBehavior_Chase000::NextAction(CEnemy* enemy)
{
	//攻撃を設定
	SetNextAction(new CEnemyBehavior_Attack000(enemy));
}

//======================================================================
//攻撃
//======================================================================

//====================================
//コンストラクタ
//====================================
CEnemyBehavior_Attack000::CEnemyBehavior_Attack000(CEnemy* enemy) : CEnemyBehavior_Attack(enemy)
{
	//設定
	GetAttackInstanse()->SetCollisionTime(START_COLLISON_TIME);	//判定を始める時間
	GetAttackInstanse()->SetEndTime(END_TIME);					//終了時間
	GetAttackInstanse()->SetDamageValue(DAMAGE_VALUE);			//ダメージ量
	SetAttackLength(ATTACK_LENGTH);								//攻撃の距離
	enemy->SetMotion(CEnemy000::ENEMY000MOTION_ACTION);			//モーション
};

//====================================
//行動を設定
//====================================
void CEnemyBehavior_Attack000::Action(CEnemy* enemy)
{
	CEnemyBehavior_Attack::Action(enemy);
}

//====================================
//次の行動を設定
//====================================
void CEnemyBehavior_Attack000::NextAction(CEnemy* enemy)
{
	SetNextAction(new CEnemyBehavior_Chase000(enemy));
}