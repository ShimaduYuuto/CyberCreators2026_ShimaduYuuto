//======================================
//
//	結界の処理[barriermanager.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "barriermanager.h"
#include "game.h"
#include "manager.h"

//============================
//コンストラクタ
//============================
CBarrierManager::CBarrierManager()
{
	m_BarrierList.clear();
}

//============================
//デストラクタ
//============================
CBarrierManager::~CBarrierManager()
{
	m_BarrierList.clear();
}

//============================
//初期化
//============================
HRESULT CBarrierManager::Init()
{
	//読み込み
	Load();
	return S_OK;
}

//============================
//終了処理
//============================
void CBarrierManager::Uninit()
{
	m_BarrierList.clear();
}

//============================
//更新
//============================
void CBarrierManager::Update()
{
	//リストのエリアを更新
	for (auto itr : m_BarrierList)
	{
		itr->Update();	//更新
	}
}

//============================
//読み込み
//============================
void CBarrierManager::Load()
{
	m_BarrierList.clear();

	//結界の生成
	Regist(CBarrier::Create({ 0.0f, 150.0f, 1000.0f }));
	Regist(CBarrier::Create({ 0.0f, 150.0f, 2000.0f }));
	Regist(CBarrier::Create({ 0.0f, 150.0f, 3000.0f }));
}

//============================
//登録処理
//============================
void CBarrierManager::Regist(CBarrier* area)
{
	//登録済みか
	bool bRegisted = false;

	//同じものが無いかを確認
	for (auto itr : m_BarrierList)
	{
		if (itr == area)
		{
			bRegisted = true;
			break;
		}
	}

	//登録済みなら抜ける
	if (bRegisted)
	{
		return;
	}

	//敵の情報を登録
	m_BarrierList.push_back(area);
}

//============================
//削除処理
//============================
void CBarrierManager::Erase()
{
	//サイズが0なら抜ける
	if (m_BarrierList.size() == 0)
	{
		return;
	}

	//登録済みか
	bool bRegisted = false;

	//同じものが無いかを確認
	/*for (auto itr : m_BarrierList)
	{
		if (itr == area)
		{
			bRegisted = true;
			break;
		}
	}*/

	//登録されていないなら抜ける
	if (!bRegisted)
	{
		//return;
	}

	//エリアの情報を削除
	m_BarrierList.front()->Uninit();
	m_BarrierList.pop_front();
}