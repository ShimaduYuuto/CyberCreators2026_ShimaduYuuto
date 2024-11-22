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
	//敵の情報を削除
	m_apManager.remove(gimmick);
}