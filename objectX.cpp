//======================================
//
//	オブジェクトXの処理[objectX.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "objectX.h"
#include "manager.h"
#include "game.h"

//オブジェクトXクラスの定数の初期化
const std::string CObjectX::FILEPATH = "data\\MODEL\\Block001.x";

//============================
//オブジェクトXのコンストラクタ
//============================
CObjectX::CObjectX(int nPriority) : CObject(nPriority)
{
	//パラメータの初期化
	m_rot = { 0.0f, 0.0f, 0.0f };	//向き
	m_Scale = { 1.0f, 1.0f, 1.0f };	//スケール
}

//============================
//オブジェクトXのデストラクタ
//============================
CObjectX::~CObjectX()
{

}

//============================
//オブジェクトXの初期化
//============================
HRESULT CObjectX::Init()
{
	return S_OK;
}

//============================
//オブジェクトXの終了処理
//============================
void CObjectX::Uninit()
{
	//消去
	SetDeath();
}

//============================
//オブジェクトXの更新
//============================
void CObjectX::Update()
{
	
}

//============================
//オブジェクトXの描画
//============================
void CObjectX::Draw()
{
	//ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;								//計算用マトリックス
	D3DMATERIAL9 matDef;												//現在のマテリアル保存用
	D3DXMATERIAL* pMat;													//マテリアルデータへのポインタ
	D3DXVECTOR3 Pos = GetPos();											//位置の取得

	//Xファイルの読み込み
	CXfile* pCXfile = CManager::GetInstance()->GetXfile();

	//ワールドの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//スケールを反映
	D3DXMatrixScaling(&mtxScale, m_Scale.x, m_Scale.y, m_Scale.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, Pos.x, Pos.y, Pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)pCXfile->GetAddress(pCXfile->Regist(CObjectX::FILEPATH.c_str())).pBuffmat->GetBufferPointer();

	//テクスチャの数をカウント
	int nTextureCount = 0;

	//マテリアルの数だけ周回
	for (int nCntMat = 0; nCntMat < (int)pCXfile->GetAddress(pCXfile->Regist(CObjectX::FILEPATH.c_str())).dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャがあったら
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, pCXfile->GetAddress(pCXfile->Regist(CObjectX::FILEPATH.c_str())).pTexture[nTextureCount]);

			//テクスチャ用のカウントを進める
			nTextureCount++;
		}
		else
		{
			//テクスチャを設定しない
			pDevice->SetTexture(0, NULL);
		}

		//オブジェクトX(パーツ)の描画
		pCXfile->GetAddress(pCXfile->Regist(CObjectX::FILEPATH.c_str())).pMesh->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);

	//位置の設定
	SetPos(Pos);
}

//============================
//引数のオブジェクトの描画
//============================
void CObjectX::Draw(const char* pfilepath)
{
	//ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;								//計算用マトリックス
	D3DMATERIAL9 matDef;												//現在のマテリアル保存用
	D3DXMATERIAL* pMat;													//マテリアルデータへのポインタ
	D3DXVECTOR3 Pos = GetPos();											//位置の取得

	//Xファイルの読み込み
	CXfile* pCXfile = CManager::GetInstance()->GetXfile();

	//ワールドの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//スケールを反映
	D3DXMatrixScaling(&mtxScale, m_Scale.x, m_Scale.y, m_Scale.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, Pos.x, Pos.y, Pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)pCXfile->GetAddress(pCXfile->Regist(pfilepath)).pBuffmat->GetBufferPointer();

	//テクスチャの数をカウント
	int nTextureCount = 0;

	//マテリアルの数だけ周回
	for (int nCntMat = 0; nCntMat < (int)pCXfile->GetAddress(pCXfile->Regist(pfilepath)).dwNumMat; nCntMat++)
	{
		//現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		//色を保存
		matDef = pMat[nCntMat].MatD3D;

		//マテリアルの設定
		pDevice->SetMaterial(&matDef);

		//テクスチャがあったら
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, pCXfile->GetAddress(pCXfile->Regist(pfilepath)).pTexture[nTextureCount]);

			//テクスチャ用のカウントを進める
			nTextureCount++;
		}
		else
		{
			//テクスチャを設定しない
			pDevice->SetTexture(0, NULL);
		}

		//オブジェクトX(パーツ)の描画
		pCXfile->GetAddress(pCXfile->Regist(pfilepath)).pMesh->DrawSubset(nCntMat);

		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}

	//位置の設定
	SetPos(Pos);
}

//============================
//オブジェクトXのクリエイト
//============================
CObjectX* CObjectX::Create(D3DXVECTOR3 pos)
{
	//ポインタ用の変数
	CObjectX* pObjectX;

	//メモリの確保
	pObjectX = new CObjectX;

	//パラメータの設定
	pObjectX->SetPos(pos);	//位置の設定

	//初期化
	pObjectX->Init();

	return pObjectX;
}