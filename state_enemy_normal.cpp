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
}

//====================================
//状態更新処理
//====================================
void CState_Enemy_Normal::UpdateState(CEnemy* enemy)
{
	//ゲームシーンの取得
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

	//他の敵との当たり判定
	EnemyCollision(enemy);

	//各ギミックとの当たり判定
	for (auto& iter : pGame->GetGimmickManager()->GetList())
	{
		//位置の取得
		D3DXVECTOR3 Pos = iter->GetCollision()->GetPos();
		D3DXVECTOR3 EnemyPos = enemy->GetCollision()->GetPos();

		//距離を計算
		float fLength = sqrtf((EnemyPos.x - Pos.x) * (EnemyPos.x - Pos.x) + (EnemyPos.z - Pos.z) * (EnemyPos.z - Pos.z));
		float fTotalRadius = iter->GetCollision()->GetRadius() + enemy->GetCollision()->GetRadius();

		//範囲内の確認
		if (fLength < fTotalRadius)
		{
			//樽の当たらない位置に補正
			float fAngle = atan2f(Pos.x - EnemyPos.x, Pos.z - EnemyPos.z);//対角線の角度を算出

			//円の内側に補正
			enemy->SetPos(D3DXVECTOR3(sinf(fAngle + D3DX_PI) * fTotalRadius + Pos.x,
				enemy->GetPos().y,
				cosf(fAngle + D3DX_PI) * fTotalRadius + Pos.z));
		}
	}
}