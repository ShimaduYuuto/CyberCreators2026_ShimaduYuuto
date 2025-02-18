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
void CEnemyBehavior_Standby003::Action(CEnemy* enemy)
{
	//クールタイムを減らす
	m_nCoolTime--;

	//クールタイムが終わったら次の行動を行う
	if (m_nCoolTime < 0)
	{
		//攻撃する
		SetNextAction(new CEnemyBehavior_ChargeAttack(enemy));
	}
}

//====================================
//次の行動を設定
//====================================
void CEnemyBehavior_Standby003::NextAction(CEnemy* enemy)
{
	//攻撃を設定
	SetNextAction(new CEnemyBehavior_Attack003(enemy));
}

//======================================================================
//チャージアタック
//======================================================================

//====================================
//アクション(チャージアタック)
//====================================
void CEnemyBehavior_ChargeAttack::Action(CEnemy* enemy)
{
	//カウントの更新
	m_nChargeCount++;

	//カウントが回り切っていないなら更新
	if (m_nChargeCount <= CHARGE_TIME)
	{
		//プレイヤーの方を向く
		LookAtPlayer(enemy);
	}
	else
	{
		//移動値の設定
		enemy->SetMove({ sinf(m_fAttackAngle) * SPEED_MOVE, 0.0f, cosf(m_fAttackAngle) * SPEED_MOVE });

		//攻撃の範囲内なら
		if (CheckAttackHit(enemy))
		{
			EndAttack(enemy);	//攻撃終了時の処理
		}

		//終了の時間になったら待機
		if (m_nChargeCount > END_TIME)
		{
			EndAttack(enemy);	//攻撃終了時の処理
		}
	}
	
}

//====================================
//プレイヤーの方を向く
//====================================
void CEnemyBehavior_ChargeAttack::LookAtPlayer(CEnemy* enemy)
{
	//変数宣言
	CGame* pGame = nullptr;
	pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());		//ゲームシーンの取得
	D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();				//プレイヤーの位置を取得
	D3DXVECTOR3 Pos = enemy->GetPos();										//自分の位置を取得

	//プレイヤーとの角度を算出
	float fAngle = atan2f(PlayerPos.x - Pos.x, PlayerPos.z - Pos.z);//対角線の角度を算出

	//角度を設定
	enemy->SetGoalRot({ enemy->GetRot().x, fAngle + D3DX_PI, enemy->GetRot().z });

	//チャージが終わったら攻撃
	if (m_nChargeCount >= CHARGE_TIME)
	{
		PreparationAttack(enemy, fAngle);
	}
}

//====================================
//攻撃の準備
//====================================
void CEnemyBehavior_ChargeAttack::PreparationAttack(CEnemy* enemy, float angle)
{
	//攻撃判定にする
	CEnemy003* pEnemy003 = dynamic_cast<CEnemy003*>(enemy);
	pEnemy003->SetAttacking(true);

	//移動値の設定
	enemy->SetMove({ sinf(angle) * SPEED_MOVE, 0.0f, cosf(angle) * SPEED_MOVE });
	m_fAttackAngle = angle;
}

//====================================
//攻撃が当たったかを確認
//====================================
bool CEnemyBehavior_ChargeAttack::CheckAttackHit(CEnemy* enemy)
{
	//変数宣言
	CGame* pGame = nullptr;
	pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());			//ゲームシーンの取得
	D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetCollision()->GetPos();	//プレイヤーの当たり判定の位置
	D3DXVECTOR3 EnemyPos = enemy->GetCollision()->GetPos();						//エネミーの位置を取得
	D3DXVECTOR3 Distance = enemy->GetPos() - PlayerPos;
	float fAngle = atan2f(Distance.x, Distance.z);

	//距離を計算
	float fXZ = sqrtf((EnemyPos.x - PlayerPos.x) * (EnemyPos.x - PlayerPos.x) + (EnemyPos.z - PlayerPos.z) * (EnemyPos.z - PlayerPos.z)); //距離を算出する
	float fXY = sqrtf((EnemyPos.x - PlayerPos.x) * (EnemyPos.x - PlayerPos.x) + (EnemyPos.y - PlayerPos.y) * (EnemyPos.y - PlayerPos.y)); //距離を算出する
	float fLength = sqrtf(fXZ * fXZ + fXY * fXY);	//距離を算出

	//判定
	if (fLength > pGame->GetGamePlayer()->GetCollision()->GetRadius() + enemy->GetCollision()->GetRadius()) return false;	//攻撃が当たっていないなら抜ける
	if (!pGame->GetGamePlayer()->SetDamage(1, fAngle)) return false;														//ダメージを与えられなかったら抜ける

	return true;
}

//====================================
//攻撃終了時の処理
//====================================
void CEnemyBehavior_ChargeAttack::EndAttack(CEnemy* enemy)
{
	//攻撃判定の終了
	CEnemy003* pEnemy003 = dynamic_cast<CEnemy003*>(enemy);
	if (pEnemy003 == nullptr) assert("enemy003へのキャストに失敗");
	pEnemy003->SetAttacking(false);

	//待機状態になる
	SetNextAction(new CEnemyBehavior_Standby003(enemy));
}