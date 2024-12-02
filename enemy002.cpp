//======================================
//
//	エネミーの処理[enemy002.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "enemy002.h"
#include "manager.h"
#include "state_enemy002.h"

//============================
//エネミーのコンストラクタ
//============================
CEnemy002::CEnemy002()
{
	//ポインタに行動を設定
	ChangeState(new CState_Enemy002_Normal(this));
}

//============================
//エネミーのデストラクタ
//============================
CEnemy002::~CEnemy002()
{

}

//============================
//エネミーの初期化
//============================
HRESULT CEnemy002::Init()
{
	//初期化
	CEnemy::Init();

	//パラメータの初期化
	CCharacter::SetLife(20);	//体力

	//モーションの読み込み
	SetMotionInfo("data\\enemy012motion.txt");

	return S_OK;
}

//============================
//エネミーの終了処理
//============================
void CEnemy002::Uninit()
{
	//初期化
	CEnemy::Uninit();
}

//============================
//エネミーの更新
//============================
void CEnemy002::Update()
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
void CEnemy002::Draw()
{
	//描画
	CCharacter::Draw();
}

//============================
//ダメージの設定
//============================
bool CEnemy002::SetDamage(int damage)
{
	//実体化していないなら当たらない
	if (!m_bMaterialized)
	{
		return false;
	}

	//基底の処理
	CEnemy::SetDamage(damage);

	return true;
}

//============================
//ダメージの設定
//============================
bool CEnemy002::SetDamage(int damage, float rotY)
{
	//実体化していないなら当たらない
	if (!m_bMaterialized)
	{
		return false;
	}

	//張り付いていないならダメージ状態に
	if (!GetEnteredStick())
	{
		//状態の変更
		ChangeState(new CState_Enemy002_Damage(this));

		//基底の処理
		CEnemy::SetDamage(damage, rotY);
	}
	else
	{
		//基底の処理
		CEnemy::SetDamage(damage);
	}

	return true;
}

//============================
//ダメージの設定
//============================
bool CEnemy002::SetBlowDamage(int damage, float rotY)
{
	//実体化していないなら当たらない
	if (!m_bMaterialized)
	{
		return false;
	}

	CEnemy::SetBlowDamage(damage, rotY);

	return true;
}

//============================
//ダメージの設定
//============================
bool CEnemy002::SetBlowDamage(int damage, float rotY, float value)
{
	//実体化していないなら当たらない
	if (!m_bMaterialized)
	{
		return false;
	}

	CEnemy::SetBlowDamage(damage, rotY, value);

	return true;
}