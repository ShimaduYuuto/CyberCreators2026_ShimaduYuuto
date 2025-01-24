//================================
//
//state_player_counter.cppに必要な宣言[state_player_counter.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_PLAYER_COUNTER_H_ //このマクロ定義がされていなかったら
#define _STATE_PLAYER_COUNTER_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "state_player.h"

//カウンターステートクラス
class CState_Player_Counter : public CState_Player
{
public:

	//定数
	static constexpr int TIME_COUNTER{ 30 };	//カウンターを受け付ける時間
	static constexpr int TIME_END{ 60 };		//状態の時間

	//メンバ関数
	CState_Player_Counter(CPlayer* player) : m_bCounter(true), m_bActivationCounter(false)
	{
		SetBehavior(new CPlayerBehavior(player));
		SetEndTime(TIME_END);
		player->SetMotion(15);
	};	//コンストラクタ
	~CState_Player_Counter() {};				//デストラクタ

	void UpdateState(CPlayer* player) override;				//状態の更新
	bool SetDamage(CPlayer* player, int damage, float angle) override;	//ダメージの設定

private:

	bool m_bCounter;			//カウンター可能か
	bool m_bActivationCounter;	//カウンターが発動したか
};

#endif