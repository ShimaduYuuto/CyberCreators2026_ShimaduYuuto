//======================================
//
//	スローゲージの処理[gauge_slow.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "gauge_slow.h"
#include "manager.h"
#include "game.h"

//定数の初期化
const std::string CGauge_Slow::TEXTUREPATH = "data\\TEXTURE\\gauge000.png";

//============================
//コンストラクタ
//============================
CGauge_Slow::CGauge_Slow(int nPriority) : CGauge(nPriority)
{
	
}

//============================
//デストラクタ
//============================
CGauge_Slow::~CGauge_Slow()
{
	
}

//============================
//初期化処理
//============================
HRESULT CGauge_Slow::Init()
{
	//初期化
	CObject2D::Init();

	return S_OK;
}

//============================
//終了処理
//============================
void CGauge_Slow::Uninit()
{
	//終了処理
	CGauge::Uninit();
}

//============================
//更新処理
//============================
void CGauge_Slow::Update()
{
	//ゲージの取得
	float fNowGauge = GetNowGauge();
	float fRate = 1.0f;
	D3DXVECTOR3 Size = m_MaxSize;

	//カウントダウン
	fNowGauge--;

	//割合からサイズを算出
	fRate = fNowGauge / GetMaxGauge();	//割合計算
	Size.x *= fRate;					//サイズを算出

	//サイズの設定
	SetSize(Size);

	//ゲージの設定
	SetNowGauge(fNowGauge);

	//オブジェクト2Dの更新
	CObject2D::Update();

	//0になったら
	if (fNowGauge <= 0)
	{
		CGauge::Uninit();
	}
}

//============================
//描画処理
//============================
void CGauge_Slow::Draw()
{
	//描画処理
	CObject2D::Draw();
}

//============================
//クリエイト
//============================
CGauge_Slow* CGauge_Slow::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float max)
{
	//ポインタ用の変数
	CGauge_Slow* pGauge_Slow;

	//メモリの確保
	pGauge_Slow = new CGauge_Slow;

	//パラメータの設定
	pGauge_Slow->SetPos(pos);
	pGauge_Slow->SetSize(size);
	pGauge_Slow->SetMaxGauge(max);
	pGauge_Slow->SetNowGauge(max);
	pGauge_Slow->m_MaxSize = size;

	//初期化
	pGauge_Slow->Init();

	return pGauge_Slow;
}