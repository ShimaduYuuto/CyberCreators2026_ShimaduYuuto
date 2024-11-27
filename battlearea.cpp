//======================================
//
//	エネミーの管理をする処理[battlearea.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "battlearea.h"
#include "manager.h"

//============================
//コンストラクタ
//============================
CBattleArea::CBattleArea() :
	m_apArea()
{
	m_apArea.clear();
}

//============================
//デストラクタ
//============================
CBattleArea::~CBattleArea()
{
	m_apArea.clear();
}

//============================
//初期化
//============================
HRESULT CBattleArea::Init()
{
	return S_OK;
}

//============================
//終了処理
//============================
void CBattleArea::Uninit()
{
	m_apArea.clear();
}