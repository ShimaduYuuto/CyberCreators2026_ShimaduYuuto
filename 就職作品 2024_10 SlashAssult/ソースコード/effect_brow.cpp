//======================================
//
//	ブローエフェクトの描画[effect_brow.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "effect_brow.h"
#include "manager.h"

//定数
const std::string CEffect_Brow::TEXTURE_PATH = "data\\TEXTURE\\broweffect000.png";

//============================
//コンストラクタ
//============================
CEffect_Brow::CEffect_Brow() :
	m_Anim()
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
CEffect_Brow::~CEffect_Brow()
{

}

//============================
//初期化
//============================
HRESULT CEffect_Brow::Init()
{
	CObject3D::Init();

	return S_OK;
}

//============================
//終了処理
//============================
void CEffect_Brow::Uninit()
{
	CObject3D::Uninit();
}

//============================
//更新処理
//============================
void CEffect_Brow::Update()
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

//============================
//描画処理
//============================
void CEffect_Brow::Draw()
{
	//描画用のローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice;		//デバイスの取得用

	//デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//ライティングオフ
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//カリング方法を変更
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//αテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	//テクスチャ描画
	CObject3D::Draw(TEXTURE_PATH.c_str());

	//ライティングオン
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//カリング方法を変更
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//αテストを元に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//============================
//生成処理
//============================
CEffect_Brow* CEffect_Brow::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//ポインタ用の変数
	CEffect_Brow* pObject;

	//メモリの確保
	pObject = new CEffect_Brow;

	//初期化
	pObject->Init();		//初期化
	pObject->SetPos(pos);	//位置
	pObject->SetRot(rot);	//向き
	pObject->SetSize(D3DXVECTOR3(RADIUS, RADIUS, 0.0f), CObject3D::TYPE_WALL);	//サイズ

	return pObject;
}