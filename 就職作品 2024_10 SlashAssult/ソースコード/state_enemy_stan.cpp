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
CState_Enemy_Stan::CState_Enemy_Stan(CEnemy* enemy) : CState_Enemy(enemy)
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
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());	//ゲームシーンの取得
	fCount += pGame->GetTime()->GetValue<float>(1.0f);							//時間に応じてカウントアップ

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