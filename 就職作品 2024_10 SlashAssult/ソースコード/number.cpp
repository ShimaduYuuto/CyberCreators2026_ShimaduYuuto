//======================================
//
//	スコアの描画[score.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "number.h"
#include "manager.h"
#include "game.h"

//定数の初期化
const std::string CNumber::TEXTUREPATH = "data\\TEXTURE\\number001.png";

//定数
static const float NUMBER_SIZE_X = 70.0f;
static const float NUMBER_SIZE_Y = 120.0f;

//============================
//数字のコンストラクタ
//============================
CNumber::CNumber(int nPriority) : CObject2D(nPriority)
{

}

//============================
//数字のデストラクタ
//============================
CNumber::~CNumber()
{

}

//============================
//数字の初期化
//============================
HRESULT CNumber::Init()
{
	//初期化
	CObject2D::Init();

	//UV座標の設定（初期化）
	CObject2D::SetTextureUV(0.0f, 0.1f, 0.0f, 1.0f);

	return S_OK;
}

//============================
//数字の初期化
//============================
void CNumber::Uninit()
{
	//初期化
	CObject2D::Uninit();
}

//============================
//数字の更新
//============================
void CNumber::Update()
{
	CObject2D::Update();
}

//============================
//数字の描画
//============================
void CNumber::Draw()
{
	//描画
	CObject2D::Draw(CNumber::TEXTUREPATH.c_str());
}

//============================
//数字のクリエイト
//============================
CNumber* CNumber::Create(D3DXVECTOR3 pos, int number)
{
	//ポインタ用の変数
	CNumber* pNumber = nullptr;

	//メモリの確保
	pNumber = new CNumber;

	//初期化
	pNumber->Init();

	//位置の設定
	pNumber->SetPos(pos);

	//サイズの設定
	pNumber->SetSize({ NUMBER_SIZE_X, NUMBER_SIZE_Y, 0.0f});

	//テクスチャの設定
	pNumber->SetTexture(0);

	return pNumber;
}

//============================
//数字のテクスチャ設定
//============================
void CNumber::SetTexture(int Num)
{
	//UV座標の設定
	CObject2D::SetTextureUV(Num / 10.0f, (Num + 1) / 10.0f, 0.0f, 1.0f);
}