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

//定数
const std::string CEnemy003::FILEPATH = "data\\enemy013motion.txt";

//============================
//エネミーのコンストラクタ
//============================
CEnemy003::CEnemy003() :
	m_bAttacking(false)
{
	
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
	SetLife(LIFE);	//体力

	//モーションの読み込み
	SetMotionInfo(FILEPATH.c_str());

	//ポインタに行動を設定
	ChangeState(new CState_Enemy003_Normal(this));

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
bool CEnemy003::SetDamage(int damage, float angle)
{
	//張り付いていないならダメージ状態に
	if (!GetEnteredStick())
	{
		//攻撃中なら吹っ飛ぶ
		if (m_bAttacking)
		{
			//状態の変更
			CEnemy::SetBlowDamage(damage, angle);
			CEnemy::SetBlowValue({ sinf(angle + D3DX_PI) * 60.0f, 0.0f, cosf(angle + D3DX_PI) * 60.0f });

			//状態の変更
			ChangeState(new CState_Enemy003_Blow(this));
		}
		else
		{
			//状態の変更
			ChangeState(new CState_Enemy003_Damage(this));

			//基底のダメージ処理
			CEnemy::SetDamage(damage, angle);
		}
	}
	else
	{
		//基底のダメージ処理
		CEnemy::SetDamage(damage, angle);
	}

	return true;
}

//============================
//状態のリセット
//============================
void CEnemy003::StateReset()
{
	//通常の状態に戻す
	ChangeState(new CState_Enemy003_Normal(this));
	SetEnableGravity(true);
	m_bAttacking = false;
}

//============================
//貼り付け状態に変更
//============================
void CEnemy003::ChangeStickState()
{
	ChangeState(new CState_Enemy003_Stick(this));
}

//============================
//スタン状態に変更
//============================
void CEnemy003::ChangeStanState()
{
	ChangeState(new CState_Enemy003_Stan(this));
}