//================================
//
//behavior_enemy002.cppに必要な宣言[behavior_enemy002.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BEHAVIOR_ENEMY002_H_ //このマクロ定義がされていなかったら
#define _BEHAVIOR_ENEMY002_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "behavior_enemy.h"
#include "enemybullet.h"
#include "effect_chargeshot.h"

//==========================
//追いかける
//==========================
class CEnemyAction_Standby : public CEnemyAction
{
public:

	//コンストラクタ
	CEnemyAction_Standby() {};
	CEnemyAction_Standby(CEnemy* enemy) : m_nCoolTime(0)
	{
		enemy->SetMotion(0);
		m_nCoolTime = COOL_TIME;
	};

	//定数
	static constexpr int COOL_TIME{90};		//クールタイムの時間
	void Action(CEnemy* enemy) override;	//アクション

	//攻撃アクションを設定
	void NextAction(CEnemy* enemy) override;

private:
	int m_nCoolTime;
};

//==========================
//エネミー002の攻撃処理
//==========================
class CEnemyAction_Attack002 : public CEnemyAction_Attack
{
public:

	//コンストラクタ
	CEnemyAction_Attack002() {};
	CEnemyAction_Attack002(CEnemy* enemy)
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

	//待機アクションを設定
	void NextAction(CEnemy* enemy) override
	{
		SetNextAction(new CEnemyAction_Standby(enemy));
	}
};

//==========================
//チャージショット
//==========================
class CEnemyAction_ChargeShot : public CEnemyAction
{
public:

	static constexpr int CHARGE_TIME{ 230 };		//チャージ時間
	static constexpr int CREATE_BULLET_TIME{ 50 };	//弾の生成時間
	static constexpr int END_TIME{ 300 };			//アクション終了時間
	static constexpr float ADD_SCALE_VALUE{ 0.03f };//スケールの加算量

	//コンストラクタ
	CEnemyAction_ChargeShot() {};
	CEnemyAction_ChargeShot(CEnemy* enemy) : m_nChargeCount(0), m_pBullet(nullptr), m_pEffect(nullptr)
	{
		//設定
		enemy->SetMotion(4);
	};

	//デストラクタ
	~CEnemyAction_ChargeShot()
	{
		if (m_pBullet != nullptr)
		{
			m_pBullet = nullptr;
		}
	}

	void Action(CEnemy* enemy) override;	//攻撃

	//待機アクションを設定
	void NextAction(CEnemy* enemy) override
	{
		SetNextAction(new CEnemyAction_Standby(enemy));
	}

private:
	int m_nChargeCount;				//チャージのカウント
	CEnemyBullet* m_pBullet;		//弾のポインタ
	CEffect_ChargeShot* m_pEffect;	//エフェクトのポインタ
};

//==========================
//エネミー002の演出
//==========================
class CEnemyAction_Direction : public CEnemyAction
{
public:

	static constexpr int DIRECTION_TIME{ 300 };	//演出の時間

	//コンストラクタ
	CEnemyAction_Direction() {};
	CEnemyAction_Direction(CEnemy* enemy);

	void Action(CEnemy* enemy) override;	//演出

	//追いかけるアクションを設定
	void NextAction(CEnemy* enemy) override
	{
		SetNextAction(new CEnemyAction_Standby(enemy));
	}

private:
	int m_nCount;	//カウント用
};

#endif