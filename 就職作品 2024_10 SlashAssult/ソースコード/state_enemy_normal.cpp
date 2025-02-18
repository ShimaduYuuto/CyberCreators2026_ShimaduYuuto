//================================
//
//通常状態処理を実行[state_enemy_damage.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "state_enemy_normal.h"
#include "game.h"
#include "manager.h"

//====================================
//コンストラクタ
//====================================
CState_Enemy_Normal::CState_Enemy_Normal(CEnemy* enemy)
{
	//設定
	enemy->SetEnableGravity(true);		//重力の影響を受ける
	enemy->SetCollisionProcess(true);	//当たり判定を行う
}

//====================================
//状態更新処理
//====================================
void CState_Enemy_Normal::UpdateState(CEnemy* enemy)
{
	//他の敵との当たり判定
	if (enemy->GetCollisionProcess())
	{
		EnemyCollision(enemy);
	}

	//ギミックとの当たり判定
	UpdateGimmickCollison(enemy);
}