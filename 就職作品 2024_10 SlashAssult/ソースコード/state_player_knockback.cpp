//================================
//
//状態に応じた処理を実行[state_player_knockback.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "state_player_knockback.h"
#include "state_player_normal.h"
#include "state_player_damage.h"
#include "manager.h"

//====================================
//状態の更新
//====================================
void CState_Player_Knockback::UpdateState(CPlayer* player)
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
bool CState_Player_Knockback::SetDamage(CPlayer* player, int damage, float angle)
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