//================================
//
//behavior_enemy003.cppに必要な宣言[behavior_enemy003.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BEHAVIOR_ENEMY003_H_ //このマクロ定義がされていなかったら
#define _BEHAVIOR_ENEMY003_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "behavior_enemy.h"

//==========================
//待機
//==========================
class CEnemyBehavior_Standby003 : public CEnemyBehavior
{
public:

	//コンストラクタ
	CEnemyBehavior_Standby003(CEnemy* enemy) : m_nCoolTime(0)
	{
		enemy->SetMotion(0);
		m_nCoolTime = COOL_TIME;
		enemy->SetCollisionProcess(true);
	};

	//定数
	static constexpr int COOL_TIME{ 90 };	//クールタイムの時間
	void Action(CEnemy* enemy) override;	//アクション

	//攻撃アクションを設定
	void NextAction(CEnemy* enemy) override;

private:
	int m_nCoolTime;
};

//==========================
//エネミー003の攻撃処理
//==========================
class CEnemyBehavior_Attack003 : public CEnemyBehavior_Attack
{
public:

	//コンストラクタ
	CEnemyBehavior_Attack003(CEnemy* enemy) : CEnemyBehavior_Attack(enemy)
	{
		//設定
		GetAttackInstanse()->SetCollisionTime(65);
		GetAttackInstanse()->SetEndTime(100.0f);
		GetAttackInstanse()->SetDamageValue(1);
		SetAttackLength(30.0f);
		enemy->SetMotion(2);
		enemy->SetCollisionProcess(false);
	};

	void Action(CEnemy* enemy) override
	{
		CEnemyBehavior_Attack::Action(enemy);
	};	//攻撃

	//待機アクションを設定
	void NextAction(CEnemy* enemy) override
	{
		SetNextAction(new CEnemyBehavior_Standby003(enemy));
	}
};

//==========================
//チャージアタック
//==========================
class CEnemyBehavior_ChargeAttack : public CEnemyBehavior
{
public:

	static constexpr int CHARGE_TIME{ 80 };			//チャージ時間
	static constexpr int END_TIME{ 200 };			//終了の時間
	static constexpr float SPEED_MOVE{ 3.0f };		//攻撃の移動速度

	//コンストラクタ
	CEnemyBehavior_ChargeAttack(CEnemy* enemy) : m_nChargeCount(0), m_fAttackAngle(0.0f)
	{
		//設定
		enemy->SetMotion(2);
		enemy->SetCollisionProcess(false);
	};

	//デストラクタ
	~CEnemyBehavior_ChargeAttack() {}

	void Action(CEnemy* enemy) override;	//攻撃

	//待機アクションを設定
	void NextAction(CEnemy* enemy) override
	{
		SetNextAction(new CEnemyBehavior_Standby003(enemy));
	}

private:

	void LookAtPlayer(CEnemy* enemy);					//プレイヤーの方を向く
	void PreparationAttack(CEnemy* enemy, float angle);	//攻撃の準備
	void EndAttack(CEnemy* enemy);						//攻撃終了時の処理

	bool CheckAttackHit(CEnemy* enemy);	//攻撃が当たったかの判定

	int m_nChargeCount;		//チャージのカウント
	float m_fAttackAngle;	//突進方向
};

#endif