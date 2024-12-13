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

//============================
//エネミーのコンストラクタ
//============================
CEnemy002_AlterEgo::CEnemy002_AlterEgo()
{
	//敵の数を減らす
	if (CBattleAreaManager::GetInstance()->GetCurrentBattleArea() != nullptr)
	{
		CBattleAreaManager::GetInstance()->GetCurrentBattleArea()->AddEnemyNum();
	}

	//オブジェクトの自動更新はしない
	SetUpdateJudge(false);
}

//============================
//エネミーのデストラクタ
//============================
CEnemy002_AlterEgo::~CEnemy002_AlterEgo()
{

}

//============================
//エネミーの初期化
//============================
HRESULT CEnemy002_AlterEgo::Init()
{
	//初期化
	CEnemy::Init();

	//パラメータの初期化
	CCharacter::SetLife(LIFE);	//体力

	//モーションの読み込み
	SetMotionInfo("data\\enemy012motion.txt");

	//ポインタに行動を設定
	ChangeState(new CState_Enemy002_AlterEgo_Normal(this));

	return S_OK;
}

//============================
//エネミーの終了処理
//============================
void CEnemy002_AlterEgo::Uninit()
{
	//初期化
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
	CEnemy::Update();
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
CEnemy002_AlterEgo* CEnemy002_AlterEgo::Create(D3DXVECTOR3 pos)
{
	//生成
	CEnemy002_AlterEgo* pEnemy = nullptr;
	pEnemy = new CEnemy002_AlterEgo;

	//パラメータの設定
	pEnemy->SetPos(pos);

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