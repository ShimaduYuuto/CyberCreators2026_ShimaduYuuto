//======================================
//
//	エネミーの処理[enemy002.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "enemy002.h"
#include "manager.h"
#include "game.h"
#include "state_enemy002.h"

//============================
//エネミーのコンストラクタ
//============================
CEnemy002::CEnemy002() : 
	m_bMaterialized(true)
{
	SetMaterialized(false);
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
	CCharacter::SetLife(LIFE);	//体力

	//モーションの読み込み
	SetMotionInfo("data\\enemy012motion.txt");

	//ポインタに行動を設定
	ChangeState(new CState_Enemy002_Direction(this));
	
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

//============================
//実体化の設定
//============================
void CEnemy002::SetMaterialized(bool materialized)
{
	//同じなら抜ける
	if (m_bMaterialized == materialized)
	{
		return;
	}

	//実体化するならパーツを透明にする
	if (materialized)
	{
		//パーツ数だけ周回
		for (auto itr : GetModelPartsVector())
		{
			itr->SetAlpha(1.0f);
		}
	}
	else
	{
		//パーツ数だけ周回
		for (auto itr : GetModelPartsVector())
		{
			itr->SetAlpha(VALUE_INVISIBLE_ALPHA);
		}
	}

	//設定
	m_bMaterialized = materialized;
}

//============================
//状態のリセット
//============================
void CEnemy002::StateReset()
{
	//通常の状態に戻す
	ChangeState(new CState_Enemy002_Normal(this));
	SetEnableGravity(true);
	SetMaterialized(false);
}

//============================
//貼り付け状態に変更
//============================
void CEnemy002::ChangeStickState()
{
	ChangeState(new CState_Enemy002_Stick(this));
}

//============================
//スタン状態に変更
//============================
void CEnemy002::ChangeStanState()
{
	ChangeState(new CState_Enemy002_Stan(this));
	SetMaterialized(true);
}