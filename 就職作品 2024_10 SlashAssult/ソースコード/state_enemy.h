//================================
//
//state_enemy.cppに必要な宣言[state_enemy.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_ENEMY_H_ //このマクロ定義がされていなかったら
#define _STATE_ENEMY_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "state.h"
#include "enemy.h"
#include "behavior_enemy.h"

//前方宣言
class CEnemy;
class CEnemyBehavior;

//エネミーステートクラス
class CState_Enemy : public CState
{
public:

	//メンバ関数
	CState_Enemy(CEnemy* enemy) : m_pAction(nullptr), m_pNextState(nullptr) {};	//コンストラクタ
	~CState_Enemy() override;													//デストラクタ

	//状態ごとの更新
	void Update(CEnemy* enemy);

	//エネミー同士の当たり判定
	void EnemyCollision(CEnemy* enemy);

	//ダメージの設定
	virtual void SetDamage(CEnemy* enemy, int damage) {}

	//アクションのインスタンス
	void SetAction(CEnemyBehavior* action) { if (m_pAction != nullptr) { return; }m_pAction = action; }	//設定
	CEnemyBehavior* GetAction() { return m_pAction; }					//取得

	//次の状態
	void SetNextState(CState_Enemy* state) { if (m_pNextState == nullptr) { m_pNextState = state; } };	//設定
	CState_Enemy* GetNextState() { return m_pNextState; }												//取得

private:

	//関数
	virtual void UpdateState(CEnemy* enemy);	//状態の更新
	void UpdateAction(CEnemy*& enemy);			//アクションの処理

	//変数
	CEnemyBehavior* m_pAction;	//アクション
	CState_Enemy* m_pNextState;	//次の状態
};

#endif