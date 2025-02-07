//======================================
//
//	チャージエフェクトの描画[effect_charge.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "effect_charge.h"
#include "manager.h"

//定数
const std::string CEffect_Charge::TEXTURE_PATH = "data\\TEXTURE\\charge001.png";

//============================
//コンストラクタ
//============================
CEffect_Charge::CEffect_Charge() :
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
CEffect_Charge::~CEffect_Charge()
{

}

//============================
//初期化
//============================
HRESULT CEffect_Charge::Init()
{
	CObjectBillboard::Init();

	return S_OK;
}

//============================
//終了処理
//============================
void CEffect_Charge::Uninit()
{
	CObjectBillboard::Uninit();
}

//============================
//更新処理
//============================
void CEffect_Charge::Update()
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
void CEffect_Charge::Draw()
{
	//描画用のローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice;		//デバイスの取得用

	//デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//テクスチャ描画
	CObjectBillboard::Draw(TEXTURE_PATH.c_str());

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//============================
//生成処理
//============================
CEffect_Charge* CEffect_Charge::Create(D3DXVECTOR3 pos)
{
	//ポインタ用の変数
	CEffect_Charge* pObject;

	//メモリの確保
	pObject = new CEffect_Charge;

	//初期化
	pObject->Init();		//初期化
	pObject->SetPos(pos);	//位置
	pObject->SetSize(D3DXVECTOR3(RADIUS, RADIUS, 0.0f));	//サイズ

	return pObject;
}