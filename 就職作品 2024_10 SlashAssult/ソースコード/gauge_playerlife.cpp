//======================================
//
//	ゲージの処理[gauge_playerlife.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "gauge_playerlife.h"
#include "manager.h"
#include "game.h"

//定数の宣言
const std::string CGauge_PlayerLife::TEXTURE_PATH = "data\\TEXTURE\\gauge001.png";
const D3DXVECTOR3 CGauge_PlayerLife::POS = { 150.0f, 50.0f, 0.0f };			//位置
const D3DXVECTOR3 CGauge_PlayerLife::SIZE = { 200.0f, 20.0f, 0.0f };		//ゲージ枠のサイズ
const D3DXVECTOR3 CGauge_PlayerLife::SIZE_GAUGE = { 173.0f, 20.0f, 0.0f };	//ゲージのサイズ

//============================
//コンストラクタ
//============================
CGauge_PlayerLife::CGauge_PlayerLife(int nPriority) : CObject2D(nPriority),
	m_pGauge(nullptr)	//ゲージのポインタ
{

}

//============================
//デストラクタ
//============================
CGauge_PlayerLife::~CGauge_PlayerLife()
{

}

//============================
//初期化
//============================
HRESULT CGauge_PlayerLife::Init()
{
	//初期化
	CObject2D::Init();

	return S_OK;
}

//============================
//終了処理
//============================
void CGauge_PlayerLife::Uninit()
{
	//ゲージの破棄
	if (m_pGauge != nullptr)
	{
		//ゲージの生成
		m_pGauge->Uninit();
		m_pGauge = nullptr;
	}

	CObject2D::Uninit();
}

//============================
//更新
//============================
void CGauge_PlayerLife::Update()
{
	//更新処理
	CObject2D::Update();
}

//============================
//描画
//============================
void CGauge_PlayerLife::Draw()
{
	//描画処理
	CObject2D::Draw(TEXTURE_PATH.c_str());
}

//============================
//クリエイト
//============================
CGauge_PlayerLife* CGauge_PlayerLife::Create(float max)
{
	//ポインタ用の変数
	CGauge_PlayerLife* pGauge_PlayerLife;

	//メモリの確保
	pGauge_PlayerLife = new CGauge_PlayerLife;

	//初期化
	pGauge_PlayerLife->Init();			//初期化
	pGauge_PlayerLife->SetPos(POS);		//位置
	pGauge_PlayerLife->SetSize(SIZE);	//サイズ
	pGauge_PlayerLife->SetGauge(max);	//ゲージの設定

	return pGauge_PlayerLife;
}

//============================
//ゲージの設定処理
//============================
void CGauge_PlayerLife::SetGauge(float max)
{
	//ゲージのポインタを持っていないなら生成
	if (m_pGauge == nullptr)
	{
		//ゲージの生成
		m_pGauge = CLifeGauge::Create(POS, SIZE_GAUGE, max);
		m_pGauge->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	}
	else //すでにゲージがあるならパラメータを設定
	{
		m_pGauge->SetPos(POS);		//位置
		m_pGauge->SetSize(SIZE);	//サイズ
		m_pGauge->SetMaxGauge(max);	//ゲージの最大
	}
}