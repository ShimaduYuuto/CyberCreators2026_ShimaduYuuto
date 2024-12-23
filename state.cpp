//================================
//
//状態に応じた処理を実行[state.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "state.h"
#include "game.h"
#include "manager.h"

//====================================
//モーションの処理
//====================================
void CState::Motion(CGame_Character* character)
{
	//モーションの更新
	character->UpdateMotion();
}

//====================================
//ギミックとの当たり判定
//====================================
void CState::UpdateGimmickCollison(CGame_Character* character)
{
	//ゲームシーンの取得
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//各ギミックとの当たり判定
	for (auto& iter : pGame->GetGimmickManager()->GetList())
	{
		//位置の取得
		D3DXVECTOR3 GimmickPos = iter->GetCollision()->GetPos();
		D3DXVECTOR3 CharacterPos = character->GetCollision()->GetPos();

		//距離を計算
		float fLength = sqrtf((CharacterPos.x - GimmickPos.x) * (CharacterPos.x - GimmickPos.x) + (CharacterPos.z - GimmickPos.z) * (CharacterPos.z - GimmickPos.z));
		float fTotalRadius = iter->GetCollision()->GetRadius() + character->GetCollision()->GetRadius();
		float fHeightLength = CharacterPos.y - GimmickPos.y;

		//高さの距離を絶対値に変更
		if (fHeightLength < 0.0f) { fHeightLength *= -1.0f; }

		//範囲内の確認
		if (fLength < fTotalRadius && fHeightLength < fTotalRadius)
		{
			//樽の当たらない位置に補正
			float fAngle = atan2f(GimmickPos.x - CharacterPos.x, GimmickPos.z - CharacterPos.z);//対角線の角度を算出

			//位置の設定
			character->SetPos(D3DXVECTOR3(sinf(fAngle + D3DX_PI) * fTotalRadius + GimmickPos.x,
				character->GetPos().y,
				cosf(fAngle + D3DX_PI) * fTotalRadius + GimmickPos.z));
		}
	}
}