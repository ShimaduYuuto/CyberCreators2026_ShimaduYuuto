//======================================
//
//	ビルボードエフェクトの処理[effect_billboard.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "effect_billboard.h"
#include "manager.h"

//============================
//コンストラクタ
//============================
CEffect_Billboard::CEffect_Billboard() :
	m_Anim()	//アニメーションクラス
{
	//ゲームタグを設定
	SetTag(CObject::TAG_GAME);
}

//============================
//デストラクタ
//============================
CEffect_Billboard::~CEffect_Billboard()
{

}

//============================
//更新処理
//============================
void CEffect_Billboard::Update()
{
	//テクスチャ座標の更新
	D3DXVECTOR2 UV = m_Anim.UpdateAnim();
	SetTextureUV(
		UV.x * m_Anim.GetTextureCount().nHorizontalAnimCount,
		UV.x * (m_Anim.GetTextureCount().nHorizontalAnimCount + 1),
		UV.y * m_Anim.GetTextureCount().nVerticalAnimCount,
		UV.y * (m_Anim.GetTextureCount().nVerticalAnimCount + 1));

	//終了
	if (m_Anim.GetEnd())
	{
		Uninit();
	}
}