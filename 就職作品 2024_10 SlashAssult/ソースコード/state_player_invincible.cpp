//================================
//
//状態に応じた処理を実行[state_player_invincible.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "state_player_invincible.h"
#include "state_player_normal.h"
#include "manager.h"

//====================================
//状態の更新
//====================================
void CState_Player_Invincible::UpdateState(CPlayer* player)
{	
	//メンバ変数の取得
	float fEndTime{ GetEndTime() };	//終了時間
	float fCount{ GetStateCount() };//カウントの取得

	//カウントアップ
	fCount++;

	//α値の変化させて点滅させる
	ChangeAlpha(player, (int)(fCount));

	//カウントが周り切ったら状態を切り替える
	if (fCount >= fEndTime)
	{
		//次の状態を設定
		if (GetNextState() == nullptr)
		{
			//パーツ数だけ周回
			for (auto itr : player->GetModelPartsVector())
			{
				itr->SetAlpha(1.0f);
			}

			//通常状態に移行
			SetNextState(new CState_Player_Normal(player));	//通常状態を設定
			GetNextState()->SetBehavior(GetBehavior());		//現在の行動を次の状態に設定
			SetBehavior(nullptr);							//ポインタ変数をnullptrに設定
		}
	}

	//状態の設定
	SetStateCount(fCount);
}

//========================
//ダメージの設定
//========================
bool CState_Player_Invincible::SetDamage(CPlayer* player, int damage, float angle)
{
	//体力がないなら更新しない
	if (player->GetLife() <= 0)
	{
		return false;
	}

	//死亡フラグが立っていたら抜ける
	if (player->GetDeath())
	{
		return true;
	}

	return true;
}

//========================
//α値の変更
//========================
void CState_Player_Invincible::ChangeAlpha(CPlayer* player, int count)
{
	//変数
	float fAlpha = 0.0f;	//変更するα値

	//点滅させる
	if ((count & 1) == 0) //偶数
	{
		//α値を代入
		fAlpha = ALPHA_EVEN;
	}
	else //奇数
	{
		//α値を代入
		fAlpha = ALPHA_ODD;
	}

	//パーツ数だけ周回
	for (auto itr : player->GetModelPartsVector())
	{
		itr->SetAlpha(ALPHA_EVEN);
	}
}