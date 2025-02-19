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
CEffect_Charge::CEffect_Charge()
{
	//情報の初期化
	CAnimation::TextureInfo Info = { VERTICAL, HORIZONTAL, SPEED_UPDATE, LOOP };
	GetAnim().SetTextureInfo(Info);	//設定

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
	//基底の更新
	CEffect_Billboard::Update();
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

	//ライティングoff
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//テクスチャ描画
	CObjectBillboard::Draw(TEXTURE_PATH.c_str());

	//ライティングon
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