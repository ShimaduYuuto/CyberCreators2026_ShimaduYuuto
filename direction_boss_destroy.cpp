//======================================
//
//	演出の処理[direction_boss.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "direction_boss_destroy.h"
#include "manager.h"

const D3DXVECTOR3 CDirection_Boss_Destroy::CAMERA_POSR = { 0.0f, 100.0f, 3500.0f };
const D3DXVECTOR3 CDirection_Boss_Destroy::CAMERA_POSV = { 0.0f, 100.0f, 3300.0f };

//============================
//演出のコンストラクタ
//============================
CDirection_Boss_Destroy::CDirection_Boss_Destroy()
{
	//カメラの位置を固定
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	pCamera->SetPosR(CAMERA_POSR);
	pCamera->SetPosV(CAMERA_POSV);

	//終了時間
	SetEndTime(END_TIME);
}

//============================
//演出のデストラクタ
//============================
CDirection_Boss_Destroy::~CDirection_Boss_Destroy()
{

}

//============================
//演出の初期化
//============================
HRESULT CDirection_Boss_Destroy::Init()
{
	return S_OK;
}

//============================
//演出の更新
//============================
bool CDirection_Boss_Destroy::TimeUpdate()
{
	//揺らす時間
	if (GetCount() == START_SHAKE_FRAME)
	{
		//カメラを揺らす
		CCamera* pCamera = CManager::GetInstance()->GetCamera();
		pCamera->SetShake(SHAKE_FRAME, SHAKE_MAGNITUDE);
	}

	//演出の更新
	return CDirection::TimeUpdate();
}