//================================
//
//通常状態処理[state_player_normal.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "state_player_normal.h"
#include "state_player_damage.h"
#include "manager.h"

//========================
//ダメージの設定
//========================
bool CState_Player_Normal::SetDamage(CPlayer* player, int damage, float angle)
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

	//SEの設定
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_DAMAGE);

	return true;
}