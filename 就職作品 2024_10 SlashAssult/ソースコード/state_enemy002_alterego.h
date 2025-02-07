//================================
//
//state_enemy002_alterego.cppに必要な宣言[state_enemy002_alterego.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_ENEMY002_ALTEREGO_H_ //このマクロ定義がされていなかったら
#define _STATE_ENEMY002_ALTEREGO_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "behavior_enemy002_alterego.h"

//========================
//通常状態
//========================
class CState_Enemy002_AlterEgo_Normal : public CState_Enemy_Normal
{
public:

	//メンバ関数
	CState_Enemy002_AlterEgo_Normal(CEnemy* enemy);	//コンストラクタ

	//状態の更新
	void UpdateState(CEnemy* enemy) override
	{
		CState_Enemy_Normal::UpdateState(enemy);
	}
};

//========================
//ダメージ状態
//========================
class CState_Enemy002_AlterEgo_Damage : public CState_Enemy002_Damage
{
public:

	//メンバ関数
	CState_Enemy002_AlterEgo_Damage(CEnemy* enemy) : CState_Enemy002_Damage(enemy){}	//コンストラクタ

	//状態の更新
	void UpdateState(CEnemy* enemy) override
	{
		CState_Enemy002_Damage::UpdateState(enemy);
	}
};

//========================
//吹き飛び状態
//========================
class CState_Enemy002_AlterEgo_Blow : public CState_Enemy002_Blow
{
public:

	//メンバ関数
	CState_Enemy002_AlterEgo_Blow()
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
class CState_Enemy002_AlterEgo_Stick : public CState_Enemy002_Stick
{
public:

	//メンバ関数
	CState_Enemy002_AlterEgo_Stick(){}												//コンストラクタ
	CState_Enemy002_AlterEgo_Stick(CEnemy* enemy) : CState_Enemy002_Stick(enemy){}	//コンストラクタ

	//状態の更新
	void UpdateState(CEnemy* enemy) override
	{
		CState_Enemy_Stick::UpdateState(enemy);
	}
};

//========================
//スタン状態
//========================
class CState_Enemy002_AlterEgo_Stan : public CState_Enemy002_Stan
{
public:

	//メンバ関数
	CState_Enemy002_AlterEgo_Stan(){}												//コンストラクタ
	CState_Enemy002_AlterEgo_Stan(CEnemy* enemy) : CState_Enemy002_Stan(enemy) {}	//コンストラクタ
	~CState_Enemy002_AlterEgo_Stan() override {};									//デストラクタ

	//状態の更新
	void UpdateState(CEnemy* enemy) override
	{
		CState_Enemy002_Stan::UpdateState(enemy);
	}
};

//========================
//演出状態
//========================
class CState_Enemy002_AlterEgo_Direction : public CState_Enemy002_Direction
{
public:

	CState_Enemy002_AlterEgo_Direction() {}													//コンストラクタ
	CState_Enemy002_AlterEgo_Direction(CEnemy* enemy) : CState_Enemy002_Direction(enemy) {}	//コンストラクタ

	//状態の更新
	void UpdateState(CEnemy* enemy) override 
	{
		CState_Enemy002_Direction::UpdateState(enemy);
	}
};

#endif