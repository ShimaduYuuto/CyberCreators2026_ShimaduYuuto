//================================
//
//behavior_enemy.cppに必要な宣言[behavior_enemy.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BEHAVIOR_ENEMY_H_ //このマクロ定義がされていなかったら
#define _BEHAVIOR_ENEMY_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "behavior_character.h"
#include "enemy.h"

//前方宣言
class CEnemy;

//==========================
//エネミーアクション基底クラス
//==========================
class CEnemyBehavior
{
public:

	//初期化
	CEnemyBehavior() : m_pNextAction(nullptr) {}
	virtual ~CEnemyBehavior() {}

	//アクションの基底
	virtual void Action(CEnemy* enemy) {}

	//次のアクション
	void SetNextAction(CEnemyBehavior* action) { m_pNextAction = action; }
	CEnemyBehavior* GetNextAction() { return m_pNextAction; }

	//次のアクションを確定する
	virtual void NextAction(CEnemy* enemy) {}	//基底の関数

private:
	CEnemyBehavior* m_pNextAction;
};

//==========================
//追いかける
//==========================
class CEnemyBehavior_Chase : public CEnemyBehavior
{
public:
	//定数
	static constexpr float VALUE_MOVE = 1.0f;			//移動量
	static constexpr float LENGTH_CHANGEATTACK = 35.0f;	//攻撃する距離

	CEnemyBehavior_Chase(CEnemy* enemy);	//コンストラクタ

	void Action(CEnemy* enemy) override;	//アクション

	//次の行動を確定
	void NextAction(CEnemy* enemy) override {}
};

//==========================
//攻撃
//==========================
class CEnemyBehavior_Attack : public CEnemyBehavior
{
public:

	//定数
	static constexpr float POS_LENGTH{ 20.0f };	//攻撃の発生する距離

	//コンストラクタとデストラクタ
	CEnemyBehavior_Attack(CEnemy* enemy);
	~CEnemyBehavior_Attack();

	//攻撃処理
	void Action(CEnemy* enemy) override;

	//攻撃のインスタンス
	void SetAttackInstance(CAttack* attack) { m_pAttack = attack; }	//設定
	CAttack*& GetAttackInstanse() { return m_pAttack; }				//取得

	//攻撃の距離
	void SetAttackLength(float length) { m_fAttackLength = length; }	//設定
	float GetAttackLength() { return m_fAttackLength; }					//取得

private:

	void CheckCollision(CEnemy* enemy);	//当たり判定の確認
	bool IsCheckCollision();			//当たり判定の処理を行うか
	void HitPlayer(float angle);		//プレイヤーにヒットした際の処理


	//基本の攻撃クラスと敵専用変数
	CAttack* m_pAttack;		//攻撃のインスタンス
	float m_fAttackLength;	//攻撃の距離
};
#endif