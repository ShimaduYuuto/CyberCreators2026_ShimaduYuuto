//======================================
//
//	エネミーの処理[enemy001.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "enemy001.h"
#include "manager.h"
#include "game.h"
//#include "state_enemy001.h"

//定数の宣言
const float CEnemy001::MOVE_VALUE = 2.0f;
const float CEnemy001::STARTATTACK_RANGE = 50.0f;

//============================
//エネミーのコンストラクタ
//============================
CEnemy001::CEnemy001() :
	m_pShield(nullptr),
	m_bDamageJudge(false)
{
	//ポインタに行動を設定
	ChangeState(new CState_Enemy001_Normal(this));
}

//============================
//エネミーのデストラクタ
//============================
CEnemy001::~CEnemy001()
{

}

//============================
//エネミーの初期化
//============================
HRESULT CEnemy001::Init()
{
	//初期化
	CEnemy::Init();

	//パラメータの初期化
	CCharacter::SetLife(10);	//体力

	//モーションの読み込み
	SetMotionInfo("data\\enemy011motion.txt");

	//盾の生成
	if (m_pShield == nullptr)
	{
		m_pShield = CShield::Create(D3DXVECTOR3(-5.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
		m_pShield->SetParent(GetModelParts(3));
	}

	return S_OK;
}

//============================
//エネミーの終了処理
//============================
void CEnemy001::Uninit()
{
	//盾の破棄
	if (m_pShield != nullptr)
	{
		m_pShield->Uninit();
		m_pShield = nullptr;
	}

	//終了処理
	CEnemy::Uninit();
}

//============================
//エネミーの更新
//============================
void CEnemy001::Update()
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
void CEnemy001::Draw()
{
	//描画
	CCharacter::Draw();
}

//============================
//ダメージの設定
//============================
bool CEnemy001::SetDamage(int damage)
{
	//ダメージの設定
	CEnemy::SetDamage(damage);

	return true;
}

//============================
//ダメージの設定
//============================
bool CEnemy001::SetDamage(int damage, float rotY)
{
	//ダメージを受けるかの判定
	if (!m_bDamageJudge)
	{
		//絶対値に変換後に角度の誤差を計算する
		float fAttackRot = rotY;
		float fRot = GetRot().y;
		float fMin = rotY - D3DX_PI * 0.5f;
		float fMax = rotY + D3DX_PI * 0.5f;

		//後ろからの攻撃なら通す
		if (fRot > fMin && fRot < fMax)
		{
			m_bDamageJudge = true;
		}
		else
		{
			return false;
		}
	}

	//盾を落とす
	DropShield();

	//張り付いていないならダメージ状態に
	if (!GetEnteredStick())
	{
		//状態の変更
		ChangeState(new CState_Enemy001_Damage(this));

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
//吹き飛び処理
//============================
bool CEnemy001::SetBlowOff()
{
	//ヒットしたか
	bool bHit = false;
	
	//アクションをしていないなら吹き飛ばない
	if (m_pShield != nullptr)
	{
		return bHit;
	}

	//盾を持っているなら
	if (m_pShield != nullptr)
	{
		m_pShield->Uninit();
		m_pShield = nullptr;
	}

	bHit = true;

	//当たっていたら吹き飛ぶ
	if (bHit)
	{
		//基底の吹き飛び処理
		CEnemy::SetBlowOff();
		SetMotion(3);
	}

	return bHit;
}

//============================
//ダメージ影響処理
//============================
void CEnemy001::DamageEffect(CPlayer* player)
{
	if (!m_bDamageJudge)
	{
		player->SetKnockBack(30);
	}
}