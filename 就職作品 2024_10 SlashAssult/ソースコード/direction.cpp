//======================================
//
//	演出の処理[direction.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "direction.h"
#include "direction_boss.h"
#include "direction_boss_destroy.h"

//============================
//演出のコンストラクタ
//============================
CDirection::CDirection() :
	m_nCount(0),
	m_nEndTime(0),
	m_pLetterBox(nullptr)
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
	case DIRECTIONTYPE_BOSS:	//ボスの登場時の演出

		//敵のメモリ確保
		pDirction = new CDirection_Boss();
		break;

	case DIRECTIONTYPE_BOSS_DESTROY:	//ボスの撃破時の演出

		//敵のメモリ確保
		pDirction = new CDirection_Boss_Destroy();
		break;

	default:
		assert(true);
		break;

	}

	//初期化
	pDirction->Init();

	//設定した情報を返す
	return pDirction;
}

//============================
//終了時間の設定
//============================
void CDirection::SetEndTime(int time)
{
	//時間の設定
	m_nEndTime = time;

	//レターボックスの生成
	if (m_pLetterBox == nullptr)
	{
		m_pLetterBox = CLetterBox::Create(time);
	}
}