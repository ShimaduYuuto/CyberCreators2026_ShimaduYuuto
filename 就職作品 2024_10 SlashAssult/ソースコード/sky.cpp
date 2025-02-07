//======================================
//
//	空の処理[sky.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "sky.h"
#include "manager.h"

//定数
const std::string CSky::FILEPATH = "data\\TEXTURE\\sky001.jpg";
const D3DXVECTOR3 CSky::POS = { 0.0f, -100.0f, 0.0f };

//============================
//コンストラクタ
//============================
CSky::CSky(int nPriority) : CObjectDome(nPriority)
{

}

//============================
//デストラクタ
//============================
CSky::~CSky()
{

}

//============================
//初期化
//============================
HRESULT CSky::Init()
{
	//初期化
	CObjectDome::Init();

	return S_OK;
}

//============================
//終了処理
//============================
void CSky::Uninit()
{
	//終了処理
	CObjectDome::Uninit();
}

//============================
//更新
//============================
void CSky::Update()
{
	CObjectDome::Update();
}

//============================
//描画
//============================
void CSky::Draw()
{
	//デバイスの取得
	 LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//オブジェクトの描画
	CObjectDome::Draw(FILEPATH.c_str());

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//============================
//クリエイト
//============================
CSky* CSky::Create()
{
	//種類に応じて動的確保
	CSky* pSky = nullptr;

	//クリエイトの処理
	pSky = new CSky;

	pSky->SetRadius(RADIUS);		//半径
	pSky->SetRate(RATE);			//倍率
	pSky->SetPos(D3DXVECTOR3(POS));	//位置

	//初期化
	pSky->Init();

	//設定した情報を返す
	return pSky;
}