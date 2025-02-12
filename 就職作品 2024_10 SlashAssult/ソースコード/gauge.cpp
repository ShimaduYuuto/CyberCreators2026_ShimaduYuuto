//======================================
//
//	ゲージの処理[gauge.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "gauge.h"
#include "manager.h"
#include "game.h"

//============================
//ゲージのコンストラクタ
//============================
CGauge::CGauge(int nPriority) : CObject2D(nPriority),
	m_fMaxGauge(0.0f),
	m_fNowGauge(0.0f)
{

}

//============================
//ゲージのデストラクタ
//============================
CGauge::~CGauge()
{

}

//============================
//ゲージの初期化
//============================
HRESULT CGauge::Init()
{
	//初期化
	CObject2D::Init();

	return S_OK;
}

//============================
//ゲージの終了処理
//============================
void CGauge::Uninit()
{
	CObject2D::Uninit();
}

//============================
//ゲージの更新
//============================
void CGauge::Update()
{
	//更新処理
	CObject2D::Update(m_fMaxGauge, m_fNowGauge);
}

//============================
//ゲージの描画
//============================
void CGauge::Draw()
{
	//描画処理
	CObject2D::Draw();
}

//============================
//ゲージのクリエイト
//============================
CGauge* CGauge::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float max)
{
	//ポインタ用の変数
	CGauge* pGauge;

	//メモリの確保
	pGauge = new CGauge;

	//初期化
	pGauge->Init();
	pGauge->SetPos(pos);	//位置
	pGauge->SetSize(size);	//サイズ
	pGauge->SetMaxGauge(max);	//ゲージの最大値を設定
	pGauge->SetNowGauge(max);	//ゲージの現在値を設定

	return pGauge;
}

//============================
//ゲージの設定
//============================
void CGauge::SetNowGauge(float value)
{
	//上限超えていたら最大値にする
	if (value > m_fMaxGauge)
	{
		m_fNowGauge = m_fMaxGauge;
	}
	else if (value < 0.0f)	//値が最低値を下回ったら補正
	{
		m_fNowGauge = 0.0f;
	}
	else
	{
		m_fNowGauge = value;
	}
}

//============================
//ゲージの加算
//============================
void CGauge::AddGauge(float value)
{
	//加算
	m_fNowGauge += value;

	//上限超えていたら最大値にする
	if (m_fNowGauge > m_fMaxGauge)
	{
		m_fNowGauge = m_fMaxGauge;
	}
	else if (m_fNowGauge < 0.0f)	//値が最低値を下回ったら補正
	{
		m_fNowGauge = 0.0f;
	}
}