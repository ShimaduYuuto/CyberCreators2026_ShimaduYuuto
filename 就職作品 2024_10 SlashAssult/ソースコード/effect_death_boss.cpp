//======================================
//
//	死亡エフェクトの描画[effect_death_boss.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "effect_death_boss.h"
#include "manager.h"

//定数
const std::string CEffect_Death_Boss::TEXTURE_PATH = "data\\TEXTURE\\death_boss001.png";

//============================
//コンストラクタ
//============================
CEffect_Death_Boss::CEffect_Death_Boss() :
	m_TargetPos(nullptr)
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
CEffect_Death_Boss::~CEffect_Death_Boss()
{

}

//============================
//初期化
//============================
HRESULT CEffect_Death_Boss::Init()
{
	CObjectBillboard::Init();

	return S_OK;
}

//============================
//終了処理
//============================
void CEffect_Death_Boss::Uninit()
{
	CObjectBillboard::Uninit();
}

//============================
//更新処理
//============================
void CEffect_Death_Boss::Update()
{
	//位置の設定
	SetPos(*m_TargetPos);

	//基底の更新
	CEffect_Billboard::Update();
}

//============================
//描画処理
//============================
void CEffect_Death_Boss::Draw()
{
	//描画用のローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice;		//デバイスの取得用

	//デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//ライティングオフ
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//αテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	//テクスチャ描画
	CObjectBillboard::Draw(TEXTURE_PATH.c_str());

	//ライティングオン
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//αテストを元に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//============================
//生成処理
//============================
CEffect_Death_Boss* CEffect_Death_Boss::Create(D3DXVECTOR3* pos)
{
	//ポインタ用の変数
	CEffect_Death_Boss* pObject;

	//メモリの確保
	pObject = new CEffect_Death_Boss;

	//初期化
	pObject->Init();										//初期化
	pObject->m_TargetPos = pos;								//対象の位置
	pObject->SetPos(*pos);									//位置
	pObject->SetSize(D3DXVECTOR3(RADIUS, RADIUS, 0.0f));	//サイズ

	return pObject;
}