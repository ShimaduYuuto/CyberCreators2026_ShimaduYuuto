//======================================
//
//	古い紙のUIの処理[oldpaper.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "oldpaper.h"
#include "manager.h"

const std::string COldPaper::TEXTUREPATH = "data\\TEXTURE\\oldpaper002.png";
const D3DXVECTOR3 COldPaper::POS = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f };
const D3DXVECTOR3 COldPaper::SIZE = { SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.8f, 0.0f };

//============================
//古い紙のUIのコンストラクタ
//============================
COldPaper::COldPaper(int nPriority) : CObject2D(nPriority)
{

}

//============================
//古い紙のUIのデストラクタ
//============================
COldPaper::~COldPaper()
{

}

//============================
//古い紙のUIの初期化
//============================
HRESULT COldPaper::Init()
{
	//初期化
	CObject2D::Init();

	//パラメータの設定
	SetPos(POS);	//位置
	SetSize(SIZE);	//サイズ

	return S_OK;
}

//============================
//古い紙のUIの終了処理
//============================
void COldPaper::Uninit()
{
	CObject2D::Uninit();
}

//============================
//古い紙のUIの更新
//============================
void COldPaper::Update()
{
	
}

//============================
//古い紙のUIの描画
//============================
void COldPaper::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得

	//テクスチャ拡大時に色を近似値にする
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);

	//描画処理
	CObject2D::Draw(TEXTUREPATH.c_str());

	//テクスチャ拡大時の色を線形補間
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
}

//============================
//古い紙のUIのクリエイト
//============================
COldPaper* COldPaper::Create()
{
	//ポインタ用の変数
	COldPaper* pOldPaper;

	//メモリの確保
	pOldPaper = new COldPaper;

	//初期化
	pOldPaper->Init();

	return pOldPaper;
}