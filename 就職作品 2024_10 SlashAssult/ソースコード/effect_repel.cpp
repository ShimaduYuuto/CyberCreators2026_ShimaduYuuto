//======================================
//
//	弾かれエフェクトの描画[effect_repel.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "effect_repel.h"
#include "manager.h"

//定数
const std::string CEffect_Repel::TEXTURE_PATH = "data\\TEXTURE\\repel000.png";

//============================
//コンストラクタ
//============================
CEffect_Repel::CEffect_Repel()
{
	//情報の初期化
	CAnimation::TextureInfo Info = { VERTICAL, HORIZONTAL, SPEED_UPDATE, LOOP };
	GetAnim().SetTextureInfo(Info);

	//ゲームタグを設定
	SetTag(CObject::TAG_GAME);
}

//============================
//デストラクタ
//============================
CEffect_Repel::~CEffect_Repel()
{

}

//============================
//初期化
//============================
HRESULT CEffect_Repel::Init()
{
	CObjectBillboard::Init();

	return S_OK;
}

//============================
//終了処理
//============================
void CEffect_Repel::Uninit()
{
	CObjectBillboard::Uninit();
}

//============================
//更新処理
//============================
void CEffect_Repel::Update()
{
	//基底の更新
	CEffect_Billboard::Update();
}

//============================
//描画処理
//============================
void CEffect_Repel::Draw()
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
CEffect_Repel* CEffect_Repel::Create(D3DXVECTOR3 pos)
{
	//ポインタ用の変数
	CEffect_Repel* pObject;

	//メモリの確保
	pObject = new CEffect_Repel;

	//初期化
	pObject->Init();		//初期化
	pObject->SetPos(pos);	//位置
	pObject->SetSize(D3DXVECTOR3(RADIUS, RADIUS, 0.0f));	//サイズ

	return pObject;
}