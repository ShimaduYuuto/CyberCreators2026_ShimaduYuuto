//======================================
//
//	ロゴの処理[title_logo.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "title_logo.h"

//定数
const std::string CTitle_Logo::TEXTURE_PATH = "data\\TEXTURE\\title001.png";

//============================
//ロゴのコンストラクタ
//============================
CTitle_Logo::CTitle_Logo(int nPriority) : CObject2D(nPriority)
{

}

//============================
//ロゴのデストラクタ
//============================
CTitle_Logo::~CTitle_Logo()
{

}

//============================
//ロゴの初期化
//============================
HRESULT CTitle_Logo::Init()
{
	//初期化
	CObject2D::Init();

	return S_OK;
}

//============================
//ロゴの終了処理
//============================
void CTitle_Logo::Uninit()
{
	CObject2D::Uninit();
}

//============================
//ロゴの更新
//============================
void CTitle_Logo::Update()
{
	CObject2D::Update();
}

//============================
//ロゴの描画
//============================
void CTitle_Logo::Draw()
{
	//描画処理
	CObject2D::Draw(TEXTURE_PATH.c_str());
}

//============================
//ロゴのクリエイト
//============================
CTitle_Logo* CTitle_Logo::Create(D3DXVECTOR3 pos)
{
	//ポインタ用の変数
	CTitle_Logo* pTitle_Logo;

	//メモリの確保
	pTitle_Logo = new CTitle_Logo;

	//初期化
	pTitle_Logo->Init();
	pTitle_Logo->SetPos(pos);	//位置
	pTitle_Logo->SetSize({WIDTH, HEIGHT, 0.0f});	//サイズ
	pTitle_Logo->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });

	return pTitle_Logo;
}