//======================================
//
//	爆発の処理[effect_explosion.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "effect_explosion.h"
#include "game.h"
#include "manager.h"

//定数
const std::string CEffect_Explosion::FILEPATH = "data\\TEXTURE\\SmashMesh000.png";

//============================
//コンストラクタ
//============================
CEffect_Explosion::CEffect_Explosion(int nPriority) : CObjectDome(nPriority),
	m_fSizeRate(0.3f)
{
	//ゲームタグを設定
	SetTag(CObject::TAG_GAME);
}

//============================
//デストラクタ
//============================
CEffect_Explosion::~CEffect_Explosion()
{

}

//============================
//初期化
//============================
HRESULT CEffect_Explosion::Init()
{
	//初期化
	CObjectDome::Init();

	return S_OK;
}

//============================
//終了処理
//============================
void CEffect_Explosion::Uninit()
{
	//終了処理
	CObjectDome::Uninit();
}

//============================
//更新
//============================
void CEffect_Explosion::Update()
{
	m_fSizeRate += 0.01f;

	//倍率の設定
	SetRate(m_fSizeRate);

	//ゲームオブジェクトの共通処理更新
	CObjectDome::Update();
}

//============================
//描画
//============================
void CEffect_Explosion::Draw()
{
	//ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得

	//カリング方法を変更
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	//オブジェクトの描画
	CObjectDome::Draw(FILEPATH.c_str());

	//カリング方法を変更
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//============================
//クリエイト
//============================
CEffect_Explosion* CEffect_Explosion::Create(D3DXVECTOR3 pos)
{
	//種類に応じて動的確保
	CEffect_Explosion* pEffect_Explosion = nullptr;

	//クリエイトの処理
	pEffect_Explosion = new CEffect_Explosion;

	//パラメータの設定
	pEffect_Explosion->SetPos(pos);		//位置
	pEffect_Explosion->SetRadius(100.0f);	//半径
	pEffect_Explosion->SetRate(pEffect_Explosion->m_fSizeRate);

	//初期化
	pEffect_Explosion->Init();

	//設定した情報を返す
	return pEffect_Explosion;
}