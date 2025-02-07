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
	SetAction(new CEnemyBehavior_Standby(enemy));
};	

//===============================================
//スタン状態
//===============================================

//====================================
//コンストラクタ
//====================================
CState_Enemy002_Stan::CState_Enemy002_Stan(CEnemy* enemy) : m_pStanEffect(nullptr)
{
	SetAction(new CEnemyBehavior());
	//enemy->SetMotion(5);
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
//貼り付け状態状態
//===============================================

//====================================
//コンストラクタ
//====================================
CState_Enemy002_Stick::CState_Enemy002_Stick(CEnemy* enemy) : CState_Enemy_Stick(enemy)
{
	SetEndTime(TIME_END);
	enemy->SetMotion(CEnemy002::ENEMY002MOTION_STICK);
}

//===============================================
//演出状態
//===============================================

//====================================
//コンストラクタ
//====================================
CState_Enemy002_Direction::CState_Enemy002_Direction(CEnemy* enemy) : m_nCount(0)
{
	SetAction(new CEnemyBehavior_Direction(enemy));
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

//===============================================
//撃破演出状態
//===============================================

//====================================
//コンストラクタ
//====================================
CState_Enemy002_Direction_Destroy::CState_Enemy002_Direction_Destroy(CEnemy* enemy)
{
	SetAction(new CEnemyBehavior_Direction_Destroy(enemy));
};