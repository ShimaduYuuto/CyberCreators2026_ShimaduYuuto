//================================
//
//状態に応じた処理を実行[state_enemy_damage.cpp]
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
	//初期アクション
	enemy->SetEnableGravity(true);
	enemy->SetCollisionProcess(true);
}

//====================================
//状態更新処理
//====================================
void CState_Enemy_Normal::UpdateState(CEnemy* enemy)
{
	//ゲームシーンの取得
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

	//他の敵との当たり判定
	if (enemy->GetCollisionProcess())
	{
		EnemyCollision(enemy);
	}

	//ギミックとの当たり判定
	UpdateGimmickCollison(enemy);
}