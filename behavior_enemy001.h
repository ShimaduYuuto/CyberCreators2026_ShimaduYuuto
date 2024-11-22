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
	};
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