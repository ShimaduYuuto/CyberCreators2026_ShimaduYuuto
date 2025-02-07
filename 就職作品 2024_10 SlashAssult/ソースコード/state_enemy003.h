//================================
//
//state_enemy.cppに必要な宣言[state_enemy.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_ENEMY003_H_ //このマクロ定義がされていなかったら
#define _STATE_ENEMY003_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "enemy003.h"
#include "behavior_enemy003.h"
#include "state_enemy_normal.h"
#include "state_enemy_damage.h"
#include "state_enemy_blow.h"
#include "state_enemy_stick.h"
#include "state_enemy_stan.h"

//========================
//通常状態
//========================
class CState_Enemy003_Normal : public CState_Enemy_Normal
{
public:

	//メンバ関数
	CState_Enemy003_Normal(CEnemy* enemy) : CState_Enemy_Normal(enemy)
	{
		SetAction(new CEnemyBehavior_Standby003(enemy));
	};	//コンストラクタ

	//状態の更新
	void UpdateState(CEnemy* enemy) override
	{
		CState_Enemy_Normal::UpdateState(enemy);
	}

private:

	//ギミックとの当たり判定
	void UpdateGimmickCollison(CGame_Character* character) override;
};

//========================
//ダメージ状態
//========================
class CState_Enemy003_Damage : public CState_Enemy_Damage
{
public:

	CState_Enemy003_Damage(CEnemy* enemy) : CState_Enemy_Damage(enemy)
	{
		SetAction(new CEnemyBehavior());
		SetEndTime(60);
		enemy->SetMotion(3);
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
class CState_Enemy003_Blow : public CState_Enemy_Blow
{
public:

	//メンバ関数
	CState_Enemy003_Blow()
	{
		SetAction(new CEnemyBehavior());
	};	//コンストラクタ

	CState_Enemy003_Blow(CEnemy* enemy)
	{
		SetAction(new CEnemyBehavior());
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
class CState_Enemy003_Stick : public CState_Enemy_Stick
{
public:

	//メンバ関数
	CState_Enemy003_Stick()
	{
		SetEndTime(180);
	};	//コンストラクタ

	CState_Enemy003_Stick(CEnemy* enemy) : CState_Enemy_Stick(enemy)
	{
		SetEndTime(180);
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
class CState_Enemy003_Stan : public CState_Enemy_Stan
{
public:

	//メンバ関数
	CState_Enemy003_Stan()
	{
		SetAction(new CEnemyBehavior());
		SetEndTime(300);
	};	//コンストラクタ

	CState_Enemy003_Stan(CEnemy* enemy)
	{
		SetAction(new CEnemyBehavior());
		SetEndTime(300);
	};	//コンストラクタ

	//状態の更新
	void UpdateState(CEnemy* enemy) override
	{
		CState_Enemy_Stan::UpdateState(enemy);
	}
};

#endif