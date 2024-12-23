//================================
//
//state_enemy.cppに必要な宣言[state_enemy.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_ENEMY001_H_ //このマクロ定義がされていなかったら
#define _STATE_ENEMY001_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "behavior_enemy001.h"
#include "state_enemy_normal.h"
#include "state_enemy_damage.h"
#include "state_enemy_blow.h"
#include "state_enemy_stick.h"
#include "state_enemy_stan.h"

//========================
//通常状態
//========================
class CState_Enemy001_Normal : public CState_Enemy_Normal
{
public:

	//メンバ関数
	CState_Enemy001_Normal(CEnemy* enemy) : CState_Enemy_Normal(enemy)
	{
		SetAction(new CEnemyAction_Chase001(enemy));
	};	//コンストラクタ

	//状態の更新
	void UpdateState(CEnemy* enemy) override
	{
		CState_Enemy_Normal::UpdateState(enemy);
	}
};

//========================
//ダメージ状態
//========================
class CState_Enemy001_Damage : public CState_Enemy_Damage
{
public:

	CState_Enemy001_Damage(CEnemy* enemy) : CState_Enemy_Damage(enemy)
	{
		SetAction(new CEnemyAction());
		SetEndTime(60);
		enemy->SetMotion(4);
	};	//コンストラクタ

	//状態の更新
	void UpdateState(CEnemy* enemy) override
	{
		CState_Enemy_Damage::UpdateState(enemy);
	}
};

//========================
//吹き飛び状態
//========================
class CState_Enemy001_Blow : public CState_Enemy_Blow
{
public:

	//メンバ関数
	CState_Enemy001_Blow()
	{
		SetAction(new CEnemyAction());
	};	//コンストラクタ

	//状態の更新
	void UpdateState(CEnemy* enemy) override
	{
		CState_Enemy_Blow::UpdateState(enemy);
	}
};

//========================
//貼り付け状態
//========================
class CState_Enemy001_Stick : public CState_Enemy_Stick
{
public:

	//メンバ関数
	CState_Enemy001_Stick()
	{
		SetEndTime(60);
	};	//コンストラクタ

	CState_Enemy001_Stick(CEnemy* enemy) : CState_Enemy_Stick(enemy)
	{
		SetEndTime(160);
	};	//コンストラクタ

	//状態の更新
	void UpdateState(CEnemy* enemy) override
	{
		CState_Enemy_Stick::UpdateState(enemy);
	}
};

//========================
//スタン状態
//========================
class CState_Enemy001_Stan : public CState_Enemy_Stan
{
public:

	//メンバ関数
	CState_Enemy001_Stan()
	{
		SetAction(new CEnemyAction());
		SetEndTime(60);
	};	//コンストラクタ

	CState_Enemy001_Stan(CEnemy* enemy)
	{
		SetAction(new CEnemyAction());
		SetEndTime(180);
	};	//コンストラクタ

	//状態の更新
	void UpdateState(CEnemy* enemy) override
	{
		CState_Enemy_Stan::UpdateState(enemy);
	}
};

#endif