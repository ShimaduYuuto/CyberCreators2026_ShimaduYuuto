//======================================
//
//	背景の処理[result_bg.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "result_bg.h"

//定数
const std::string CResult_Bg::TEXTURE_PATH = "data\\TEXTURE\\result001.png";

//============================
//背景のコンストラクタ
//============================
CResult_Bg::CResult_Bg(int nPriority) : CObject2D(nPriority)
{

}

//============================
//背景のデストラクタ
//============================
CResult_Bg::~CResult_Bg()
{

}

//============================
//背景の初期化
//============================
HRESULT CResult_Bg::Init()
{
	//初期化
	CObject2D::Init();

	return S_OK;
}

//============================
//背景の終了処理
//============================
void CResult_Bg::Uninit()
{
	CObject2D::Uninit();
}

//============================
//背景の更新
//============================
void CResult_Bg::Update()
{
	CObject2D::Update();
}

//============================
//背景の描画
//============================
void CResult_Bg::Draw()
{
	//描画処理
	CObject2D::Draw(TEXTURE_PATH.c_str());
}

//============================
//背景のクリエイト
//============================
CResult_Bg* CResult_Bg::Create()
{
	//ポインタ用の変数
	CResult_Bg* pResult_Bg;

	//メモリの確保
	pResult_Bg = new CResult_Bg;

	//初期化
	pResult_Bg->Init();
	pResult_Bg->SetPos({SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f});	//位置
	pResult_Bg->SetSize({ WIDTH, HEIGHT, 0.0f });	//サイズ

	return pResult_Bg;
}