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
#include "effect_justguard.h"
#include "manager.h"

//====================================
//コンストラクタ
//====================================
CState_Player_Guard::CState_Player_Guard(CPlayer* player) :
	KnockBackMove(), 
	m_bStiffening(true), 
	m_nStiffnessCount(0),
	m_pEffect(nullptr),
	m_bJustGuard(false),
	m_nFirstStiffnessCount(0)
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
	//パーツ数だけ周回
	for (auto itr : player->GetModelPartsVector())
	{
		itr->SetAlpha(1.0f);
	}

	//発動硬直の更新
	UpdateFirstStiffness();

	//硬直時の更新
	UpdateStiffness(player);
}

//====================================
//発動硬直時の更新
//====================================
void CState_Player_Guard::UpdateFirstStiffness()
{
	//硬直時間を過ぎていたら抜ける
	if (m_nFirstStiffnessCount > TIME_FIRST_STIFFNESS)
	{
		return;
	}

	m_nFirstStiffnessCount++;

	//発動硬直時間を過ぎたら硬直をやめる
	if (m_nFirstStiffnessCount > TIME_FIRST_STIFFNESS)
	{
		m_bStiffening = false;
	}
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
bool CState_Player_Guard::SetDamage(CPlayer* player, int damage, float angle)
{
	//体力がないなら更新しない
	if (player->GetLife() <= 0)
	{
		return false;
	}

	//死亡フラグが立っていたら抜ける
	if (player->GetDeath())
	{
		return true;
	}

	//ジャストガードのフレーム内でガードしたら発動硬直をなくす
	if (m_nFirstStiffnessCount <= TIME_JUSTGUARD)
	{
		//フラグを立てて硬直をなくす
		m_bJustGuard = true;
		m_bStiffening = false;
		CEffect_JustGuard::Create(player->GetCollision()->GetPos());
		return true;
	}

	//ノックバックの移動量を設定
	KnockBackMove = { sinf(angle) * VALUE_KNOCKBACK, 0.0f, cosf(angle) * VALUE_KNOCKBACK };
	m_bStiffening = true;
	m_nStiffnessCount = 0;
	m_nFirstStiffnessCount = TIME_FIRST_STIFFNESS + 1;

	//SEの設定
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_REPEL);

	return true;
}