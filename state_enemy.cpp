//================================
//
//状態に応じた処理を実行[state_enemy.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "state_enemy.h"
#include "game.h"
#include "manager.h"
#include "state_enemy_normal.h"

//====================================
//デストラクタ
//====================================
CState_Enemy::~CState_Enemy()
{
	//アクションの破棄
	if (m_pAction != nullptr)
	{
		delete m_pAction;
		m_pAction = nullptr;
	}

	//次の状態を破棄
	if (m_pNextState != nullptr)
	{
		//delete m_pNextState;
		m_pNextState = nullptr;
	}
}

//====================================
//更新処理
//====================================
void CState_Enemy::Update(CEnemy* enemy)
{
	//アクションの更新
	UpdateAction(enemy);

	//状態カウントの更新
	UpdateState(enemy);
}

//====================================
//アクション処理
//====================================
void CState_Enemy::UpdateAction(CEnemy*& enemy)
{
	//アクションの更新
	if (m_pAction != nullptr)
	{
		//派生先のアクションを実行
		m_pAction->Action(enemy);

		//次のアクションがあるなら変更
		if (m_pAction->GetNextAction() != nullptr)
		{
			//次のアクションに変更
			CEnemyAction* pNext = m_pAction->GetNextAction();
			delete m_pAction;
			m_pAction = nullptr;

			//代入
			m_pAction = pNext;
		}
	}
}

//====================================
//状態更新処理
//====================================
void CState_Enemy::UpdateState(CEnemy* enemy)
{
	//メンバ変数の取得
	float fEndTime{ GetEndTime() };	//終了時間
	float fCount{ GetStateCount() };//カウントの取得

	//カウントアップ
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();	//ゲームシーンの取得
	fCount += pGame->GetTime()->GetValue<float>(1.0f);			//時間に応じてカウントアップ

	//カウントが周り切ったら状態を切り替える
	if (fCount >= fEndTime)
	{
		//次の状態を設定
		if (m_pNextState == nullptr)
		{
			m_pNextState = new CState_Enemy_Normal();
		}
	}
}