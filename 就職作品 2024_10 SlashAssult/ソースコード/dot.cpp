//======================================
//
//	ゲージの処理[dot.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "dot.h"
#include "manager.h"
#include "game.h"

//定数
const std::string CDot::TEXTURE_PATH = "data\\TEXTURE\\dot000.png";

//============================
//ゲージのコンストラクタ
//============================
CDot::CDot(int nPriority) : CObject2D(nPriority)
{

}

//============================
//ゲージのデストラクタ
//============================
CDot::~CDot()
{

}

//============================
//ゲージの初期化
//============================
HRESULT CDot::Init()
{
	//初期化
	CObject2D::Init();

	return S_OK;
}

//============================
//ゲージの終了処理
//============================
void CDot::Uninit()
{
	CObject2D::Uninit();
}

//============================
//ゲージの更新
//============================
void CDot::Update()
{
	//更新処理
	CObject2D::Update();
}

//============================
//ゲージの描画
//============================
void CDot::Draw()
{
	//描画処理
	CObject2D::Draw(TEXTURE_PATH.c_str());
}

//============================
//ゲージのクリエイト
//============================
CDot* CDot::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//ポインタ用の変数
	CDot* pDot;

	//メモリの確保
	pDot = new CDot;

	//初期化
	pDot->Init();
	pDot->SetPos(pos);	//位置
	pDot->SetSize(size);	//サイズ

	return pDot;
}