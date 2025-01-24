//================================
//
//状態に応じた処理を実行[state_player_death.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "state_player_death.h"
#include "game.h"
#include "manager.h"
#include "state_player_normal.h"

//====================================
//コンストラクタ
//====================================
CState_Player_Death::CState_Player_Death(CPlayer* player)
{
	//死亡モーション
	player->SetMotion(CPlayer::PLAYERMOTION_DEATH);
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());
	pGame->SetGameOver(true);
}

//====================================
//状態の更新
//====================================
void CState_Player_Death::UpdateState(CPlayer* player)
{
	
}

//========================
//ダメージの設定
//========================
bool CState_Player_Death::SetDamage(CPlayer* player, int damage, float angle)
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