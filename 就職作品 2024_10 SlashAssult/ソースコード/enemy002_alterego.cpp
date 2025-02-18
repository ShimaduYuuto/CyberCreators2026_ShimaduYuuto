//======================================
//
//	エネミーの処理[enemy002_alterego.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "enemy002_alterego.h"
#include "state_enemy002_alterego.h"
#include "battleareamanager.h"

//定数
const std::string CEnemy002_AlterEgo::FILEPATH = "data\\enemy012AlterEgomotion.txt";

//============================
//エネミーのコンストラクタ
//============================
CEnemy002_AlterEgo::CEnemy002_AlterEgo() :
	m_pMainEnemyBehavior(nullptr)
{
	//敵の数を減らす
	if (CBattleAreaManager::GetInstance()->GetCurrentBattleArea() != nullptr)
	{
		CBattleAreaManager::GetInstance()->GetCurrentBattleArea()->AddEnemyNum();
	}
}

//============================
//エネミーのデストラクタ
//============================
CEnemy002_AlterEgo::~CEnemy002_AlterEgo()
{
	//本体に消えたことを伝える
	m_pMainEnemyBehavior->Erase(this);
}

//============================
//エネミーの初期化
//============================
HRESULT CEnemy002_AlterEgo::Init()
{
	//初期化
	CEnemy::Init();

	//パラメータの初期化
	SetLife(LIFE);	//体力

	//モーションの読み込み
	SetMotionInfo(FILEPATH.c_str());

	//ポインタに行動を設定
	ChangeState(new CState_Enemy002_AlterEgo_Normal(this));

	//透明に設定
	SetMaterialized(false);

	return S_OK;
}

//============================
//エネミーの終了処理
//============================
void CEnemy002_AlterEgo::Uninit()
{
	//終了
	CEnemy002::Uninit();
}

//============================
//エネミーの更新
//============================
void CEnemy002_AlterEgo::Update()
{
	//死亡フラグが立っているなら抜ける
	if (GetDeath())
	{
		return;
	}

	//共通処理の更新
	CEnemy002::Update();
}

//============================
//エネミーの描画
//============================
void CEnemy002_AlterEgo::Draw()
{
	//描画
	CCharacter::Draw();
}

//============================
//生成
//============================
CEnemy002_AlterEgo* CEnemy002_AlterEgo::Create(D3DXVECTOR3 pos, CEnemyBehavior_AlterEgoAttack* action)
{
	//生成
	CEnemy002_AlterEgo* pEnemy = nullptr;
	pEnemy = new CEnemy002_AlterEgo;

	//パラメータの設定
	pEnemy->SetPos(pos);
	pEnemy->m_pMainEnemyBehavior = action;

	//初期化
	pEnemy->Init();

	return pEnemy;
}

//============================
//状態のリセット
//============================
void CEnemy002_AlterEgo::StateReset()
{
	//通常の状態に戻す
	ChangeState(new CState_Enemy002_Normal(this));
	SetEnableGravity(true);
	SetMaterialized(false);
}

//============================
//死亡時の処理
//============================
void CEnemy002_AlterEgo::SetCharacterDeath()
{
	//親の死亡処理
	CEnemy::SetCharacterDeath();
}