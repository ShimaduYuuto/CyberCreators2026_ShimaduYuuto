//================================
//
//エネミー002の状態処理[state_enemy002.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "state_enemy002.h"

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