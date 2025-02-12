//======================================
//
//	アニメーション処理[animation.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "animation.h"

//============================
//コンストラクタ
//============================
CAnimation::CAnimation() :
	m_TextureInfo(),
	m_TextureCount(),
	m_bEnd(false)
{

}

//============================
//デストラクタ
//============================
CAnimation::~CAnimation()
{

}

//============================
//アニメーションの更新
//============================
D3DXVECTOR2 CAnimation::UpdateAnim()
{
	//返す用の変数
	D3DXVECTOR2 UV = { 0.0f, 0.0f };

	UpdateCnt();

	//計算用の変数
	float fHorizontal = 1.0f / m_TextureInfo.nHorizontal;	//横分割
	float fVertical = 1.0f / m_TextureInfo.nVertical;		//縦分割
	UV = D3DXVECTOR2(fHorizontal, fVertical);				//UV座標を算出

	return UV;
}

//============================
//カウントの更新
//============================
void CAnimation::UpdateCnt()
{
	//フレームの更新
	m_TextureCount.nFrameCount++;

	//カウントが更新する値まで進んだら
	if (m_TextureCount.nFrameCount < m_TextureInfo.nUpdateSpeed)
	{
		return;
	}

	//カウントの更新
	m_TextureCount.nFrameCount = 0;			//フレームカウントの初期化
	m_TextureCount.nHorizontalAnimCount++;	//アニメーションカウントのカウントアップ

	//横のアニメカウントが最大まで進んだら
	if (m_TextureCount.nHorizontalAnimCount < m_TextureInfo.nHorizontal)
	{
		return;
	}

	//カウントの更新
	m_TextureCount.nHorizontalAnimCount = 0;	//横のカウントを初期化
	m_TextureCount.nVerticalAnimCount++;		//縦のカウントアップ

	//縦のカウントが最大まで進んだら
	if (m_TextureCount.nVerticalAnimCount < m_TextureInfo.nVertical)
	{
		return;
	}

	//ループが無いなら
	if (!m_TextureInfo.bLoop)
	{
		//終了処理
		m_bEnd = true;
	}
}
