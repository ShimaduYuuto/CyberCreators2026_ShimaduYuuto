//======================================
//
//	結界の処理[barrier.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "barrier.h"

//定数
const std::string CBarrier::TEXTURE_PATH = "data\\TEXTURE\\wall002.png";	//テクスチャパス
const D3DXVECTOR3 CBarrier::SIZE = { 1000.0f, 300.0f, 0.0f };				//ポリゴンサイズ

//============================
//コンストラクタ
//============================
CBarrier::CBarrier()
{
	//情報の初期化
	CAnimation::TextureInfo Info = { VERTICAL, HORIZONTAL, SPEED_UPDATE, LOOP };
	m_Anim.SetTextureInfo(Info);

	//ゲームタグを設定
	SetTag(CObject::TAG_GAME);
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
	CObject3D::Init();								//基底の初期化
	CObject3D::SetSize(SIZE, CObject3D::TYPE_WALL);	//ポリゴンサイズの設定
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

	CObject3D::Update();	//基底の更新
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