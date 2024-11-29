//======================================
//
//	当たり判定の位置の可視化[billboardeffect.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "billboardeffect.h"
#include "manager.h"

//============================
//コンストラクタ
//============================
CBillboardEffect::CBillboardEffect() :
	m_Anim()
{

}

//============================
//デストラクタ
//============================
CBillboardEffect::~CBillboardEffect()
{

}

//============================
//初期化
//============================
HRESULT CBillboardEffect::Init()
{
	CObjectBillboard::Init();

	return S_OK;
}

//============================
//終了処理
//============================
void CBillboardEffect::Uninit()
{
	CObjectBillboard::Uninit();
}

//============================
//更新処理
//============================
void CBillboardEffect::Update()
{
	CObjectBillboard::Update();
}

//============================
//描画処理
//============================
void CBillboardEffect::Draw()
{
	
}