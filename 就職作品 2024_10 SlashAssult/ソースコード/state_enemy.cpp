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
		//次のアクションも破棄
		if (m_pAction->GetNextAction() != nullptr)
		{
			CEnemyBehavior* pNext = m_pAction->GetNextAction();
			delete pNext;
			pNext = nullptr;
		}
		
		delete m_pAction;
		m_pAction = nullptr;
	}

	//次の状態を破棄
	if (m_pNextState != nullptr)
	{
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
			CEnemyBehavior* pNext = m_pAction->GetNextAction();
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
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());	//ゲームシーンの取得
	fCount += pGame->GetTime()->GetValue<float>(1.0f);							//時間に応じてカウントアップ

	//カウントが周り切ったら状態を切り替える
	if (fCount >= fEndTime)
	{
		//次の状態を設定
		if (m_pNextState == nullptr)
		{
			m_pNextState = new CState_Enemy_Normal(enemy);
		}
	}
}

//====================================
//エネミー同士の当たり判定
//====================================
void CState_Enemy::EnemyCollision(CEnemy* enemy)
{
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());	//ゲームシーンの取得
	CEnemyManager* pManager = pGame->GetEnemyManager();							//エネミーマネージャーの取得

	//他の敵との当たり判定
	for (auto& itr : pManager->GetList())
	{
		//自分自身なら飛ばす
		if (itr == enemy)
		{
			continue;
		}

		//位置の取得
		D3DXVECTOR3 Pos = itr->GetCollision()->GetPos();
		D3DXVECTOR3 EnemyPos = enemy->GetCollision()->GetPos();

		//距離を計算
		float fLength = sqrtf((EnemyPos.x - Pos.x) * (EnemyPos.x - Pos.x) + (EnemyPos.z - Pos.z) * (EnemyPos.z - Pos.z));
		float fTotalRadius = itr->GetCollision()->GetRadius() + enemy->GetCollision()->GetRadius();

		//範囲内の確認
		if (fLength < fTotalRadius)
		{
			//敵の当たらない位置に補正
			float fAngle = atan2f(Pos.x - EnemyPos.x, Pos.z - EnemyPos.z);//対角線の角度を算出

			//位置を設定
			enemy->SetPos(D3DXVECTOR3(sinf(fAngle + D3DX_PI) * fTotalRadius + Pos.x,
				enemy->GetPos().y,
				cosf(fAngle + D3DX_PI) * fTotalRadius + Pos.z));
		}
	}
}