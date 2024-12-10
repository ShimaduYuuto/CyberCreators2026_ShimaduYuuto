//================================
//
//敵の行動まとめ[behavior_enemy002.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "behavior_enemy002.h"
#include "enemy002.h"
#include "enemybullet.h"
#include "game.h"
#include "manager.h"

//======================================================================
//待機
//======================================================================

//====================================
//アクション(待機)
//====================================
void CEnemyAction_Standby::Action(CEnemy* enemy)
{
	//クールタイムが終わったら次の行動を行う
	m_nCoolTime--;

	if (m_nCoolTime < 0)
	{
		//攻撃する
		SetNextAction(new CEnemyAction_ChargeShot(enemy));
	}
}

//====================================
//次の行動を設定
//====================================
void CEnemyAction_Standby::NextAction(CEnemy* enemy)
{
	//攻撃を設定
	SetNextAction(new CEnemyAction_Attack002(enemy));
}

//======================================================================
//チャージショット
//======================================================================

//====================================
//アクション(チャージショット)
//====================================
void CEnemyAction_ChargeShot::Action(CEnemy* enemy)
{
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

		//カウントの更新
		m_nChargeCount++;

		//弾の生成時間になったら生成
		if (m_nChargeCount > CREATE_BULLET_TIME)
		{
			//弾の生成
			if (m_pBullet == nullptr)
			{
				m_pBullet = CEnemyBullet::Create(enemy->GetCollision()->GetPos(), { 0.0f, 0.0f, 0.0f });
				m_pEffect = CEffect_ChargeShot::Create(enemy->GetCollision()->GetPos());
			}
		}

		//弾が生成済みなら
		if (m_pBullet != nullptr)
		{
			//スケールを大きくする
			m_pBullet->AddSizeRate(ADD_SCALE_VALUE);
			m_pBullet->SetPos({ enemy->GetCollision()->GetPos().x + sinf(fAngle) * 20.0f * m_pBullet->GetSizeRate() , enemy->GetCollision()->GetPos().y, enemy->GetCollision()->GetPos().z + cosf(fAngle) * 20.0f * m_pBullet->GetSizeRate() });

			//チャージ時間を終えたら発射
			if (m_nChargeCount > CHARGE_TIME)
			{
				//向いている方向に撃つ
				m_pBullet->SetMove({ sinf(fAngle) * 3.0f, 0.0f, cosf(fAngle) * 3.0f });
				m_pBullet->SetShooting(true);

				//エフェクトの破棄
				if (m_pEffect != nullptr)
				{
					m_pEffect->Uninit();
					m_pEffect = nullptr;
				}	
			}
		}
	}

	//終了の時間になったら待機アクション
	if (m_nChargeCount > END_TIME)
	{
		SetNextAction(new CEnemyAction_Standby(enemy));
	}

	//当たっていたら消す
	if (m_pBullet != nullptr)
	{
		if (m_pBullet->GetDeath())
		{
			m_pBullet = nullptr;
			SetNextAction(new CEnemyAction_Standby(enemy));
		}
	}
}

//======================================================================
//登場演出
//======================================================================

//====================================
//コンストラクタ
//====================================
CEnemyAction_Direction::CEnemyAction_Direction(CEnemy* enemy) :
	m_nCount(0)
{
	enemy->SetMotion(6);
}

//====================================
//アクション(演出)
//====================================
void CEnemyAction_Direction::Action(CEnemy* enemy)
{
	//演出の時間が終わったら行動開始
	m_nCount++;

	if (m_nCount > DIRECTION_TIME)
	{
		NextAction(enemy);
	}
}