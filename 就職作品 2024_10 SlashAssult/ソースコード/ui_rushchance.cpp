//======================================
//
//	ラッシュチャンスのUIの描画[ui_rushchance.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "ui_rushchance.h"
#include "manager.h"

//定数
const std::string CUi_RushChance::TEXTURE_PATH = "data\\TEXTURE\\ui_rushchance000.png";

//============================
//コンストラクタ
//============================
CUi_RushChance::CUi_RushChance(int nPriority) : CObjectBillboard(nPriority),
	m_Anim(),
	m_TargetPos(nullptr)
{
	//情報の初期化
	CAnimation::TextureInfo Info = { VERTICAL, HORIZONTAL, SPEED_UPDATE, LOOP };
	m_Anim.SetTextureInfo(Info);
}

//============================
//デストラクタ
//============================
CUi_RushChance::~CUi_RushChance()
{

}

//============================
//初期化
//============================
HRESULT CUi_RushChance::Init()
{
	CObjectBillboard::Init();

	return S_OK;
}

//============================
//終了処理
//============================
void CUi_RushChance::Uninit()
{
	CObjectBillboard::Uninit();
}

//============================
//更新処理
//============================
void CUi_RushChance::Update()
{
	//テクスチャ座標の更新
	D3DXVECTOR2 UV = m_Anim.UpdateAnim();
	SetTextureUV(
		UV.x * m_Anim.GetTextureCount().nHorizontalAnimCount,
		UV.x * (m_Anim.GetTextureCount().nHorizontalAnimCount + 1),
		UV.y * m_Anim.GetTextureCount().nVerticalAnimCount,
		UV.y * (m_Anim.GetTextureCount().nVerticalAnimCount + 1));

	SetPos(*m_TargetPos + D3DXVECTOR3{100.0f, 0.0f, 0.0f});
}

//============================
//描画処理
//============================
void CUi_RushChance::Draw()
{
	//描画用のローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice;		//デバイスの取得用

	//デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Zの比較方法変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//テクスチャ描画
	CObjectBillboard::Draw(TEXTURE_PATH.c_str());

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//Zの比較方法変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}

//============================
//生成処理
//============================
CUi_RushChance* CUi_RushChance::Create(D3DXVECTOR3* pos)
{
	//ポインタ用の変数
	CUi_RushChance* pObject;

	//メモリの確保
	pObject = new CUi_RushChance();

	//初期化
	pObject->Init();			//初期化
	pObject->m_TargetPos = pos;	//ターゲットの位置
	pObject->SetPos(*pos);		//位置
	pObject->SetSize(D3DXVECTOR3(RADIUS, RADIUS, 0.0f));	//サイズ

	return pObject;
}