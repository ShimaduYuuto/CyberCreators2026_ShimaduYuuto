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
class CEnemyBehavior_Chase001 : public CEnemyBehavior_Chase
{
public:

	//定数
	static constexpr float VALUE_MOVE = 1.0f;	//移動量

	//関数
	CEnemyBehavior_Chase001(CEnemy* enemy);	//コンストラクタ
	void Action(CEnemy* enemy) override;	//アクション
	void NextAction(CEnemy* enemy) override;//攻撃アクションを設定
};

//==========================
//エネミー001の攻撃処理
//==========================
class CEnemyBehavior_Attack001 : public CEnemyBehavior_Attack
{
public:

	//定数
	static constexpr float START_COLLISON_TIME{ 45.0f };	//当たり判定が出始めるフレーム
	static constexpr float END_TIME{ 100.0f };				//攻撃が終了するフレーム
	static constexpr int DAMAGE_VALUE{ 1 };					//与えるダメージ量
	static constexpr float ATTACK_LENGTH{ 50.0f };			//攻撃が発生する距離

	//関数
	CEnemyBehavior_Attack001(CEnemy* enemy);		//コンストラクタ
	void Action(CEnemy* enemy) override;		//攻撃
	void NextAction(CEnemy* enemy) override;	//追いかけるアクションを設定
};

#endif