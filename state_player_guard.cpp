//================================
//
//通常状態処理[state_player_guard.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "state_player_guard.h"
#include "state_player_damage.h"
#include "state_player_normal.h"
#include "behavior_player.h"
#include "effect_guard.h"

//====================================
//コンストラクタ
//====================================
CState_Player_Guard::CState_Player_Guard(CPlayer* player) :
	KnockBackMove(), 
	m_bStiffening(false), 
	m_nStiffnessCount(0),
	m_pEffect(nullptr)
{
	SetBehavior(new CPlayerBehavior_Guard(player));							//行動の設定
	m_pEffect = CEffect_Guard::Create(&player->GetCollision()->GetPos());	//エフェクトの取得
}

//====================================
//デストラクタ
//====================================
CState_Player_Guard::~CState_Player_Guard()
{
	//エフェクトに終了の合図を送る
	if (m_pEffect != nullptr)
	{
		m_pEffect->SetEnd();
		m_pEffect = nullptr;
	}
}

//====================================
//行動の更新
//====================================
void CState_Player_Guard::UpdateBehavior(CPlayer* player)
{
	//硬直中
	if (m_bStiffening)
	{
		return;
	}

	//行動の更新
	CState_Player::UpdateBehavior(player);
}

//====================================
//状態の更新
//====================================
void CState_Player_Guard::UpdateState(CPlayer* player)
{
	//硬直時の更新
	UpdateStiffness(player);
}

//====================================
//硬直時の更新
//====================================
void CState_Player_Guard::UpdateStiffness(CPlayer* player)
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

//========================
//ダメージの設定
//========================
bool CState_Player_Guard::SetDamage(CPlayer* player, int damage)
{
	//死亡フラグが立っていたら抜ける
	if (player->GetDeath())
	{
		return true;
	}

	//ノックバックの移動量を設定
	KnockBackMove = { sinf(player->GetRot().y) * VALUE_KNOCKBACK, 0.0f, cosf(player->GetRot().y) * VALUE_KNOCKBACK };
	m_bStiffening = true;
	m_nStiffnessCount = 0;

	return true;
}