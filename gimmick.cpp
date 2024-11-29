//======================================
//
//	ギミックの処理[gimmick.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "gimmick.h"
#include "manager.h"
#include "game.h"

//============================
//コンストラクタ
//============================
CGimmick::CGimmick(int nPriority) : CObjectX(nPriority),
m_Collision(nullptr)
{
	//ゲームシーンの取得
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

	//マネージャーに登録
	pGame->GetGimmickManager()->Regist(this);
}

//============================
//デストラクタ
//============================
CGimmick::~CGimmick()
{
	//ゲームシーンの取得
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

	//マネージャーから削除
	if (pGame->GetGimmickManager() != nullptr)
	{
		pGame->GetGimmickManager()->Erase(this);
	}	

	//当たり判定の消去
	if (m_Collision != nullptr)
	{
		m_Collision->Uninit();
		m_Collision = nullptr;
	}
}

//============================
//初期化
//============================
HRESULT CGimmick::Init()
{
	//初期化
	CObjectX::Init();

	//当たり判定の生成
	if (m_Collision == nullptr)
	{
		m_Collision = CCollision::Create(20.0f, D3DXVECTOR3(0.0f, 30.0f, 0.0f));
	}

	return S_OK;
}

//============================
//終了処理
//============================
void CGimmick::Uninit()
{
	//当たり判定の消去
	/*if (m_Collision != nullptr)
	{
		m_Collision->Uninit();
		m_Collision = nullptr;
	}*/

	//初期化
	CObjectX::Uninit();
}

//============================
//更新
//============================
void CGimmick::Update()
{
	//ゲームオブジェクトの共通処理更新
	CObjectX::Update();
	m_Collision->Update(GetPos());
}