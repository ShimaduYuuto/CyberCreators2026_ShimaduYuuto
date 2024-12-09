//======================================
//
//	エネミーの処理[enemy003.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "enemy003.h"
#include "manager.h"
#include "state_enemy003.h"

//============================
//エネミーのコンストラクタ
//============================
CEnemy003::CEnemy003() :
	m_bAttacking(false)
{
	//ポインタに行動を設定
	ChangeState(new CState_Enemy003_Normal(this));
}

//============================
//エネミーのデストラクタ
//============================
CEnemy003::~CEnemy003()
{

}

//============================
//エネミーの初期化
//============================
HRESULT CEnemy003::Init()
{
	//初期化
	CEnemy::Init();

	//パラメータの初期化
	CCharacter::SetLife(10);	//体力

	//モーションの読み込み
	SetMotionInfo("data\\enemy013motion.txt");

	return S_OK;
}

//============================
//エネミーの終了処理
//============================
void CEnemy003::Uninit()
{
	//初期化
	CEnemy::Uninit();
}

//============================
//エネミーの更新
//============================
void CEnemy003::Update()
{
	//死亡フラグが立っているなら抜ける
	if (GetDeath())
	{
		return;
	}

	//共通処理の更新
	CEnemy::Update();
}

//============================
//エネミーの描画
//============================
void CEnemy003::Draw()
{
	//描画
	CCharacter::Draw();
}

//============================
//ダメージの設定
//============================
bool CEnemy003::SetDamage(int damage, float rotY)
{
	//張り付いていないならダメージ状態に
	if (!GetEnteredStick())
	{
		//攻撃中なら吹っ飛ぶ
		if (m_bAttacking)
		{
			//状態の変更
			CEnemy::SetBlowDamage(damage, rotY);
			CEnemy::SetBlowValue({ sinf(rotY + D3DX_PI) * 60.0f, 0.0f, cosf(rotY + D3DX_PI) * 60.0f });

			//状態の変更
			ChangeState(new CState_Enemy003_Blow(this));
		}
		else
		{
			//状態の変更
			ChangeState(new CState_Enemy003_Damage(this));

			//基底の処理
			CEnemy::SetDamage(damage, rotY);
		}
	}
	else
	{
		//基底の処理
		CEnemy::SetDamage(damage);
	}

	return true;
}