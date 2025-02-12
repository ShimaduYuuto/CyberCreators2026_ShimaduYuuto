//======================================
//
//	リザルトカメラの処理[camera_result.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "camera_result.h"

//定数
const D3DXVECTOR3 CCamera_Result::POSV = { 0.0f, 100.0f, -300.0f };
const D3DXVECTOR3 CCamera_Result::POSR = { 0.0f, 20.0f, 0.0f };

//============================
//カメラのコンストラクタ
//============================
CCamera_Result::CCamera_Result()
{

}

//============================
//カメラのデストラクタ
//============================
CCamera_Result::~CCamera_Result()
{

}

//============================
//カメラの初期化
//============================
HRESULT CCamera_Result::Init()
{
	//基底の初期化
	CCamera::Init();

	//取得
	D3DXVECTOR3 PosR = GetPosR();
	D3DXVECTOR3 PosV = GetPos();

	//代入
	PosV = POSV;		//視点
	PosR = POSR;		//注視点

	//設定
	SetPosR(PosR);
	SetPosV(PosV);

	return S_OK;
}

//============================
//カメラの終了処理
//============================
void CCamera_Result::Uninit()
{

}

//============================
//カメラの更新処理
//============================
void CCamera_Result::Update()
{

}