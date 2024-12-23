//======================================
//
//	ランクのUIの処理[rank.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "rank.h"

const std::string CRank::TEXTUREPATH = "data\\TEXTURE\\rank001.png";
const D3DXVECTOR3 CRank::POS = { 880.0f, 510.0f, 0.0f };
const D3DXVECTOR3 CRank::SIZE = { 200.0f, 200.0f, 0.0f };

//============================
//ランクのUIのコンストラクタ
//============================
CRank::CRank(int nPriority) : CObject2D(nPriority)
{

}

//============================
//ランクのUIのデストラクタ
//============================
CRank::~CRank()
{

}

//============================
//ランクのUIの初期化
//============================
HRESULT CRank::Init()
{
	//初期化
	CObject2D::Init();

	//パラメータの設定
	SetPos(POS);	//位置
	SetSize(SIZE);	//サイズ
	SetTextureUV(0.0f, 1.0f / 5.0f, 0.0f, 1.0f);	//UV座標

	return S_OK;
}

//============================
//ランクのUIの終了処理
//============================
void CRank::Uninit()
{
	CObject2D::Uninit();
}

//============================
//ランクのUIの更新
//============================
void CRank::Update()
{

}

//============================
//ランクのUIの描画
//============================
void CRank::Draw()
{
	//描画処理
	CObject2D::Draw(TEXTUREPATH.c_str());
}

//============================
//ランクのUIのクリエイト
//============================
CRank* CRank::Create()
{
	//ポインタ用の変数
	CRank* pRank;

	//メモリの確保
	pRank = new CRank;

	//初期化
	pRank->Init();

	return pRank;
}