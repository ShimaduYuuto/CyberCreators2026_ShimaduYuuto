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
#include "dot.h"

//============================
//クリアタイムのコンストラクタ
//============================
CClearTime::CClearTime() : m_fTime(0.0f), m_Pos()
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
		//引数で渡す用の変数(位置)
		D3DXVECTOR3 Pos = m_Pos;

		//桁に応じて横の位置を変更
		Pos.x += i * NUM_SPACE;

		//数字のクリエイト
		m_pNumber[i] = CNumber::Create(Pos, 0);

		/*if (i == 2)
		{
			CDot::Create(D3DXVECTOR3(Pos.x + NUM_SPACE * 0.5f, Pos.y + 30.0f, 0.0f), { 15.0f, 15.0f, 0.0f });
		}*/
	}

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
	int aPosTex[TIME_NUM]; //各桁の数字を格納
	int nClearTime = m_fTime * 1000.0f;

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