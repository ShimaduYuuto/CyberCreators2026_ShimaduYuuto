//================================
//
//state_enemy.cppに必要な宣言[state_enemy.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_ENEMY002_H_ //このマクロ定義がされていなかったら
#define _STATE_ENEMY002_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "enemy.h"
#include "behavior_enemy002.h"
#include "state_enemy_normal.h"
#include "state_enemy_damage.h"
#include "state_enemy_blow.h"
#include "state_enemy_stick.h"
#include "state_enemy_stan.h"

//========================
//通常状態
//========================
class CState_Enemy002_Normal : public CState_Enemy_Normal
{
public:

	//メンバ関数
	CState_Enemy002_Normal(CEnemy* enemy)
	{
		SetAction(new CEnemyAction_Standby(enemy));
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
class CState_Enemy002_Damage : public CState_Enemy_Damage
{
public:

	//メンバ関数
	CState_Enemy002_Damage()
	{
		SetAction(new CEnemyAction());
		SetEndTime(60);
	};	//コンストラクタ

	CState_Enemy002_Damage(CEnemy* enemy)
	{
		SetAction(new CEnemyAction());
		SetEndTime(60);
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
class CState_Enemy002_Blow : public CState_Enemy_Blow
{
public:

	//メンバ関数
	CState_Enemy002_Blow()
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
class CState_Enemy002_Stick : public CState_Enemy_Stick
{
public:

	//メンバ関数
	CState_Enemy002_Stick()
	{
		SetEndTime(60);
	};	//コンストラクタ

	CState_Enemy002_Stick(CEnemy* enemy) : CState_Enemy_Stick(enemy)
	{
		SetEndTime(60);
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
class CState_Enemy002_Stan : public CState_Enemy_Stan
{
public:

	//メンバ関数
	CState_Enemy002_Stan()
	{
		SetAction(new CEnemyAction());
		SetEndTime(60);
	};	//コンストラクタ

	CState_Enemy002_Stan(CEnemy* enemy)
	{
		SetAction(new CEnemyAction());
		enemy->SetMotion(5);
		SetEndTime(180);
	};	//コンストラクタ

	//状態の更新
	void UpdateState(CEnemy* enemy) override
	{
		CState_Enemy_Stan::UpdateState(enemy);
	}
};

#endif