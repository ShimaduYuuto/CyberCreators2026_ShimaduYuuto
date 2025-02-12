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
#include "effect_stan.h"

//========================
//通常状態
//========================
class CState_Enemy002_Normal : public CState_Enemy_Normal
{
public:

	//メンバ関数
	CState_Enemy002_Normal(CEnemy* enemy);	//コンストラクタ

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

	//定数
	static constexpr int TIME_END{ 120 };	//終了時間

	CState_Enemy002_Damage(CEnemy* enemy) : CState_Enemy_Damage(enemy)
	{
		SetAction(new CEnemyBehavior());
		SetEndTime(TIME_END);
		enemy->SetMotion(8);
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
	CState_Enemy002_Blow(CEnemy* enemy) : CState_Enemy_Blow(enemy)
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
class CState_Enemy002_Stick : public CState_Enemy_Stick
{
public:

	//定数
	static constexpr int TIME_END{ 300 };	//終了時間

	//メンバ関数
	CState_Enemy002_Stick(CEnemy* enemy);	//コンストラクタ

	//状態の更新
	void UpdateState(CEnemy* enemy) override
	{
		//親の更新
		CState_Enemy_Stick::UpdateState(enemy);
	}
};

//========================
//スタン状態
//========================
class CState_Enemy002_Stan : public CState_Enemy_Stan
{
public:

	//定数
	static constexpr int END_TIME{ 3000 };	//終了時間

	//メンバ関数
	CState_Enemy002_Stan(CEnemy* enemy);	//コンストラクタ
	~CState_Enemy002_Stan() override;		//デストラクタ

	//状態の更新
	void UpdateState(CEnemy* enemy) override
	{
		CState_Enemy_Stan::UpdateState(enemy);
	}

private:
	CEffect_Stan* m_pStanEffect;
};

//========================
//演出状態
//========================
class CState_Enemy002_Direction : public CState_Enemy
{
public:

	//定数
	static constexpr int TIME_END{ 300 };	//終了時間

	//メンバ関数
	CState_Enemy002_Direction() : m_nCount(0)
	{
		SetAction(new CEnemyBehavior());
		SetEndTime(TIME_END);
	};	//コンストラクタ

	CState_Enemy002_Direction(CEnemy* enemy);	///コンストラクタ

	//状態の更新
	void UpdateState(CEnemy* enemy) override;

private:
	int m_nCount;	//カウント用
};

//========================
//演出状態
//========================
class CState_Enemy002_Direction_Destroy : public CState_Enemy
{
public:

	CState_Enemy002_Direction_Destroy(CEnemy* enemy);	///コンストラクタ

private:
	
	//状態の更新
	void UpdateState(CEnemy* enemy) override {}
};

#endif