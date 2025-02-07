//================================
//
//状態に応じた処理を実行[state_enemy_stan.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "state_enemy_stan.h"
#include "state_enemy_normal.h"
#include "game.h"
#include "manager.h"

//====================================
//コンストラクタ
//====================================
CState_Enemy_Stan::CState_Enemy_Stan()
{
	//初期アクション
	SetAction(new CEnemyBehavior);
}

//====================================
//状態更新処理
//====================================
void CState_Enemy_Stan::UpdateState(CEnemy* enemy)
{
	//メンバ変数の取得
	float fEndTime{ GetEndTime() };	//終了時間
	float fCount{ GetStateCount() };//カウントの取得

	//カウントアップ
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();	//ゲームシーンの取得
	fCount += pGame->GetTime()->GetValue<float>(1.0f);			//時間に応じてカウントアップ

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

	//カウントが周り切ったら状態を切り替える
	if (fCount >= fEndTime)
	{
		//次の状態を設定
		if (GetNextState() == nullptr)
		{
			//状態の設定
			enemy->StateReset();
		}
	}

	//カウントの設定
	SetStateCount(fCount);
}