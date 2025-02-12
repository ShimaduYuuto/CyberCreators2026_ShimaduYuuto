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

//====================================
//追いかけ処理
//====================================

//==============================
//コンストラクタ
//==============================
CEnemyBehavior_Chase::CEnemyBehavior_Chase(CEnemy* enemy)
{
	enemy->SetCollisionProcess(true);	//当たり判定を続ける
}

//==============================
//アクション
//==============================
void CEnemyBehavior_Chase::Action(CEnemy* enemy)
{
	//プレイヤーの方を向く
	LookAtPlayer(enemy);

	//移動
	Move(enemy);
}

//==============================
//プレイヤーの方向を向く
//==============================
void CEnemyBehavior_Chase::LookAtPlayer(CEnemy* enemy)
{
	//ゲームシーンのプレイヤーの位置を取得
	CGame* pGame = nullptr;
	pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());	//ゲームシーンの取得
	D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();			//プレイヤーの位置を取得
	D3DXVECTOR3 Pos = enemy->GetPos();									//自分の位置を取得

	//プレイヤーとの角度を算出
	float fAngle = atan2f(PlayerPos.x - Pos.x, PlayerPos.z - Pos.z);//対角線の角度を算出

	//角度を設定
	enemy->SetGoalRot({ enemy->GetRot().x, fAngle + D3DX_PI, enemy->GetRot().z });
}

//==============================
//移動処理
//==============================
void CEnemyBehavior_Chase::Move(CEnemy* enemy)
{
	//立っていたら
	if (enemy->GetOnStand())
	{
		//一定範囲内に入ったら攻撃
		if (IsNextAction(enemy))
		{
			//次のアクションに移行
			NextAction(enemy);
		}
		else
		{
			//追いかける移動を処理
			ChaseMove(enemy);
		}
	}
	else
	{
		//重力の影響のみ反映
		enemy->CCharacter::SetMove({ 0.0f, enemy->CCharacter::GetMove().y, 0.0f });
	}
}

//==============================
//次の行動に移行するか
//==============================
bool CEnemyBehavior_Chase::IsNextAction(CEnemy* enemy)
{
	if (!enemy->GetOnStand()) return false;	//立っていないなら移行しない

	//ゲームシーンのプレイヤーの位置を取得
	CGame* pGame = nullptr;
	pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());	//ゲームシーンの取得
	D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();			//プレイヤーの位置を取得
	D3DXVECTOR3 Pos = enemy->GetPos();									//自分の位置を取得

	//距離の計算
	D3DXVECTOR3 fLengthPos = PlayerPos - Pos;
	float fLength = sqrtf(fLengthPos.x * fLengthPos.x + fLengthPos.z * fLengthPos.z);

	//範囲外なら抜ける
	if (fLength > LENGTH_CHANGEATTACK) return false;

	//範囲内なら移行
	return true;
}

//==============================
//追いかける移動の処理
//==============================
void CEnemyBehavior_Chase::ChaseMove(CEnemy* enemy)
{
	//ゲームシーンのプレイヤーの位置を取得
	CGame* pGame = nullptr;
	pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());	//ゲームシーンの取得
	D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();			//プレイヤーの位置を取得
	D3DXVECTOR3 Pos = enemy->GetPos();									//自分の位置を取得

	//プレイヤーとの角度を算出
	float fAngle = atan2f(PlayerPos.x - Pos.x, PlayerPos.z - Pos.z);//対角線の角度を算出

	enemy->CCharacter::AddMove({ sinf(fAngle) * VALUE_MOVE, 0.0f, cosf(fAngle) * VALUE_MOVE });
}

//===========================
//攻撃クラス
//===========================

//===============================
//コンストラクタ
//===============================
CEnemyBehavior_Attack::CEnemyBehavior_Attack(CEnemy* enemy) :m_pAttack(nullptr), m_fAttackLength(0.0f)
{
	//インスタンスを生成
	if (m_pAttack == nullptr)
	{
		m_pAttack = new CAttack();
	}

	//攻撃中は当たり判定を行わない
	enemy->SetCollisionProcess(false);
}

//===============================
//デストラクタ
//===============================
CEnemyBehavior_Attack::~CEnemyBehavior_Attack()
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
void CEnemyBehavior_Attack::Action(CEnemy* enemy)
{
	//パラメータの取得
	float fCount = m_pAttack->GetActionCount();		//カウント
	float fEndTime = m_pAttack->GetEndTime();			//終了時間

	//当たり判定を確認するか
	if (IsCheckCollision())
	{
		//当たり判定の確認
		CheckCollision(enemy);
	}

	//カウントが終了値になったら状態の変更
	if (fEndTime < fCount)
	{
		NextAction(enemy);	//次の行動を設定
	}

	//カウントの更新
	fCount++;

	//パラメータの設定
	m_pAttack->SetActionCount(fCount);
}

//===============================
//当たり判定の確認
//===============================
void CEnemyBehavior_Attack::CheckCollision(CEnemy* enemy)
{
	//ゲームシーンの取得
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//変数宣言
	D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetCollision()->GetPos();	//プレイヤーの位置
	D3DXVECTOR3 AttackRot = enemy->GetRot();									//攻撃の向き
	D3DXVECTOR3 AttackPos = enemy->GetCollision()->GetPos();					//攻撃の位置

	//攻撃の位置を算出
	AttackPos += D3DXVECTOR3(sinf(AttackRot.y + D3DX_PI) * POS_LENGTH, 0.0f, cosf(AttackRot.y + D3DX_PI) * POS_LENGTH);

	//距離を計算
	D3DXVECTOR3 Length = AttackPos - PlayerPos;	//3方向に分解した距離
	float fLength = D3DXVec3Length(&Length);	//距離
	float fAngle = atan2f(Length.x, Length.z);	//角度

	//攻撃の範囲内なら
	if (fLength < m_fAttackLength)
	{
		HitPlayer(fAngle);
	}
}

//===============================
//当たり判定の確認をするか
//===============================
bool CEnemyBehavior_Attack::IsCheckCollision()
{
	//パラメータの取得
	bool bHit = m_pAttack->GetHit();						//当たったか
	float fCount = m_pAttack->GetActionCount();				//カウント
	float fCollisionTime = m_pAttack->GetCollisionTime();	//当たり判定の時間

	//確認
	if (fCount <= fCollisionTime) return false;	//コリジョンが発生する時間なら通す
	if (bHit) return false;						//まだ当たっていないなら通す

	return true;
}

//===============================
//プレイヤーにヒットした際の処理
//===============================
void CEnemyBehavior_Attack::HitPlayer(float angle)
{
	//変数宣言
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());	//ゲームシーンの取得
	int nDamageValue = m_pAttack->GetDamageValue();								//ダメージ値

	//プレイヤーにダメージを与える
	pGame->GetGamePlayer()->SetDamage(nDamageValue, angle);
	m_pAttack->SetHit(true);
}