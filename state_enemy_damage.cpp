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
CState_Enemy_Damage::CState_Enemy_Damage(CEnemy* enemy)
{
	//初期アクション
	SetAction(new CEnemyAction);
	enemy->SetCollisionProcess(true);
}

//====================================
//状態更新処理
//====================================
void CState_Enemy_Damage::UpdateState(CEnemy* enemy)
{
	//メンバ変数の取得
	float fEndTime{ GetEndTime() };	//終了時間
	float fCount{ GetStateCount() };//カウントの取得

	//カウントアップ
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();	//ゲームシーンの取得
	fCount += pGame->GetTime()->GetValue<float>(1.0f);			//時間に応じてカウントアップ

	//他の敵との当たり判定
	EnemyCollision(enemy);

	//ギミックとの当たり判定
	UpdateGimmickCollison(enemy);

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