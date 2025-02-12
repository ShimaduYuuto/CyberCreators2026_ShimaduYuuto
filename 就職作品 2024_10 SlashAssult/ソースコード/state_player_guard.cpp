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
	KnockBackMove(),			//ノックバック量
	m_bStiffening(true),		//硬直判定
	m_nStiffnessCount(0),		//硬直のカウント
	m_pEffect(nullptr),			//エフェクト
	m_bJustGuard(false),		//ジャストガード判定
	m_nFirstStiffnessCount(0)	//発動時の硬直カウント
{
	//設定
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
	//パーツの色を通常に戻す
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

	//カウントアップ
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
		m_bStiffening = false;					//硬直判定をoff
		KnockBackMove = { 0.0f, 0.0f, 0.0f };	//ノックバック量を無くす
		m_nStiffnessCount = 0;					//カウントを初期化
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
		m_bJustGuard = true;											//ジャストガードの判定をon
		m_bStiffening = false;											//硬直判定をoff
		CEffect_JustGuard::Create(player->GetCollision()->GetPos());	//エフェクトを生成
		return true;
	}

	
	KnockBackMove = { sinf(angle + D3DX_PI) * VALUE_KNOCKBACK, 0.0f, cosf(angle + D3DX_PI) * VALUE_KNOCKBACK };	//ノックバックの移動量を設定
	m_bStiffening = true;																						//硬直の判定をon
	m_nStiffnessCount = 0;																						//カウントを初期化
	m_nFirstStiffnessCount = TIME_FIRST_STIFFNESS + 1;															//硬直時間を設定

	//SEの設定
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_REPEL);

	return true;
}