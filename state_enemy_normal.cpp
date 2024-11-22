//================================
//
//状態に応じた処理を実行[state_enemy_damage.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "state_enemy_damage.h"
#include "state_enemy_normal.h"
#include "game.h"
#include "manager.h"

//====================================
//コンストラクタ
//====================================
CState_Enemy_Normal::CState_Enemy_Normal(CEnemy* enemy)
{
	//初期アクション
	enemy->SetEnableGravity(true);
}