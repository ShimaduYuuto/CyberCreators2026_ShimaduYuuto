//================================
//
//通常状態処理[state_player_counter.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "state_player_counter.h"
#include "state_player_damage.h"
#include "state_player_normal.h"

//====================================
//状態の更新
//====================================
void CState_Player_Counter::UpdateState(CPlayer* player)
{
	//カウンターが発動していたら更新しない
	if (m_bActivationCounter)
	{
		return;
	}

	//メンバ変数の取得
	float fEndTime{ GetEndTime() };	//終了時間
	float fCount{ GetStateCount() };//カウントの取得

	//カウントアップ
	fCount++;

	//カウンターの受付を終了
	if (fCount > TIME_COUNTER && m_bCounter)
	{
		m_bCounter = false;
	}

	//カウントが周り切ったら状態を切り替える
	if (fCount >= fEndTime)
	{
		//次の状態を設定
		if (GetNextState() == nullptr)
		{
			//通常状態に移行
			SetNextState(new CState_Player_Normal(player));
		}
	}

	//状態の設定
	SetStateCount(fCount);
}

//========================
//ダメージの設定
//========================
bool CState_Player_Counter::SetDamage(CPlayer* player, int damage, float angle)
{
	//死亡フラグが立っていたら抜ける
	if (player->GetDeath())
	{
		return true;
	}

	//カウンター攻撃中なら抜ける
	if (m_bActivationCounter)
	{
		return true;
	}

	//カウンター受付中なら
	if (m_bCounter)
	{
		m_bActivationCounter = true;	//カウンターが発動
		SetBehavior(new CPlayerBehavior_CounterAttack(player));	//カウンター攻撃
		return true;
	}

	//ダメージを受ける
	player->CGame_Character::SetDamage(damage, angle);
	player->SetMotion(8);											//モーションの設定
	SetNextState(new CState_Player_Damage(player));					//ステートの設定

	//ノックバックの移動量を設定
	D3DXVECTOR3 Rot = player->GetRot();
	D3DXVECTOR3 Move = player->GetMove();
	D3DXVECTOR3 AddMove = { sinf(Rot.y) * 10.0f, 0.0f, cosf(Rot.y) * 10.0f };

	//移動量の加算
	Move += AddMove;
	player->SetMove(Move);

	//インスタンスの取得
	CGauge_PlayerLife* pGauge = player->GetLifeGauge();

	//体力ゲージに反映
	if (pGauge != nullptr)
	{
		//ゲージに反映
		pGauge->GetGauge()->AddGauge(-(float)damage);
	}

	player->SetLifeGauge(pGauge);

	return true;
}