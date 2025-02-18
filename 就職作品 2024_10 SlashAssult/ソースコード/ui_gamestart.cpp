//======================================
//
//	UIの処理[ui_gamestart.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "ui_gamestart.h"

//定数
const std::string CUi_GameStart::TEXTURE_PATH = "data\\TEXTURE\\GameStart001.png";
const D3DXVECTOR3 CUi_GameStart::POS = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.7f, 0.0f };

//============================
//UIのコンストラクタ
//============================
CUi_GameStart::CUi_GameStart(int nPriority) : CObject2D(nPriority),
	m_fCurrentAlpha(1.0f),
	m_fAddAlpha(0.0f)
{

}

//============================
//UIのデストラクタ
//============================
CUi_GameStart::~CUi_GameStart()
{

}

//============================
//UIの初期化
//============================
HRESULT CUi_GameStart::Init()
{
	//初期化
	CObject2D::Init();

	return S_OK;
}

//============================
//UIの終了処理
//============================
void CUi_GameStart::Uninit()
{
	CObject2D::Uninit();
}

//============================
//UIの更新
//============================
void CUi_GameStart::Update()
{
	//α値の更新
	m_fCurrentAlpha += m_fAddAlpha;

	//加算減算の確認
	if (m_fCurrentAlpha >= 1.0f)
	{
		m_fCurrentAlpha = 1.0f;
		m_fAddAlpha = -ADD_ALPHA;
	}
	else if (m_fCurrentAlpha <= 0.0f)
	{
		m_fCurrentAlpha = 0.0f;
		m_fAddAlpha = ADD_ALPHA;
	}

	//色の設定
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fCurrentAlpha));

	CObject2D::Update();
}

//============================
//UIの描画
//============================
void CUi_GameStart::Draw()
{
	//描画処理
	CObject2D::Draw(TEXTURE_PATH.c_str());
}

//============================
//UIのクリエイト
//============================
CUi_GameStart* CUi_GameStart::Create()
{
	//ポインタ用の変数
	CUi_GameStart* pUi_GameStart;

	//メモリの確保
	pUi_GameStart = new CUi_GameStart;

	//初期化
	pUi_GameStart->Init();
	pUi_GameStart->SetPos(POS);	//位置
	pUi_GameStart->SetSize({ WIDTH, HEIGHT, 0.0f });	//サイズ
	pUi_GameStart->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });

	return pUi_GameStart;
}