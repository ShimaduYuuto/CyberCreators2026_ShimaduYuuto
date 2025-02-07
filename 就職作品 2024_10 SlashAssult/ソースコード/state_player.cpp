//================================
//
//状態に応じた処理を実行[state_player.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "state_player.h"
#include "state_player_normal.h"

//====================================
//デストラクタ
//====================================
CState_Player::~CState_Player()
{
	//行動インスタンスの破棄
	if (m_pBehavior != nullptr)
	{
		delete m_pBehavior;
		m_pBehavior = nullptr;
	}
}

//====================================
//状態に応じた更新処理
//====================================
void CState_Player::Update(CPlayer* player)
{
	//アクションの更新
	UpdateBehavior(player);

	//状態カウントの更新
	UpdateState(player);
}

//====================================
//行動の更新
//====================================
void CState_Player::UpdateBehavior(CPlayer* player)
{
	//アクションの更新
	if (m_pBehavior != nullptr)
	{
		//派生先のアクションを実行
		m_pBehavior->Behavior(player);

		//次のアクションがあるなら変更
		if (m_pBehavior->GetNextBehavior() != nullptr)
		{
			//次のアクションに変更
			CPlayerBehavior* pNext = m_pBehavior->GetNextBehavior();
			delete m_pBehavior;
			m_pBehavior = nullptr;

			//代入
			m_pBehavior = pNext;
		}
	}
}

//====================================
//状態更新処理
//====================================
void CState_Player::UpdateState(CPlayer* player)
{
	//メンバ変数の取得
	float fEndTime{ GetEndTime() };	//終了時間
	float fCount{ GetStateCount() };//カウントの取得

	//カウントアップ
	fCount++;

	//カウントが周り切ったら状態を切り替える
	if (fCount >= fEndTime)
	{
		//次の状態を設定
		if (m_pNextState == nullptr)
		{
			//通常状態に移行
			m_pNextState = new CState_Player_Normal(player);
		}
	}
}

//====================================
//行動の設定
//====================================
void CState_Player::SetBehavior(CPlayerBehavior* behavior)
{
	//中身があるなら消去	//消した方が良いがnullで上書きできない
	//SafeDelete(m_pBehavior);
	m_pBehavior = behavior;
}

//========================
//ダメージの設定
//========================
bool CState_Player::SetDamage(CPlayer* player, int damage, float angle)
{
	return true;
}