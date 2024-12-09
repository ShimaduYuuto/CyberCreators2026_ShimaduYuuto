//======================================
//
//	バトルエリアの処理[battleareamanager.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "battleareamanager.h"
#include "battlearea000.h"
#include "battlearea001.h"
#include "battlearea002.h"
#include "battlearea003.h"
#include "game.h"
#include "manager.h"

//============================
//コンストラクタ
//============================
CBattleAreaManager::CBattleAreaManager() :
	m_BattleAreaList(),
	m_pCurrentBattleArea(nullptr)
{
	m_BattleAreaList.clear();
}

//============================
//デストラクタ
//============================
CBattleAreaManager::~CBattleAreaManager()
{
	m_BattleAreaList.clear();
}

//============================
//初期化
//============================
HRESULT CBattleAreaManager::Init()
{
	//読み込み
	Load();
	m_pCurrentBattleArea = nullptr;
	return S_OK;
}

//============================
//終了処理
//============================
void CBattleAreaManager::Uninit()
{
	m_BattleAreaList.clear();
	m_pCurrentBattleArea = nullptr;
}

//============================
//更新
//============================
void CBattleAreaManager::Update()
{
	//リストのエリアを更新
	for (auto itr : m_BattleAreaList)
	{
		itr->Update();	//更新
		
		//死亡判定が立っていたら消去
		if (itr->GetEnd())
		{
			itr->Uninit();
		}
	}

	//エリアの終了確認
	if (m_pCurrentBattleArea != nullptr)
	{
		if (m_pCurrentBattleArea->GetEnd())
		{
			//リストから削除
			Erase(m_pCurrentBattleArea);
		}
	}

	//残りのエリアが無くなったらクリア判定にする(一旦)
	if (m_BattleAreaList.size() == 0)
	{
		//ゲームシーンの取得
		CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();
		pGame->SetClear(true);
	}
}

//============================
//読み込み
//============================
void CBattleAreaManager::Load()
{
	m_BattleAreaList.clear();

	//エリアの生成
	Regist(CBattleArea::Create({ 0.0f, 0.0f, 500.0f }, new CBattleArea000));
	Regist(CBattleArea::Create({ 0.0f, 0.0f, 1500.0f }, new CBattleArea001));
	Regist(CBattleArea::Create({ 0.0f, 0.0f, 2500.0f }, new CBattleArea002));
	Regist(CBattleArea::Create({ 0.0f, 0.0f, 3500.0f }, new CBattleArea003));
}

//============================
//登録処理
//============================
void CBattleAreaManager::Regist(CBattleArea* area)
{
	//登録済みか
	bool bRegisted = false;

	//同じものが無いかを確認
	for (auto itr : m_BattleAreaList)
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
	m_BattleAreaList.push_back(area);
}

//============================
//削除処理
//============================
void CBattleAreaManager::Erase(CBattleArea* area)
{
	//サイズが0なら抜ける
	if (m_BattleAreaList.size() == 0)
	{
		return;
	}

	//登録済みか
	bool bRegisted = false;

	//同じものが無いかを確認
	for (auto itr : m_BattleAreaList)
	{
		if (itr == area)
		{
			bRegisted = true;
			break;
		}
	}

	//登録されていないなら抜ける
	if (!bRegisted)
	{
		return;
	}

	//現在のエリアならnullptrにする
	if (m_pCurrentBattleArea == area)
	{
		delete m_pCurrentBattleArea;
		m_pCurrentBattleArea = nullptr;
	}

	//エリアの情報を削除
	m_BattleAreaList.remove(area);
}