//======================================
//
//	爆発の管理をする処理[explosionmanager.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "explosionmanager.h"
#include "manager.h"

//============================
//コンストラクタ
//============================
CExplosionManager::CExplosionManager() :
	m_apManager()
{
	m_apManager.clear();
}

//============================
//デストラクタ
//============================
CExplosionManager::~CExplosionManager()
{

}

//============================
//初期化
//============================
HRESULT CExplosionManager::Init()
{
	return S_OK;
}

//============================
//終了処理
//============================
void CExplosionManager::Uninit()
{
	m_apManager.clear();
}

//============================
//登録処理
//============================
void CExplosionManager::Regist(CExplosion* explosion)
{
	//敵の情報を登録
	m_apManager.push_back(explosion);
}

//============================
//削除処理
//============================
void CExplosionManager::Erase(CExplosion* explosion)
{
	//サイズが0なら抜ける
	if (m_apManager.size() == 0)
	{
		return;
	}
	//敵の情報を削除
	m_apManager.remove(explosion);
}