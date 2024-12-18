//======================================
//
//	結界の処理[barrier.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "barrier.h"
#include "game.h"
#include "manager.h"
#include "barriermanager.h"

//定数
const std::string CBarrier::TEXTURE_PATH = "data\\TEXTURE\\wall002.png";

//============================
//コンストラクタ
//============================
CBarrier::CBarrier()
{
	//情報の初期化
	CAnimation::TextureInfo Info = { VERTICAL, HORIZONTAL, SPEED_UPDATE, LOOP };
	m_Anim.SetTextureInfo(Info);
}

//============================
//デストラクタ
//============================
CBarrier::~CBarrier()
{
	
}

//============================
//初期化
//============================
HRESULT CBarrier::Init()
{
	CObject3D::Init();
	CObject3D::SetSize({ 1000.0f, 300.0f, 0.0f }, CObject3D::TYPE_WALL);
	return S_OK;
}

//============================
//終了処理
//============================
void CBarrier::Uninit()
{
	CObject3D::Uninit();
}

//============================
//更新処理
//============================
void CBarrier::Update()
{
	//テクスチャ座標の更新
	D3DXVECTOR2 UV = m_Anim.UpdateAnim();
	SetTextureUV(
		UV.x * m_Anim.GetTextureCount().nHorizontalAnimCount,
		UV.x * (m_Anim.GetTextureCount().nHorizontalAnimCount + 1),
		UV.y * m_Anim.GetTextureCount().nVerticalAnimCount,
		UV.y * (m_Anim.GetTextureCount().nVerticalAnimCount + 1));

	CObject3D::Update();
}

//============================
//描画処理
//============================
void CBarrier::Draw()
{
	CObject3D::Draw(TEXTURE_PATH.c_str());
}

//============================
//生成処理
//============================
CBarrier* CBarrier::Create(D3DXVECTOR3 pos)
{
	//ポインタ用の変数
	CBarrier* pBarrier = nullptr;
	pBarrier = new CBarrier;

	//パラメータの代入
	pBarrier->SetPos(pos);

	//初期化
	pBarrier->Init();

	return pBarrier;
}