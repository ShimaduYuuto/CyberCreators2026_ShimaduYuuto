//================================
//
//状態に応じた処理を実行[state_player_damage.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "state_player_damage.h"
#include "state_player_invincible.h"

//====================================
//コンストラクタ
//====================================
CState_Player_Damage::CState_Player_Damage(CPlayer* player)
{
	//設定
	SetEndTime(END_TIME);			//終了時間
	player->SetEnableGravity(true);	//重力を受ける
};

//====================================
//状態の更新
//====================================
void CState_Player_Damage::UpdateState(CPlayer* player)
{
	//メンバ変数の取得
	float fEndTime{ GetEndTime() };	//終了時間
	float fCount{ GetStateCount() };//カウントの取得

	//カウントアップ
	fCount++;

	//カウントが周り切ったら状態を切り替える
	if (fCount >= fEndTime)
	{
		//次の状態を設定
		if (GetNextState() == nullptr)
		{
			//通常状態に移行
			SetNextState(new CState_Player_Invincible(player));
		}
	}

	//カウントの更新
	SetStateCount(fCount);
}