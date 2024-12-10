//======================================
//
//	演出の処理[direction.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "direction.h"
#include "direction_boss.h"

//============================
//演出のコンストラクタ
//============================
CDirection::CDirection() :
	m_nCount(0),
	m_nEndTime(0)
{
	
}

//============================
//演出のデストラクタ
//============================
CDirection::~CDirection()
{

}

//============================
//演出の初期化
//============================
HRESULT CDirection::Init()
{
	return S_OK;
}

//============================
//演出の更新
//============================
bool CDirection::TimeUpdate()
{
	m_nCount++;

	//終了時間を超えたら
	if (m_nCount > m_nEndTime)
	{
		return true;
	}

	return false;
}

//============================
//演出の生成
//============================
CDirection* CDirection::Create(DIRECTIONTYPE type)
{
	//種類に応じて動的確保
	CDirection* pDirction = nullptr;

	switch (type)
	{
	case DIRECTIONTYPE_BOSS:	//通常の敵

		//敵のメモリ確保
		pDirction = new CDirection_Boss();
		break;

	default:
		assert(true);
		break;

	}

	//設定した情報を返す
	return pDirction;
}