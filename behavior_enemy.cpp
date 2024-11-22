//================================
//
//敵の行動まとめ[behavior_enemy.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "behavior_enemy.h"
#include "manager.h"
#include "game.h"

const float CEnemyMove_Chase::VALUE_MOVE = 1.0f;

//====================================
//追いかけ処理
//====================================
void CEnemyAction_Chase::Action(CEnemy* enemy)
{
	//ゲームシーンのプレイヤーの位置を取得
	CGame* pGame = nullptr;
	pGame = (CGame*)CManager::GetInstance()->GetScene();		//ゲームシーンの取得
	D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();	//プレイヤーの位置を取得
	D3DXVECTOR3 Pos = enemy->GetPos();							//自分の位置を取得

	//プレイヤーとの角度を算出
	float fAngle = atan2f(PlayerPos.x - Pos.x, PlayerPos.z - Pos.z);//対角線の角度を算出

	//角度を設定
	enemy->SetGoalRot({ enemy->GetRot().x, fAngle + D3DX_PI, enemy->GetRot().z });

	//立っていたら
	if (enemy->CCharacter::GetOnStand())
	{
		//距離の計算
		D3DXVECTOR3 fLengthPos = PlayerPos - Pos;
		float fLength = sqrtf(fLengthPos.x * fLengthPos.x + fLengthPos.z * fLengthPos.z);

		//一定範囲内に入ったら攻撃
		if (fLength < 30.0f)
		{
			//次のアクションに移行
			NextAction(enemy);
		}
		else
		{
			enemy->CCharacter::AddMove({ sinf(fAngle) * VALUE_MOVE, 0.0f, cosf(fAngle) * VALUE_MOVE });
			enemy->SetMotion(1);
		}
	}
	else
	{
		enemy->CCharacter::SetMove({ 0.0f, enemy->CCharacter::GetMove().y, 0.0f });
		enemy->SetMotion(3);
	}
}

//===========================
//攻撃クラス
//===========================

//===============================
//コンストラクタ
//===============================
CEnemyAction_Attack::CEnemyAction_Attack() : m_pAttack(nullptr), m_fAttackLength(0.0f)
{
	//インスタンスを生成
	if (m_pAttack == nullptr)
	{
		m_pAttack = new CAttack();
	}
}

//===============================
//デストラクタ
//===============================
CEnemyAction_Attack::~CEnemyAction_Attack()
{
	//攻撃ポインタの開放
	if (m_pAttack != nullptr)
	{
		delete m_pAttack;
		m_pAttack = nullptr;
	}
}

//===============================
//攻撃処理
//===============================
void CEnemyAction_Attack::Action(CEnemy* enemy)
{
	//ゲームシーンの取得
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

	//パラメータの取得
	bool bHit = m_pAttack->GetHit();
	float fCount = m_pAttack->GetActionCount();
	float fCollisionTime = m_pAttack->GetCollisionTime();
	float fEndTime = m_pAttack->GetEndTime();
	int nDamageValue = m_pAttack->GetDamageValue();

	//当たり判定を始めるカウントになったら
	if (fCount > fCollisionTime)
	{
		//当たっていないなら処理
		if (!bHit)
		{
			//変数宣言
			D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();	//プレイヤーの位置
			D3DXVECTOR3 AttackRot = enemy->GetRot();					//攻撃の向き
			D3DXVECTOR3 AttackPos = enemy->GetPos();					//攻撃の位置

			//攻撃の位置を算出
			AttackPos += D3DXVECTOR3(sinf(AttackRot.y + D3DX_PI) * 20.0f, 0.0f, cosf(AttackRot.y + D3DX_PI) * 20.0f);

			//距離を計算
			float fXZ = sqrtf((AttackPos.x - PlayerPos.x) * (AttackPos.x - PlayerPos.x) + (AttackPos.z - PlayerPos.z) * (AttackPos.z - PlayerPos.z)); //距離を算出する
			float fXY = sqrtf((AttackPos.x - PlayerPos.x) * (AttackPos.x - PlayerPos.x) + (AttackPos.y - PlayerPos.y) * (AttackPos.y - PlayerPos.y)); //距離を算出する
			float fLength = sqrtf(fXZ * fXZ + fXY * fXY);	//距離を算出

			//攻撃の範囲内なら
			if (fLength < m_fAttackLength)
			{
				//プレイヤーにダメージを与える
				pGame->GetGamePlayer()->SetDamage(nDamageValue);
				bHit = true;
			}
		}
	}

	//カウントの更新
	fCount += pGame->GetTime()->GetValue(1.0f);

	//パラメータの設定
	m_pAttack->SetHit(bHit);
	m_pAttack->SetActionCount(fCount);
	m_pAttack->SetCollisionTime(fCollisionTime);
	m_pAttack->SetEndTime(fEndTime);
	m_pAttack->SetDamageValue(nDamageValue);

	//カウントが終了値になったら状態の変更
	if (fEndTime < fCount)
	{
		NextAction(enemy);
	}
}

