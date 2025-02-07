//================================
//
//state_player.cppに必要な宣言[state_player.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_PLAYER_H_ //このマクロ定義がされていなかったら
#define _STATE_PLAYER_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "state.h"
#include "player.h"
#include "behavior_player.h"

//前方宣言
class CPlayer;
class CPlayerBehavior;

//ステートクラス
class CState_Player : public CState
{
public:

	//メンバ関数
	CState_Player() : m_pBehavior(nullptr), m_pNextState(nullptr){};					//コンストラクタ
	CState_Player(CPlayer* player) : m_pBehavior(nullptr), m_pNextState(nullptr) {};	//コンストラクタ
	~CState_Player();																	//デストラクタ

	//状態ごとの更新
	virtual void Update(CPlayer* player);					//更新
	virtual bool SetDamage(CPlayer* player, int damage, float angle);	//ダメージの設定

	//アクション
	void SetBehavior(CPlayerBehavior* behavior);							//設定
	CPlayerBehavior* GetBehavior() { return m_pBehavior; }					//取得

	//次の状態
	void SetNextState(CState_Player* state) { if (m_pNextState == nullptr) { m_pNextState = state; } };	//設定
	CState_Player* GetNextState() { return m_pNextState; }												//取得

	//行動の更新
	virtual void UpdateBehavior(CPlayer* player);	

private:

	//状態とアクションの更新
	virtual void UpdateState(CPlayer* player);		//状態の更新

	//インスタンス
	CPlayerBehavior* m_pBehavior;	//行動
	CState_Player* m_pNextState;	//次の状態
};

#endif