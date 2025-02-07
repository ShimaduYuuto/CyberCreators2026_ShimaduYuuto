//======================================
//
//	ポーズの背景の処理[pause_bg.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "pause_bg.h"
#include "manager.h"
#include "game.h"

//定数
const std::string CPause_Bg::TEXTURE_PATH = "data\\TEXTURE\\pause_bg000.png";

//============================
//コンストラクタ
//============================
CPause_Bg::CPause_Bg(int nPriority) : CObject2D(nPriority)
{

}

//============================
//デストラクタ
//============================
CPause_Bg::~CPause_Bg()
{

}

//============================
//初期化
//============================
HRESULT CPause_Bg::Init()
{
	//初期化
	CObject2D::Init();

	SetPos({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f });
	SetSize({ SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f });
	SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f));

	return S_OK;
}

//============================
//終了処理
//============================
void CPause_Bg::Uninit()
{
	CObject2D::Uninit();
}

//============================
//更新
//============================
void CPause_Bg::Update()
{
	//更新処理
	CObject2D::Update();
}

//============================
//描画
//============================
void CPause_Bg::Draw()
{
	//描画処理
	CObject2D::Draw();
}

//============================
//クリエイト
//============================
CPause_Bg* CPause_Bg::Create()
{
	//ポインタ用の変数
	CPause_Bg* pPause_Bg;

	//メモリの確保
	pPause_Bg = new CPause_Bg;

	//初期化
	pPause_Bg->Init();

	return pPause_Bg;
}