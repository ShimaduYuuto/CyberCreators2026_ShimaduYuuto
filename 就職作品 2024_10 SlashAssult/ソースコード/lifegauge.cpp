//======================================
//
//	体力ゲージの処理[lifegauge.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "lifegauge.h"
#include "manager.h"
#include "game.h"

const std::string CLifeGauge::TEXTUREPATH = "data\\TEXTURE\\LifeGauge.png";

//============================
//ゲージのコンストラクタ
//============================
CLifeGauge::CLifeGauge(int nPriority) : CGauge(nPriority)
{

}

//============================
//ゲージのデストラクタ
//============================
CLifeGauge::~CLifeGauge()
{

}

//============================
//ゲージの描画
//============================
void CLifeGauge::Draw()
{
	//描画処理
	CObject2D::Draw(TEXTUREPATH.c_str());
}

//============================
//ゲージのクリエイト
//============================
CLifeGauge* CLifeGauge::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float max)
{
	//ポインタ用の変数
	CLifeGauge* pLifeGauge;

	//メモリの確保
	pLifeGauge = new CLifeGauge;

	//初期化
	pLifeGauge->Init();
	pLifeGauge->SetPos(pos);	//位置
	pLifeGauge->SetSize(size);	//サイズ
	pLifeGauge->SetMaxGauge(max);	//ゲージの最大値を設定
	pLifeGauge->SetNowGauge(max);	//ゲージの現在値を設定

	return pLifeGauge;
}