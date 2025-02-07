//================================
//
//state_player_invincible.cppに必要な宣言[state_player_invincible.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_PLAYER_INVINCIBLE_H_ //このマクロ定義がされていなかったら
#define _STATE_PLAYER_INVINCIBLE_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "state_player.h"

//ステートクラス
class CState_Player_Invincible : public CState_Player
{
public:

	//ノックバックの時間
	static constexpr int TIME_INVINCIBLE{ 90 };	//無敵時間

	//メンバ関数
	CState_Player_Invincible() {};					//コンストラクタ
	CState_Player_Invincible(CPlayer* player)
	{
		SetBehavior(new CPlayerBehavior_Move(player));
		SetEndTime(TIME_INVINCIBLE);
	};	//コンストラクタ
	~CState_Player_Invincible() {};					//デストラクタ

	//状態の更新
	void UpdateState(CPlayer* player) override;
	bool SetDamage(CPlayer* player, int damage, float angle) override;	//ダメージの設定

private:
};

#endif