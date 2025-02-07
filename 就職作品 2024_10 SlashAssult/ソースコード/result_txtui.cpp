//======================================
//
//	テキストUIの処理[result_txtui.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "result_txtui.h"

//定数
const std::string CResult_Txtui::TEXTUREPATH = "data\\TEXTURE\\cleartime000.png";
const D3DXVECTOR3 CResult_Txtui::POS = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.3f, 0.0f };
const D3DXVECTOR3 CResult_Txtui::SIZE = { 600.0f, 100.0f, 0.0f };

//============================
//背景のコンストラクタ
//============================
CResult_Txtui::CResult_Txtui(int nPriority) : CObject2D(nPriority)
{

}

//============================
//背景のデストラクタ
//============================
CResult_Txtui::~CResult_Txtui()
{

}

//============================
//背景の初期化
//============================
HRESULT CResult_Txtui::Init()
{
	//初期化
	CObject2D::Init();

	return S_OK;
}

//============================
//背景の終了処理
//============================
void CResult_Txtui::Uninit()
{
	CObject2D::Uninit();
}

//============================
//背景の更新
//============================
void CResult_Txtui::Update()
{
	CObject2D::Update();
}

//============================
//背景の描画
//============================
void CResult_Txtui::Draw()
{
	//描画処理
	CObject2D::Draw(TEXTUREPATH.c_str());
}

//============================
//背景のクリエイト
//============================
CResult_Txtui* CResult_Txtui::Create()
{
	//ポインタ用の変数
	CResult_Txtui* pResult_Txtui;

	//メモリの確保
	pResult_Txtui = new CResult_Txtui;

	//初期化
	pResult_Txtui->Init();
	pResult_Txtui->SetPos(POS);		//位置
	pResult_Txtui->SetSize(SIZE);	//サイズ

	return pResult_Txtui;
}