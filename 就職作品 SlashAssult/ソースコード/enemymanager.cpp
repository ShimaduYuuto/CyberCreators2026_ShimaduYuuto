//======================================
//
//	エネミーの管理をする処理[enemymanager.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "enemymanager.h"
#include "manager.h"

//============================
//コンストラクタ
//============================
CEnemyManager::CEnemyManager():
	m_apManager()
{
	m_apManager.clear();
}

//============================
//デストラクタ
//============================
CEnemyManager::~CEnemyManager()
{

}

//============================
//初期化
//============================
HRESULT CEnemyManager::Init()
{
	return S_OK;
}

//============================
//終了処理
//============================
void CEnemyManager::Uninit()
{
	m_apManager.clear();
}

//============================
//登録処理
//============================
void CEnemyManager::Regist(CEnemy* enemy)
{
	//敵の情報を登録
	m_apManager.push_back(enemy);
}

//============================
//削除処理
//============================
void CEnemyManager::Erase(CEnemy* enemy)
{
	//サイズが0なら抜ける
	if (m_apManager.size() == 0)
	{
		return;
	}
	//敵の情報を削除
	m_apManager.remove(enemy);
}