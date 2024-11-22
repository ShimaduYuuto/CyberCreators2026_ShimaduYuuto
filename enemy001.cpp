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
#include "player.h"
#include "behavior_enemy001.h"
#include "state_enemy_normal.h"

//定数の宣言
const float CEnemy001::MOVE_VALUE = 2.0f;
const float CEnemy001::STARTATTACK_RANGE = 50.0f;

//============================
//エネミーのコンストラクタ
//============================
CEnemy001::CEnemy001() :
	m_pShield(nullptr)
{
	//ポインタに行動を設定
	ChangeState(new CState_Enemy_Normal());
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
void CEnemy001::SetDamage(int damage)
{
	//シールドを持っていたらダメージを受けない
	if (m_pShield != nullptr)
	{
		//ゲームシーンのプレイヤーの位置を取得
		CGame* pGame = nullptr;
		pGame = (CGame*)CManager::GetInstance()->GetScene();	//ゲームシーンの取得
		pGame->GetGamePlayer()->SetKnockBack(20);				//ノックバック
		return;
	}

	//ダメージの設定
	CEnemy::SetDamage(damage);
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