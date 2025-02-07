//======================================
//
//	スタンエフェクトの描画[effect_stan.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "effect_stan.h"
#include "manager.h"

//定数
const std::string CEffect_Stan::TEXTURE_PATH = "data\\TEXTURE\\staneffect000.png";

//============================
//コンストラクタ
//============================
CEffect_Stan::CEffect_Stan() :
	m_pmtxParent(nullptr)
{
	//ゲームタグを設定
	SetTag(CObject::TAG_GAME);
}

//============================
//デストラクタ
//============================
CEffect_Stan::~CEffect_Stan()
{

}

//============================
//初期化
//============================
HRESULT CEffect_Stan::Init()
{
	CObjectCylinder::Init();

	return S_OK;
}

//============================
//終了処理
//============================
void CEffect_Stan::Uninit()
{
	CObjectCylinder::Uninit();
}

//============================
//更新処理
//============================
void CEffect_Stan::Update()
{
	//回転
	D3DXVECTOR3 Rot = GetRot();
	Rot.y += 0.05f;
	SetRot(Rot);

	//基底の更新
	CObjectCylinder::Update();
}

//============================
//描画処理
//============================
void CEffect_Stan::Draw()
{
	//描画用のローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice;		//デバイスの取得用

	//デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//ライティングオフ
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//両面カリング
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//テクスチャ描画
	CObjectCylinder::Draw(TEXTURE_PATH.c_str());

	//ライティングオン
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//片面カリング
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//============================
//マトリックスの計算
//============================
void CEffect_Stan::MtxCalculation()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxObject;	//計算用マトリックス
	mtxObject = GetMtx();					//自身のマトリックス

	//ワールドの初期化
	D3DXMatrixIdentity(&mtxObject);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);

	D3DXMatrixMultiply(&mtxObject, &mtxObject, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);

	D3DXMatrixMultiply(&mtxObject, &mtxObject, &mtxTrans);

	//ワールド変換行列と親の行列をかけ合わせる
	D3DXMatrixMultiply(&mtxObject, &mtxObject, m_pmtxParent);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxObject);

	//マトリックスの設定
	SetMtx(mtxObject);
}

//============================
//生成処理
//============================
CEffect_Stan* CEffect_Stan::Create(D3DXVECTOR3 pos, D3DXMATRIX* mtx)
{
	//ポインタ用の変数
	CEffect_Stan* pObject;

	//メモリの確保
	pObject = new CEffect_Stan;

	//パラメータの設定
	pObject->SetPos(pos);			//位置
	pObject->SetRadius(RADIUS);		//半径
	pObject->SetHeight(HEIGHT);		//高さ
	pObject->m_pmtxParent = mtx;	//親のマトリックス

	//初期化
	pObject->Init();				//初期化

	return pObject;
}