//======================================
//
//	エネミーの処理[enemy.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "enemy.h"
#include "manager.h"
#include "game.h"
#include "enemy000.h"
#include "enemy001.h"
#include "enemy002.h"
#include "enemy003.h"
#include "state_enemy_damage.h"
#include "battleareamanager.h"

//============================
//エネミーのコンストラクタ
//============================
CEnemy::CEnemy(int nPriority) : 
	CCharacter(nPriority), m_Collision(),
	m_EnemyType(),
	m_pState(nullptr)
{
	//敵の種類を設定
	m_EnemyType = ENEMYTYPE_ENEMY000;
	SetType(TYPE_ENEMY);	//敵の種類

	//ゲームシーンなら判定
	if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
	{
		//ゲームシーンの取得
		CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

		//マネージャーに登録
		pGame->GetEnemyManager()->Regist(this);

		//当たり判定の生成
		if (m_Collision == nullptr)
		{
			m_Collision = CCollision::Create(GetSizeRadius(), D3DXVECTOR3(0.0f, 30.0f, 0.0f));
		}
	}
}

//============================
//エネミーのデストラクタ
//============================
CEnemy::~CEnemy()
{
	//ゲームシーンなら判定
	if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
	{
		//ゲームシーンの取得
		CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

		//マネージャーから削除
		pGame->GetEnemyManager()->Erase(this);

		if (pGame->GetLockon() != nullptr)
		{
			pGame->GetLockon()->Erase(this);
		}
	}

	//敵の数を減らす
	if (CBattleAreaManager::GetInstance()->GetCurrentBattleArea() != nullptr)
	{
		CBattleAreaManager::GetInstance()->GetCurrentBattleArea()->DecrementEnemyNum();
	}

	//当たり判定の消去
	if (m_Collision != nullptr)
	{
		m_Collision->Uninit();
		m_Collision = nullptr;
	}
}

//============================
//エネミーの初期化
//============================
HRESULT CEnemy::Init()
{
	//初期化
	CCharacter::Init();

	return S_OK;
}

//============================
//エネミーの終了処理
//============================
void CEnemy::Uninit()
{
	//死亡フラグが立っていたら抜ける
	if (GetDeath())
	{
		return;
	}

	//初期化
	CCharacter::Uninit();
}

//============================
//エネミーの更新
//============================
void CEnemy::Update()
{
	//状態に応じた更新処理
	if (m_pState != nullptr)
	{
		m_pState->Update(this);

		//次のアクションがあるなら変更
		if (m_pState->GetNextState() != nullptr)
		{
			//次のアクションに変更
			CState_Enemy* pNext = m_pState->GetNextState();
			delete m_pState;
			m_pState = nullptr;

			//代入
			m_pState = pNext;
		}
	}

	//共通処理の更新
	CCharacter::Update();

	//当たり判定の位置の更新
	m_Collision->Update(GetPos());
}

//============================
//エネミーの描画
//============================
void CEnemy::Draw()
{
	
}

//============================
//エネミーのクリエイト
//============================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, ENEMYTYPE type)
{
	//種類に応じて動的確保
	CEnemy* pEnemy = nullptr;

	switch (type)
	{
	case ENEMYTYPE_ENEMY000:	//通常の敵

		//敵のメモリ確保
		pEnemy = new CEnemy000;
		break;

	case ENEMYTYPE_ENEMY001:	//盾持ちの敵

	//敵のメモリ確保
		pEnemy = new CEnemy001;
		break;

	case ENEMYTYPE_ENEMY002:	//ボスの敵

	//敵のメモリ確保
		pEnemy = new CEnemy002;
		break;

	case ENEMYTYPE_ENEMY003:	//突進の敵

	//敵のメモリ確保
		pEnemy = new CEnemy003;
		break;
	}

	//初期化
	pEnemy->Init();

	//位置の設定
	pEnemy->SetPos(pos);

	//設定した情報を返す
	return pEnemy;
}

//============================
//ダメージの設定
//============================
bool CEnemy::SetDamage(int damage)
{
	//攻撃を止める
	//SetMotion(0);

	//ダメージの設定
	CCharacter::SetDamage(damage);

	return true;
}

//============================
//ダメージの設定
//============================
bool CEnemy::SetDamage(int damage, float rotY)
{
	//ノックバックの設定
	D3DXVECTOR3 Move = {sinf(rotY + D3DX_PI) * VALUE_KNOCKBACK, 0.0f, cosf(rotY + D3DX_PI) * VALUE_KNOCKBACK };

	//移動量を設定
	CCharacter::AddMove(Move);

	//ダメージの設定
	CEnemy::SetDamage(damage);

	return true;
}

//============================
//吹き飛ばしてダメージの設定
//============================
bool CEnemy::SetBlowDamage(int damage, float rotY)
{
	//浮かせながら吹き飛ばす
	AddMove(D3DXVECTOR3(0.0f, 7.0f, 0.0f));
	D3DXVECTOR3 Blow = { sinf(rotY + D3DX_PI) * VALUE_BLOWOFF, 0.0f, cosf(rotY + D3DX_PI) * VALUE_BLOWOFF };
	SetBlowValue(Blow);
	SetOnStand(false);
	CEnemy::SetDamage(damage, rotY);

	//吹き飛び状態に変更
	ChangeState(new CState_Enemy_Blow(this));

	return true;
}

//============================
//吹き飛ばしてダメージの設定
//============================
bool CEnemy::SetBlowDamage(int damage, float rotY, float value)
{
	//浮かせながら吹き飛ばす
	AddMove(D3DXVECTOR3(0.0f, 7.0f, 0.0f));
	D3DXVECTOR3 Blow = { sinf(rotY + D3DX_PI) * value, 0.0f, cosf(rotY + D3DX_PI) * value };
	SetBlowValue(Blow);
	SetOnStand(false);
	SetDamage(damage, rotY);

	//吹き飛び状態に変更
	ChangeState(new CState_Enemy_Blow(this));

	return true;
}

//============================
//吹き飛び処理
//============================
bool CEnemy::SetBlowOff()
{
	//吹き飛ぶ処理
	CCharacter::SetMove(D3DXVECTOR3(0.0f, VALUE_BLOWOFF, 0.0f));	//移動量の設定
	SetOnStand(false);												//立っていない状態に設定
	SetEnableGravity(true);											//重力を受ける

	return true;
}

//============================
//状態の変更
//============================
void CEnemy::ChangeState(CState_Enemy* state)
{
	//チェック後に開放
	if (m_pState != nullptr)
	{
		delete m_pState;
	}
	
	m_pState = state;
}