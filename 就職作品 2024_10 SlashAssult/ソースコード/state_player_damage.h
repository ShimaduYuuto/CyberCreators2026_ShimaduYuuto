//================================
//
//state_player_damage.cppに必要な宣言[state_player_damage.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_PLAYER_DAMAGE_H_ //このマクロ定義がされていなかったら
#define _STATE_PLAYER_DAMAGE_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "state_player.h"

//ステートクラス
class CState_Player_Damage : public CState_Player
{
public:

	//定数
	static constexpr int END_TIME{ 30 };	//終了時間

	//メンバ関数
	CState_Player_Damage(CPlayer* player);	//コンストラクタ
	~CState_Player_Damage() {};				//デストラクタ

	//状態ごとの更新
	void UpdateState(CPlayer* player) override;				//状態の更新
};

#endif