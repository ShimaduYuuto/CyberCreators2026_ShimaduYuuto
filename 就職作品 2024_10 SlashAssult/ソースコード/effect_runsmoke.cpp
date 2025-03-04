//======================================
//
//	走った際の煙エフェクトの描画[effect_runsmoke.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "effect_runsmoke.h"
#include "manager.h"

//定数
const std::string CEffect_RunSmoke::TEXTURE_PATH = "data\\TEXTURE\\smoke000.png";

//============================
//コンストラクタ
//============================
CEffect_RunSmoke::CEffect_RunSmoke()
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
CEffect_RunSmoke::~CEffect_RunSmoke()
{

}

//============================
//初期化
//============================
HRESULT CEffect_RunSmoke::Init()
{
	CObjectBillboard::Init();

	return S_OK;
}

//============================
//終了処理
//============================
void CEffect_RunSmoke::Uninit()
{
	CObjectBillboard::Uninit();
}

//============================
//更新処理
//============================
void CEffect_RunSmoke::Update()
{
	//基底の更新
	CEffect_Billboard::Update();
}

//============================
//描画処理
//============================
void CEffect_RunSmoke::Draw()
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
CEffect_RunSmoke* CEffect_RunSmoke::Create(D3DXVECTOR3 pos)
{
	//ポインタ用の変数
	CEffect_RunSmoke* pObject;

	//メモリの確保
	pObject = new CEffect_RunSmoke;

	//初期化
	pObject->Init();		//初期化
	pObject->SetPos(pos);	//位置
	pObject->SetSize(D3DXVECTOR3(RADIUS, RADIUS, 0.0f));	//サイズ

	return pObject;
}