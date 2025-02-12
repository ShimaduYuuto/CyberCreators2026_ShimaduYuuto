//======================================
//
//	タイトルカメラの処理[camera_title.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "camera_title.h"

//定数
const D3DXVECTOR3 CCamera_Title::POSV = { -30.0f, 30.0f, -100.0f };
const D3DXVECTOR3 CCamera_Title::POSR = { -30.0f, 20.0f, 0.0f };

//============================
//カメラのコンストラクタ
//============================
CCamera_Title::CCamera_Title()
{

}

//============================
//カメラのデストラクタ
//============================
CCamera_Title::~CCamera_Title()
{

}

//============================
//カメラの初期化
//============================
HRESULT CCamera_Title::Init()
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
void CCamera_Title::Uninit()
{

}

//============================
//カメラの更新処理
//============================
void CCamera_Title::Update()
{
	
}