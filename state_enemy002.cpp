//================================
//
//エネミー002の状態処理[state_enemy002.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "state_enemy002.h"

//===============================================
//通常状態
//===============================================

//====================================
//コンストラクタ
//====================================
CState_Enemy002_Normal::CState_Enemy002_Normal(CEnemy* enemy) : CState_Enemy_Normal(enemy)
{
	SetAction(new CEnemyAction_Standby(enemy));
};	

//===============================================
//スタン状態
//===============================================

//====================================
//コンストラクタ
//====================================
CState_Enemy002_Stan::CState_Enemy002_Stan(CEnemy* enemy) : m_pStanEffect(nullptr)
{
	SetAction(new CEnemyAction());
	enemy->SetMotion(5);
	SetEndTime(3000);
	m_pStanEffect = CEffect_Stan::Create({ 0.0f, 40.0f, 0.0f }, &enemy->GetModelParts(1)->GetMtx());
}

//====================================
//デストラクタ
//====================================
CState_Enemy002_Stan::~CState_Enemy002_Stan()
{
	if (m_pStanEffect != nullptr)
	{
		m_pStanEffect->Uninit();
		m_pStanEffect = nullptr;
	}
}

//===============================================
//演出状態
//===============================================

//====================================
//コンストラクタ
//====================================
CState_Enemy002_Direction::CState_Enemy002_Direction(CEnemy* enemy) : m_nCount(0)
{
	SetAction(new CEnemyAction_Direction(enemy));
	enemy->SetMotion(6);
	SetEndTime(TIME_END);
};

//====================================
//状態の更新処理
//====================================
void CState_Enemy002_Direction::UpdateState(CEnemy* enemy)
{
	//カウントアップ
	m_nCount++;

	//一定時間で終了
	if (m_nCount > GetEndTime())
	{
		//状態のリセット
		enemy->StateReset();
	}
}