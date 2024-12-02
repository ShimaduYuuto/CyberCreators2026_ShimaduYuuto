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
//追いかける
//==========================
class CEnemyAction_Chase001 : public CEnemyAction_Chase
{
public:

	//コンストラクタ
	CEnemyAction_Chase001() {};
	CEnemyAction_Chase001(CEnemy* enemy);

	//定数
	static constexpr float VALUE_MOVE = 1.0f;	//移動量

	void Action(CEnemy* enemy) override
	{
		CEnemyAction_Chase::Action(enemy);
	};	//アクション

	//攻撃アクションを設定
	void NextAction(CEnemy* enemy) override;
};

//==========================
//エネミー001の攻撃処理
//==========================
class CEnemyAction_Attack001 : public CEnemyAction_Attack
{
public:

	//コンストラクタ
	CEnemyAction_Attack001() {};
	CEnemyAction_Attack001(CEnemy* enemy);

	void Action(CEnemy* enemy) override
	{
		CEnemyAction_Attack::Action(enemy);
	};	//攻撃

	//追いかけるアクションを設定
	void NextAction(CEnemy* enemy) override
	{
		SetNextAction(new CEnemyAction_Chase001(enemy));
	}
};

#endif