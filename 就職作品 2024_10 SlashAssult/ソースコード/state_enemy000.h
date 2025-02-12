//================================
//
//state_enemy.cppに必要な宣言[state_enemy.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_ENEMY000_H_ //このマクロ定義がされていなかったら
#define _STATE_ENEMY000_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "enemy.h"
#include "behavior_enemy000.h"
#include "state_enemy_normal.h"
#include "state_enemy_damage.h"
#include "state_enemy_blow.h"
#include "state_enemy_stick.h"
#include "state_enemy_stan.h"

//========================
//通常状態
//========================
class CState_Enemy000_Normal : public CState_Enemy_Normal
{
public:

	//メンバ関数
	CState_Enemy000_Normal(CEnemy* enemy) : CState_Enemy_Normal(enemy)
	{
		SetAction(new CEnemyBehavior_Chase000(enemy));
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
class CState_Enemy000_Damage : public CState_Enemy_Damage
{
public:

	//関数
	CState_Enemy000_Damage(CEnemy* enemy) : CState_Enemy_Damage(enemy)
	{
		SetAction(new CEnemyBehavior());
		SetEndTime(60);
		enemy->SetMotion(5);
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
class CState_Enemy000_Blow : public CState_Enemy_Blow
{
public:

	//状態の更新
	void UpdateState(CEnemy* enemy) override
	{
		CState_Enemy_Blow::UpdateState(enemy);
	}
};

//========================
//貼り付け状態
//========================
class CState_Enemy000_Stick : public CState_Enemy_Stick
{
public:

	//定数
	static constexpr int END_TIME{ 160 };

	//関数
	CState_Enemy000_Stick(CEnemy* enemy);//コンストラクタ

	//状態の更新
	void UpdateState(CEnemy* enemy) override
	{
		CState_Enemy_Stick::UpdateState(enemy);
	}
};

//========================
//スタン状態
//========================
class CState_Enemy000_Stan : public CState_Enemy_Stan
{
public:

	//定数
	static constexpr int END_TIME{ 180 };	//状態終了時間

	//関数
	CState_Enemy000_Stan(CEnemy* enemy) : CState_Enemy_Stan(enemy)
	{
		SetAction(new CEnemyBehavior());
		SetEndTime(END_TIME);
	};	//コンストラクタ

	//状態の更新
	void UpdateState(CEnemy* enemy) override
	{
		CState_Enemy_Stan::UpdateState(enemy);
	}
};

#endif