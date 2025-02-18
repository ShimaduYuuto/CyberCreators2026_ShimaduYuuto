//================================
//
//状態に応じた処理を実行[state_player_knockback.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "state_player_knockback.h"
#include "state_player_normal.h"
#include "state_player_damage.h"
#include "manager.h"

//====================================
//状態の更新
//====================================
void CState_Player_Knockback::UpdateState(CPlayer* player)
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
			SetNextState(new CState_Player_Normal(player));
		}
	}

	//状態の設定
	SetStateCount(fCount);
}