//================================
//
//吹き飛び状態処理を実行[state_enemy_blow.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "state_enemy_blow.h"
#include "state_enemy_normal.h"
#include "game.h"
#include "manager.h"

//====================================
//コンストラクタ
//====================================
CState_Enemy_Blow::CState_Enemy_Blow()
{
	//初期アクション
	SetAction(new CEnemyAction());
}

//====================================
//状態更新処理
//====================================
void CState_Enemy_Blow::UpdateState(CEnemy* enemy)
{
	//減衰後に移動量を加算

	//ゲームシーンの取得
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

	//壁に触れていたら
	if (pGame->GetWall()->GetHit(enemy->GetPos(), enemy->GetSizeRadius()))
	{
		enemy->ChangeStickState();

		//カメラを揺らす
		CManager::GetInstance()->GetCamera()->SetShake(5, 15);	//ヒット時カメラを揺らす
	}

	//カウントが周り切ったら状態を切り替える
	if (enemy->GetOnStand())
	{
		//次の状態を設定
		if (GetNextState() == nullptr)
		{
			//状態の設定
			enemy->StateReset();
		}
	}
}