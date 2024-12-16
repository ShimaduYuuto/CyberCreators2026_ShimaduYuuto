//======================================
//
//	Xファイルの管理[xfile.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "xfile.h"
#include "manager.h"

//静的メンバ変数の初期化
std::map<std::string, CXfile::XFileInfo> CXfile::m_pXfilemap = {};	//Xファイルの情報

//============================
//Xファイルのコンストラクタ
//============================
CXfile::CXfile()
{
	m_pXfilemap.clear();
}

//============================
//Xファイルのデストラクタ
//============================
CXfile::~CXfile()
{
	m_pXfilemap.clear();
}

//============================
//Xファイルの破棄
//============================
void CXfile::Unload()
{
	//全てのXファイルの番号とパスを破棄
	m_pXfilemap.erase(m_pXfilemap.begin(), m_pXfilemap.end());
}

//============================
//Xファイルの登録
//============================
int CXfile::Regist(const char* pXfileName)
{
	//Xファイルが存在していなかったら
	if (m_pXfilemap.count(pXfileName) == NULL)		//1つも無かったら０
	{
		//情報を一時的に保持する変数
		CXfile::XFileInfo pObjectInfo = {NULL};		//オブジェクトの情報
		pObjectInfo.nIndex = m_pXfilemap.size();	//要素数

		//デバイスの宣言
		LPDIRECT3DDEVICE9 pDevice;

		//デバイスの取得
		pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

		//Xファイルの読み込み
		D3DXLoadMeshFromX(pXfileName,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&pObjectInfo.pBuffmat,
			NULL,
			&pObjectInfo.dwNumMat,
			&pObjectInfo.pMesh);

		D3DXMATERIAL* pMat; //マテリアルへのポインタ

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)pObjectInfo.pBuffmat->GetBufferPointer();

		//マテリアルの数だけ周回
		for (int nCntMat = 0; nCntMat < (int)pObjectInfo.dwNumMat; nCntMat++)
		{
			//テクスチャが存在する
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//テクスチャ読み込み用
				LPDIRECT3DTEXTURE9 pTexture;

				//テクスチャを読み込む
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&pTexture);

				//テクスチャのメモリ確保
				pObjectInfo.pTexture.push_back(pTexture);
			}
		}

		//サイズの読み込み
		LoadSize(pObjectInfo);

		//マップの生成
		m_pXfilemap[pXfileName] = { pObjectInfo };
	}

	//Xファイルの値を返す
	return m_pXfilemap[pXfileName].nIndex;
}

//============================
//サイズの読み込み
//============================
void CXfile::LoadSize(XFileInfo& pfileinfo)
{
	//値の初期化
	pfileinfo.aSize.Max = { 0.0f, 0.0f, 0.0f };
	pfileinfo.aSize.Min = { 0.0f, 0.0f, 0.0f };

	//頂点情報を読み込むためのローカル変数宣言
	int nNumVtx;			//頂点数
	DWORD sizeFVF;			//頂点フォーマットのサイズ
	BYTE* pVtxBuff;			//頂点バッファへのポインタ

	//頂点数の取得
	nNumVtx = pfileinfo.pMesh->GetNumVertices();
	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(pfileinfo.pMesh->GetFVF());
	//頂点バッファのロック
	pfileinfo.pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	//頂点の数だけ周回
	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//頂点座標を比較してモデルの最小値最大値を取得
		//X座標
		if (vtx.x > pfileinfo.aSize.Max.x)
		{
			pfileinfo.aSize.Max.x = vtx.x;
		}
		else if (vtx.x < pfileinfo.aSize.Min.x)
		{
			pfileinfo.aSize.Min.x = vtx.x;
		}

		//Y座標
		if (vtx.y > pfileinfo.aSize.Max.y)
		{
			pfileinfo.aSize.Max.y = vtx.y;
		}
		else if (vtx.y < pfileinfo.aSize.Min.y)
		{
			pfileinfo.aSize.Min.y = vtx.y;
		}

		//Z座標
		if (vtx.z > pfileinfo.aSize.Max.z)
		{
			pfileinfo.aSize.Max.z = vtx.z;
		}
		else if (vtx.z < pfileinfo.aSize.Min.z)
		{
			pfileinfo.aSize.Min.z = vtx.z;
		}

		//頂点フォーマットのサイズ分ポインタを進める
		pVtxBuff += sizeFVF;
	}

	//頂点バッファのアンロック
	pfileinfo.pMesh->UnlockVertexBuffer();
}

//============================
//Xファイルの取得
//============================
CXfile::XFileInfo CXfile::GetAddress(int nIdx)
{
	//Xファイルの数だけ周回
	for (auto& iter : m_pXfilemap)
	{
		//引数と値が一致したなら
		if (iter.second.nIndex == nIdx)
		{
			//Xファイルのパスを返す
			return iter.second;
		}
	}

	//Xファイルが存在しない
	return {};
}