//================================
//
//ガード時のノックバック処理[guard_knockback.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "guard_knockback.h"
#include "effect_guard.h"
#include "effect_justguard.h"
#include "manager.h"

//====================================
//コンストラクタ
//====================================
CGuard_Knockback::CGuard_Knockback(float angle) :
	KnockBackMove(),
	m_bStiffening(true),
	m_nStiffnessCount(0)
{
	//ノックバックの移動量を設定
	KnockBackMove = { sinf(angle) * VALUE_KNOCKBACK, 0.0f, cosf(angle) * VALUE_KNOCKBACK };
	m_bStiffening = true;
	m_nStiffnessCount = 0;
}

//====================================
//デストラクタ
//====================================
CGuard_Knockback::~CGuard_Knockback()
{
	
}

//====================================
//行動の更新
//====================================
void CGuard_Knockback::Update(CPlayer* player)
{
	//硬直中
	if (m_bStiffening) return;

	//硬直時の更新
	UpdateStiffness(player);
}

//====================================
//硬直時の更新
//====================================
void CGuard_Knockback::UpdateStiffness(CPlayer* player)
{
	//硬直時のフラグが立っているなら抜ける
	if (!m_bStiffening)
	{
		return;
	}

	//カウントアップ
	m_nStiffnessCount++;

	//ノックバック値を減衰
	KnockBackMove.x += (0.0f - KnockBackMove.x) * VALUE_ATTENUATION;
	KnockBackMove.z += (0.0f - KnockBackMove.z) * VALUE_ATTENUATION;

	//プレイヤーの移動量に加算
	player->AddMove(KnockBackMove);

	//一定カウント後に硬直を解除
	if (m_nStiffnessCount > TIME_STIFFNESS)
	{
		m_bStiffening = false;
		KnockBackMove = { 0.0f, 0.0f, 0.0f };
		m_nStiffnessCount = 0;
	}
}