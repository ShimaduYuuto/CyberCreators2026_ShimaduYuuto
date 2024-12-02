//================================
//
//敵の行動まとめ[behavior_enemy003.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "behavior_enemy003.h"
#include "enemy003.h"
#include "game.h"
#include "manager.h"

//======================================================================
//待機
//======================================================================

//====================================
//アクション(待機)
//====================================
void CEnemyAction_Standby003::Action(CEnemy* enemy)
{
	//クールタイムが終わったら次の行動を行う
	m_nCoolTime--;

	if (m_nCoolTime < 0)
	{
		//攻撃する
		SetNextAction(new CEnemyAction_ChargeAttack(enemy));
	}
}

//====================================
//次の行動を設定
//====================================
void CEnemyAction_Standby003::NextAction(CEnemy* enemy)
{
	//攻撃を設定
	SetNextAction(new CEnemyAction_Attack003(enemy));
}

//======================================================================
//チャージアタック
//======================================================================

//====================================
//アクション(チャージアタック)
//====================================
void CEnemyAction_ChargeAttack::Action(CEnemy* enemy)
{
	//カウントの更新
	m_nChargeCount++;

	//カウントが回り切っていないなら更新
	if (m_nChargeCount <= CHARGE_TIME)
	{
		CGame* pGame = nullptr;
		pGame = (CGame*)CManager::GetInstance()->GetScene();		//ゲームシーンの取得
		D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();	//プレイヤーの位置を取得
		D3DXVECTOR3 Pos = enemy->GetPos();							//自分の位置を取得

		//プレイヤーとの角度を算出
		float fAngle = atan2f(PlayerPos.x - Pos.x, PlayerPos.z - Pos.z);//対角線の角度を算出

		//角度を設定
		enemy->SetGoalRot({ enemy->GetRot().x, fAngle + D3DX_PI, enemy->GetRot().z });

		//チャージが終わったら攻撃
		if (m_nChargeCount >= CHARGE_TIME)
		{
			//攻撃判定にする
			CEnemy003* pEnemy003 = (CEnemy003*)enemy;
			pEnemy003->SetAttacking(true);

			//移動値の設定
			enemy->SetMove({ sinf(fAngle) * SPEED_MOVE, 0.0f, cosf(fAngle) * SPEED_MOVE });
			m_fAttackAngle = fAngle;
		}
	}
	else
	{
		//移動値の設定
		enemy->SetMove({ sinf(m_fAttackAngle) * SPEED_MOVE, 0.0f, cosf(m_fAttackAngle) * SPEED_MOVE });

		//終了の時間になったら待機
		if (m_nChargeCount > END_TIME)
		{
			//攻撃判定の終了
			CEnemy003* pEnemy003 = (CEnemy003*)enemy;
			pEnemy003->SetAttacking(false);

			SetNextAction(new CEnemyAction_Standby003(enemy));
		}
	}
	
}