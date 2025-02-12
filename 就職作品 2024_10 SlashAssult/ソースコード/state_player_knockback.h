//================================
//
//state_player_knockback.cppに必要な宣言[state_player_knockback.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_PLAYER_KNOCKBACK_H_ //このマクロ定義がされていなかったら
#define _STATE_PLAYER_KNOCKBACK_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "state_player.h"

//ステートクラス
class CState_Player_Knockback : public CState_Player
{
public:

	//ノックバックの時間
	static const int TIME_KNOCKBACK = 30;

	//メンバ関数
	CState_Player_Knockback() : m_nKnockbackCount(TIME_KNOCKBACK){};					//コンストラクタ
	CState_Player_Knockback(CPlayer* player) : m_nKnockbackCount(TIME_KNOCKBACK)
	{
		SetBehavior(new CPlayerBehavior(player));
		SetEndTime(TIME_KNOCKBACK);
	};	//コンストラクタ
	~CState_Player_Knockback() {};	//デストラクタ

	//状態の更新
	void UpdateState(CPlayer* player) override;	
	//bool SetDamage(CPlayer* player, int damage, float angle) override;	//ダメージの設定

private:

	//変数
	int m_nKnockbackCount;
};

#endif