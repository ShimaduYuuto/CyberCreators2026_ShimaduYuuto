//======================================
//
//	ランクのUIの処理[rank.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "rank.h"
#include "cleartime.h"

const std::string CRank::TEXTUREPATH = "data\\TEXTURE\\rank001.png";
const D3DXVECTOR3 CRank::POS = { 870.0f, 510.0f, 0.0f };
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

	//時間からランクを設定
	int nRank = CClearTime::GetInstance()->GetTime() - TIME_RANKS;

	if (nRank < 0) { nRank = 0; }	//自然数に補正
	nRank = nRank / TIME_CARRYUP;	//小数点を切り捨て

	if (nRank > NUM_RANK - 1) { nRank = NUM_RANK - 1; }	//最低値を下回ったら補正
	float fTextureU = 1.0f / NUM_RANK;					//U座標を算出

	SetTextureUV(fTextureU * nRank, fTextureU * (nRank + 1), 0.0f, 1.0f);	//UV座標

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