//================================
//
//state_player_normal.cppに必要な宣言[state_player_normal.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_PLAYER_NORMAL_H_ //このマクロ定義がされていなかったら
#define _STATE_PLAYER_NORMAL_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "state_player.h"

//ノーマルステートクラス
class CState_Player_Normal : public CState_Player
{
public:

	//メンバ関数
	CState_Player_Normal() {};					//コンストラクタ
	CState_Player_Normal(CPlayer* player) 
	{
		//中身がないなら移動を設定
		if (GetBehavior() == nullptr)
		{
			SetBehavior(new CPlayerBehavior_Move(player));
		}
		
	};	//コンストラクタ
	~CState_Player_Normal() {};					//デストラクタ

	void UpdateState(CPlayer* player) override {};			//状態の更新
	//bool SetDamage(CPlayer* player, int damage, float angle) override;	//ダメージの設定
};

#endif