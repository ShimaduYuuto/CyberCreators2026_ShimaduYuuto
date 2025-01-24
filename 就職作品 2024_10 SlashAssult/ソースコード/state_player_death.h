//================================
//
//state_player_death.cppに必要な宣言[state_player_death.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_PLAYER_DEATH_H_ //このマクロ定義がされていなかったら
#define _STATE_PLAYER_DEATH_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "state_player.h"

//ステートクラス
class CState_Player_Death : public CState_Player
{
public:

	//メンバ関数
	CState_Player_Death(CPlayer* player);
	/*{
		SetEndTime(30);
	};	*///コンストラクタ
	~CState_Player_Death() {};					//デストラクタ

	//状態ごとの更新
	void UpdateState(CPlayer* player) override;				//状態の更新
	bool SetDamage(CPlayer* player, int death, float angle) override;	//ダメージの設定
};

#endif