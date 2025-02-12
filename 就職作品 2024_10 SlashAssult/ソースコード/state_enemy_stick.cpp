//================================
//
//状態に応じた処理を実行[state_enemy_stick.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "state_enemy_stick.h"
#include "state_enemy_normal.h"
#include "game.h"
#include "manager.h"

//====================================
//コンストラクタ
//====================================
CState_Enemy_Stick::CState_Enemy_Stick(CEnemy* enemy)
{
	//設定
	SetAction(new CEnemyBehavior());									//空の行動
	SetEndTime(END_TIME);												//終了時間
	enemy->SetEnableGravity(false);										//重力を受けない
	enemy->SetBlowValue({ 0.0f, 0.0f, 0.0f });							//吹き飛ぶ量を無くす
	enemy->SetMove({ enemy->GetMove().x, 0.0f, enemy->GetMove().z });	//移動量
	enemy->SetEnteredStick(true);										//張り付き判定にする

	//ゲームの処理
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());	//ゲームシーンの取得
	pGame->SetLockon(true);														//ロックオンを設定
	pGame->GetLockon()->Regist(enemy);											//ロックオン対象に登録

	//効果音
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_STICK);
}

//====================================
//状態更新処理
//====================================
void CState_Enemy_Stick::UpdateState(CEnemy* enemy)
{
	//メンバ変数の取得
	float fEndTime{ GetEndTime() };	//終了時間
	float fCount{ GetStateCount() };//カウントの取得

	//カウントアップ
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());	//ゲームシーンの取得
	fCount += pGame->GetTime()->GetValue<float>(1.0f);							//時間に応じてカウントアップ

	//カウントが周り切ったら状態を切り替える
	if (fCount >= fEndTime)
	{
		//次の状態を設定
		if (GetNextState() == nullptr)
		{
			//状態のリセット
			enemy->StateReset();
			enemy->SetEnteredStick(false);
			pGame->GetLockon()->Erase(enemy);
		}
	}

	//カウントの設定
	SetStateCount(fCount);
}