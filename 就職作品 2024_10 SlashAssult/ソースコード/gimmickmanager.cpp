//======================================
//
//	ギミックの管理をする処理[gimmickmanager.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "gimmickmanager.h"
#include "manager.h"

//============================
//コンストラクタ
//============================
CGimmickManager::CGimmickManager() :
	m_apManager()
{
	m_apManager.clear();
}

//============================
//デストラクタ
//============================
CGimmickManager::~CGimmickManager()
{
	m_apManager.clear();
}

//============================
//初期化
//============================
HRESULT CGimmickManager::Init()
{
	return S_OK;
}

//============================
//終了処理
//============================
void CGimmickManager::Uninit()
{
	m_apManager.clear();
}

//============================
//登録処理
//============================
void CGimmickManager::Regist(CGimmick* gimmick)
{
	//敵の情報を登録
	m_apManager.push_back(gimmick);
}

//============================
//削除処理
//============================
void CGimmickManager::Erase(CGimmick* gimmick)
{
	//サイズが0なら抜ける
	if (m_apManager.size() == 0)
	{
		return;
	}

	//登録済みか
	bool bRegisted = false;

	//同じものが無いかを確認
	for (auto itr : m_apManager)
	{
		if (itr == gimmick)
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

	//ギミックの情報を削除
	m_apManager.remove(gimmick);
}