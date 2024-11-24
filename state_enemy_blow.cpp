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
	//ゲームシーンの取得
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

	//壁に触れていたら
	if (pGame->GetWall()->GetHit(enemy->GetPos(), enemy->GetSizeRadius()))
	{
		enemy->ChangeStickState();

		//カメラを揺らす
		CManager::GetInstance()->GetCamera()->SetShake(5, 15);	//ヒット時カメラを揺らす
	}

	//各ギミックとの当たり判定
	for (auto& iter : pGame->GetGimmickManager()->GetList())
	{
		//位置の取得
		D3DXVECTOR3 Pos = iter->GetCollision()->GetPos();
		D3DXVECTOR3 EnemyPos = enemy->GetCollision()->GetPos();

		//距離を計算
		float fLength = sqrtf((EnemyPos.x - Pos.x) * (EnemyPos.x - Pos.x) + (EnemyPos.z - Pos.z) * (EnemyPos.z - Pos.z));

		//範囲内の確認
		if (fLength < iter->GetCollision()->GetRadius() + enemy->GetCollision()->GetRadius())
		{
			iter->Uninit();
		}
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