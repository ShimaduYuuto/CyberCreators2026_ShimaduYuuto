//======================================
//
//	アタックヒットエフェクトの描画[effect_hitattack.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "effect_hitattack.h"
#include "manager.h"

//定数
const std::string CEffect_HitAttack::TEXTURE_PATH = "data\\TEXTURE\\attack000.png";

//============================
//コンストラクタ
//============================
CEffect_HitAttack::CEffect_HitAttack()
{
	//情報の初期化
	CAnimation::TextureInfo Info = {VERTICAL, HORIZONTAL, SPEED_UPDATE, LOOP};
	GetAnim().SetTextureInfo(Info);

	//ゲームタグを設定
	SetTag(CObject::TAG_GAME);
}

//============================
//デストラクタ
//============================
CEffect_HitAttack::~CEffect_HitAttack()
{

}

//============================
//初期化
//============================
HRESULT CEffect_HitAttack::Init()
{
	CObjectBillboard::Init();

	return S_OK;
}

//============================
//終了処理
//============================
void CEffect_HitAttack::Uninit()
{
	CObjectBillboard::Uninit();
}

//============================
//更新処理
//============================
void CEffect_HitAttack::Update()
{
	//基底の更新
	CEffect_Billboard::Update();
}

//============================
//描画処理
//============================
void CEffect_HitAttack::Draw()
{
	//描画用のローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice;		//デバイスの取得用

	//デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//ライティングをoff
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//テクスチャ描画
	CObjectBillboard::Draw(TEXTURE_PATH.c_str());

	//ライティングをon
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//============================
//生成処理
//============================
CEffect_HitAttack* CEffect_HitAttack::Create(D3DXVECTOR3 pos)
{
	//ポインタ用の変数
	CEffect_HitAttack* pObject;

	//メモリの確保
	pObject = new CEffect_HitAttack;

	//初期化
	pObject->Init();		//初期化
	pObject->SetPos(pos);	//位置
	pObject->SetSize(D3DXVECTOR3(RADIUS, RADIUS, 0.0f));	//サイズ

	return pObject;
}