//======================================
//
//	コロンの処理[colon.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "colon.h"

//定数
const std::string CColon::TEXTURE_PATH = "data\\TEXTURE\\colon000.png";

//============================
//コロンのコンストラクタ
//============================
CColon::CColon(int nPriority) : CObject2D(nPriority)
{

}

//============================
//コロンのデストラクタ
//============================
CColon::~CColon()
{

}

//============================
//コロンの初期化
//============================
HRESULT CColon::Init()
{
	//初期化
	CObject2D::Init();

	return S_OK;
}

//============================
//コロンの終了処理
//============================
void CColon::Uninit()
{
	CObject2D::Uninit();
}

//============================
//コロンの更新
//============================
void CColon::Update()
{
	//更新処理
	CObject2D::Update();
}

//============================
//コロンの描画
//============================
void CColon::Draw()
{
	//描画処理
	CObject2D::Draw(TEXTURE_PATH.c_str());
}

//============================
//コロンのクリエイト
//============================
CColon* CColon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//ポインタ用の変数
	CColon* pColon;

	//メモリの確保
	pColon = new CColon;

	//初期化
	pColon->Init();
	pColon->SetPos(pos);	//位置
	pColon->SetSize(size);	//サイズ

	return pColon;
}