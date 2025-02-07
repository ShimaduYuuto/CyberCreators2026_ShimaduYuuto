//================================
//
//エネミー003の状態処理[state_enemy003.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "state_enemy003.h"
#include "game.h"
#include "manager.h"

//===============================================
//通常状態
//===============================================

//====================================
//ギミックとの当たり判定
//====================================
void CState_Enemy003_Normal::UpdateGimmickCollison(CGame_Character* character)
{
	//ゲームシーンの取得
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//各ギミックとの当たり判定
	for (auto& iter : pGame->GetGimmickManager()->GetList())
	{
		//位置の取得
		D3DXVECTOR3 GimmickPos = iter->GetCollision()->GetPos();
		D3DXVECTOR3 EnemyPos = character->GetCollision()->GetPos();

		//距離を計算
		float fLength = sqrtf((EnemyPos.x - GimmickPos.x) * (EnemyPos.x - GimmickPos.x) + (EnemyPos.z - GimmickPos.z) * (EnemyPos.z - GimmickPos.z));
		float fTotalRadius = iter->GetCollision()->GetRadius() + character->GetCollision()->GetRadius();

		//範囲内の確認
		if (fLength < fTotalRadius)
		{
			//エネミー003にキャスト(ダウンキャストなので微妙)
			CEnemy003* pEnemy003 = dynamic_cast<CEnemy003*>(character);

			//攻撃中ならギミックが起動
			if (pEnemy003->GetAttacking())
			{
				iter->GimmickActivation();
			}
			else
			{
				//樽の当たらない位置に補正
				float fAngle = atan2f(GimmickPos.x - EnemyPos.x, GimmickPos.z - EnemyPos.z);//対角線の角度を算出

				//位置の設定
				character->SetPos(D3DXVECTOR3(sinf(fAngle + D3DX_PI) * fTotalRadius + GimmickPos.x,
					character->GetPos().y,
					cosf(fAngle + D3DX_PI) * fTotalRadius + GimmickPos.z));
			}
		}
	}
}