//================================
//
//behavior_enemy000.cppに必要な宣言[behavior_enemy000.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BEHAVIOR_ENEMY000_H_ //このマクロ定義がされていなかったら
#define _BEHAVIOR_ENEMY000_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "behavior_enemy.h"

//==========================
//追いかける
//==========================
class CEnemyAction_Chase000 : public CEnemyAction_Chase
{
public:

	//コンストラクタ
	CEnemyAction_Chase000() {};
	CEnemyAction_Chase000(CEnemy* enemy)
	{
		enemy->SetMotion(1);
	};

	//定数
	static constexpr float VALUE_MOVE = 1.0f;	//移動量

	void Action(CEnemy* enemy) override
	{
		CEnemyAction_Chase::Action(enemy);
	};	//アクション

	//攻撃アクションを設定
	void NextAction(CEnemy* enemy) override;
};

//==========================
//エネミー000の攻撃処理
//==========================
class CEnemyAction_Attack000 : public CEnemyAction_Attack
{
public:

	//コンストラクタ
	CEnemyAction_Attack000() {};
	CEnemyAction_Attack000(CEnemy* enemy)
	{
		//設定
		GetAttackInstanse()->SetCollisionTime(65);
		GetAttackInstanse()->SetEndTime(100.0f);
		GetAttackInstanse()->SetDamageValue(1);
		SetAttackLength(30.0f);
		enemy->SetMotion(2);
	};

	void Action(CEnemy* enemy) override
	{
		CEnemyAction_Attack::Action(enemy);
	};	//攻撃

	//追いかけるアクションを設定
	void NextAction(CEnemy* enemy) override
	{
		SetNextAction(new CEnemyAction_Chase000(enemy));
	}
};

//=======================================
//以下はバックアップ
//=======================================

//==========================
//エネミー000のアタックストラテジー
//==========================
class CEnemy000Attack : public CEnemyAttack
{
public:

	//コンストラクタ
	CEnemy000Attack();
	CEnemy000Attack(CEnemy* enemy);

	//パラメータの設定
	void SetParam() override
	{
		//設定
		SetCollisionTime(65);
		SetEndTime(100.0f);
		SetDamageValue(1);
		SetAttackLength(30.0f);
	}
};

#endif