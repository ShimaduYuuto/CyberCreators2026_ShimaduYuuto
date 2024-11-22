//======================================
//
//	インパクトメッシュの処理[impactmesh.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "impactmesh.h"
#include "manager.h"
#include "game.h"

//オブジェクトメッシュクラスの定数の初期化
const std::string CImpactMesh::FILEPATH = "data\\TEXTURE\\SmashMesh000.png";//テクスチャパス
const int CImpactMesh::NUM_CORNER = 20;										//角の数
const float CImpactMesh::HEIGHT = 50.0f;									//高さ

//============================
//コンストラクタ
//============================
CImpactMesh::CImpactMesh(int nPriority) : CObjectCylinder(nPriority)
{
	
}

//============================
//デストラクタ
//============================
CImpactMesh::~CImpactMesh()
{
	
}

//============================
//初期化
//============================
HRESULT CImpactMesh::Init()
{
	//基底の初期化
	CObjectCylinder::Init();

	return S_OK;
}

//============================
//終了処理
//============================
void CImpactMesh::Uninit()
{
	//自分の開放
	CObjectCylinder::Uninit();
}

//============================
//更新
//============================
void CImpactMesh::Update()
{
	//更新
	CObjectCylinder::Update();
}

//============================
//描画
//============================
void CImpactMesh::Draw()
{
	//描画処理
	CObjectCylinder::Draw(FILEPATH.c_str());
}

//================================
//クリエイト
//================================
CImpactMesh* CImpactMesh::Create(D3DXVECTOR3 pos, float radius)
{
	//ポインタ用の変数
	CImpactMesh* pObject;

	//メモリの確保
	pObject = new CImpactMesh;

	//パラメータの設定
	pObject->SetPos(pos);			//位置の設定
	pObject->SetRadius(radius);	//半径の設定

	//初期化
	pObject->Init();

	return pObject;
}