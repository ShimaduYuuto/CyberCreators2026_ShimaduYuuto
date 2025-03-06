//================================
//
//ダメージ状態処理を実行[state_enemy_damage.cpp]
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
CState_Enemy_Damage::CState_Enemy_Damage(CEnemy* enemy) : CState_Enemy(enemy)
{
	//設定
	SetAction(new CEnemyBehavior);		//空のアクション
	enemy->SetCollisionProcess(true);	//当たり判定を行う
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
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());	//ゲームシーンの取得
	fCount++;																	//時間に応じてカウントアップ

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