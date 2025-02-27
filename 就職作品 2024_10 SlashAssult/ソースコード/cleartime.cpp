//======================================
//
//	クリアタイムの描画[cleartime.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "cleartime.h"
#include "manager.h"
#include "game.h"
#include "colon.h"

//============================
//クリアタイムのコンストラクタ
//============================
CClearTime::CClearTime() : 
	m_fTime(0.0f),	//現在の時間
	m_Pos()			//位置
{
	//ナンバーの初期化
	for (int i = 0; i < TIME_NUM; i++)
	{
		m_pNumber[i] = nullptr;
	}
}

//============================
//クリアタイムのデストラクタ
//============================
CClearTime::~CClearTime()
{

}

//============================
//クリアタイムの初期化
//============================
HRESULT CClearTime::Init()
{
	//表示する桁数だけナンバーをクリエイト
	for (int i = 0; i < TIME_NUM; i++)
	{
		//引数で渡す用の変数
		D3DXVECTOR3 Pos = m_Pos;	//位置

		//桁に応じて横の位置を変更
		Pos.x += i * NUM_SPACE;

		//少数と整数で隙間を変更
		if (i >= NUM_FEW)
		{
			Pos.x += FEW_SPACE * 0.5f;
		}
		else
		{
			Pos.x -= FEW_SPACE * 0.5f;
		}

		//数字のクリエイト
		m_pNumber[i] = CNumber::Create(Pos, 0);

		//コロンの生成
		if (i == NUM_FEW - 1)
		{
			CColon::Create(D3DXVECTOR3(Pos.x + (NUM_SPACE + FEW_SPACE) * 0.5f, Pos.y, 0.0f), { 70.0f, 70.0f, 0.0f });
		}
	}

	//時間の設定
	SetTime();

	return S_OK;
}

//============================
//クリアタイムの終了処理
//============================
void CClearTime::Uninit()
{
	
}

//============================
//クリアタイムの加算処理
//============================
void CClearTime::AddTime(float value)
{
	//クリアタイムの加算
	m_fTime += value;

	//クリアタイムの設定
	SetTime();
}

//============================
//クリアタイムの設定
//============================
void CClearTime::SetTime()
{
	//計算用の変数
	int aPosTex[TIME_NUM];				//各桁の数字を格納
	float fClearTime = m_fTime;			//クリアタイム
	int nClearTime = 0;					//整数に置き換えたクリアタイム

	//少数点をの桁を引いた分だけ桁を増やす
	for (int i = 0; i < NUM_FEW; i++)
	{
		fClearTime *= 10.0f;
	}

	//少数の桁の分だけずらした値を代入
	nClearTime = static_cast<int>(fClearTime);

	//桁ごとに数値を代入
	for (int nCount = TIME_NUM; nCount > 0; nCount--)
	{
		aPosTex[nCount - 1] = nClearTime % 10;
		nClearTime /= 10;
	}

	//テクスチャの座標の設定
	for (int nCntClearTime = 0; nCntClearTime < TIME_NUM; nCntClearTime++)
	{
		m_pNumber[nCntClearTime]->SetTexture(aPosTex[nCntClearTime]);
	}

}

//============================
//クリアタイムのリセット
//============================
void CClearTime::ResetTime()
{
	//クリアタイムのリセット
	m_fTime = 0.0f;
}