//================================================================
//以下はバックアップ
//================================================================

//====================================
//移動処理
//====================================
void CEnemyMove_Chase::Move(CEnemy* enemy)
{
	//ゲームシーンのプレイヤーの位置を取得
	CGame* pGame = nullptr;
	pGame = (CGame*)CManager::GetInstance()->GetScene();		//ゲームシーンの取得
	D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();	//プレイヤーの位置を取得
	D3DXVECTOR3 Pos = enemy->GetPos();							//自分の位置を取得

	//プレイヤーとの角度を算出
	float fAngle = atan2f(PlayerPos.x - Pos.x, PlayerPos.z - Pos.z);//対角線の角度を算出

	//角度を設定
	enemy->SetGoalRot({ enemy->GetRot().x, fAngle + D3DX_PI, enemy->GetRot().z });

	//立っていたら
	if (enemy->CCharacter::GetOnStand())
	{
		enemy->CCharacter::AddMove({ sinf(fAngle) * VALUE_MOVE, 0.0f, cosf(fAngle) * VALUE_MOVE });
		enemy->SetMotion(1);
	}
	else
	{
		enemy->CCharacter::SetMove({ 0.0f, enemy->CCharacter::GetMove().y, 0.0f });
		enemy->SetMotion(3);
	}
}

//====================================
//攻撃処理
//====================================
void CEnemyAttack::Attack(CEnemy* enemy)
{
	//ゲームシーンの取得
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

	//パラメータの取得
	bool bHit = GetHit();
	float fCount = GetActionCount();
	float fCollisionTime = GetCollisionTime();
	float fEndTime = GetEndTime();
	int nDamageValue = GetDamageValue();

	//当たり判定を始めるカウントになったら
	if (fCount > fCollisionTime)
	{
		//ゲームシーンなら判定
		if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
		{
			//当たっていないなら処理
			if (!bHit)
			{
				//変数宣言
				D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();	//プレイヤーの位置
				D3DXVECTOR3 AttackRot = enemy->GetRot();					//攻撃の向き
				D3DXVECTOR3 AttackPos = enemy->GetPos();					//攻撃の位置

				//攻撃の位置を算出
				AttackPos += D3DXVECTOR3(sinf(AttackRot.y + D3DX_PI) * 20.0f, 0.0f, cosf(AttackRot.y + D3DX_PI) * 20.0f);

				//距離を計算
				float fXZ = sqrtf((AttackPos.x - PlayerPos.x) * (AttackPos.x - PlayerPos.x) + (AttackPos.z - PlayerPos.z) * (AttackPos.z - PlayerPos.z)); //距離を算出する
				float fXY = sqrtf((AttackPos.x - PlayerPos.x) * (AttackPos.x - PlayerPos.x) + (AttackPos.y - PlayerPos.y) * (AttackPos.y - PlayerPos.y)); //距離を算出する
				float fLength = sqrtf(fXZ * fXZ + fXY * fXY);	//距離を算出

				//攻撃の範囲内なら
				if (fLength < m_fAttackLength)
				{
					//プレイヤーにダメージを与える
					pGame->GetGamePlayer()->SetDamage(nDamageValue);
					bHit = true;
				}
			}
		}
	}

	//カウントの更新
	fCount += pGame->GetTime()->GetValue(1.0f);

	//カウントが終了値になったら
	if (fEndTime < fCount)
	{
		//アクションの終了判定
		SetEndAction(true);
	}

	//パラメータの設定
	SetHit(bHit);
	SetActionCount(fCount);
	SetCollisionTime(fCollisionTime);
	SetEndTime(fEndTime);
	SetDamageValue(nDamageValue);
}