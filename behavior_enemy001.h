//================================
//
//behavior_enemy001.cppに必要な宣言[behavior_enemy001.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BEHAVIOR_ENEMY001_H_ //このマクロ定義がされていなかったら
#define _BEHAVIOR_ENEMY001_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "behavior_enemy.h"
//#include "enemy001.h"

//class CEnemy001;

//==========================
//追いかける
//==========================
class CEnemyAction_Chase001 : public CEnemyAction_Chase
{
public:

	//コンストラクタ
	CEnemyAction_Chase001() {};
	CEnemyAction_Chase001(CEnemy* enemy)
	{
		//モーションの設定
		enemy->SetMotion(1);
		//CEnemy001* enemy001 = (CEnemy001*)enemy;
		//enemy001->SetDamageJudge(false);
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
//エネミー001の攻撃処理
//==========================
class CEnemyAction_Attack001 : public CEnemyAction_Attack
{
public:

	//コンストラクタ
	CEnemyAction_Attack001() {};
	CEnemyAction_Attack001(CEnemy* enemy)
	{
		//設定
		GetAttackInstanse()->SetCollisionTime(45);
		GetAttackInstanse()->SetEndTime(100.0f);
		GetAttackInstanse()->SetDamageValue(1);
		SetAttackLength(50.0f);

		enemy->SetMotion(5);
		//CEnemy001* enemy001 = (CEnemy001*)enemy;
		//enemy001->SetDamageJudge(true);
	};

	void Action(CEnemy* enemy) override
	{
		CEnemyAction_Attack::Action(enemy);
	};	//攻撃

	//追いかけるアクションを設定
	void NextAction(CEnemy* enemy) override
	{
		SetNextAction(new CEnemyAction_Chase001(enemy));
	}
};

//=======================================
//以下はバックアップ
//=======================================

//==========================
//エネミー001のアタックストラテジー
//==========================
class CEnemy001Attack : public CEnemyAttack
{
public:

	//コンストラクタ
	CEnemy001Attack();
	CEnemy001Attack(CEnemy* enemy);

	//パラメータの設定
	void SetParam() override
	{
		//設定
		SetCollisionTime(45);
		SetEndTime(100.0f);
		SetDamageValue(1);
		SetAttackLength(50.0f);
	}
};

#endif