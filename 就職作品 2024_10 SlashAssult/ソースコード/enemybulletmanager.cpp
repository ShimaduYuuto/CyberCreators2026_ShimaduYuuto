//======================================
//
//	エネミー弾の管理をする処理[enemybulletmanager.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "enemybulletmanager.h"
#include "manager.h"

//============================
//コンストラクタ
//============================
CEnemyBulletManager::CEnemyBulletManager() :
	m_apManager()	//管理している弾のリスト
{
	//リストのクリア
	m_apManager.clear();
}

//============================
//デストラクタ
//============================
CEnemyBulletManager::~CEnemyBulletManager()
{

}

//============================
//初期化
//============================
HRESULT CEnemyBulletManager::Init()
{
	return S_OK;
}

//============================
//終了処理
//============================
void CEnemyBulletManager::Uninit()
{
	//リストのクリア
	m_apManager.clear();
}

//============================
//登録処理
//============================
void CEnemyBulletManager::Regist(CEnemyBullet* enemybullet)
{
	//敵の情報を登録
	m_apManager.push_back(enemybullet);
}

//============================
//削除処理
//============================
void CEnemyBulletManager::Erase(CEnemyBullet* enemybullet)
{
	//サイズが0なら抜ける
	if (m_apManager.size() == 0)
	{
		return;
	}
	//敵の情報を削除
	m_apManager.remove(enemybullet);
}