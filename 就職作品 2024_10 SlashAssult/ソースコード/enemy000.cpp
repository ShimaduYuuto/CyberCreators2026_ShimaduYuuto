//======================================
//
//	エネミーの処理[enemy000.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "enemy000.h"
#include "manager.h"
#include "state_enemy000.h"

//定数の宣言
const std::string CEnemy000::FILEPATH = "data\\enemy010motion.txt";
const float CEnemy000::MOVE_VALUE = 2.0f;
const float CEnemy000::STARTATTACK_RANGE = 50.0f;

//============================
//エネミーのコンストラクタ
//============================
CEnemy000::CEnemy000()
{
	
}

//============================
//エネミーのデストラクタ
//============================
CEnemy000::~CEnemy000()
{

}

//============================
//エネミーの初期化
//============================
HRESULT CEnemy000::Init()
{
	//初期化
	CEnemy::Init();

	//パラメータの初期化
	SetLife(LIFE);	//体力

	//モーションの読み込み
	SetMotionInfo(FILEPATH.c_str());

	//ポインタに行動を設定
	ChangeState(new CState_Enemy000_Normal(this));

	return S_OK;
}

//============================
//エネミーの終了処理
//============================
void CEnemy000::Uninit()
{
	//初期化
	CEnemy::Uninit();
}

//============================
//エネミーの更新
//============================
void CEnemy000::Update()
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
void CEnemy000::Draw()
{
	//描画
	CCharacter::Draw();
}

//============================
//ダメージの設定
//============================
bool CEnemy000::SetDamage(int damage, float angle)
{
	//張り付いていないならダメージ状態に
	if (!GetEnteredStick())
	{
		//状態の変更
		ChangeState(new CState_Enemy000_Damage(this));

		//基底の処理
		CEnemy::SetDamage(damage, angle);
	}
	else
	{
		//基底の処理
		CEnemy::SetDamage(damage, angle);
	}

	return true;
}