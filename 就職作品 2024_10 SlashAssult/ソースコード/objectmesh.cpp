//======================================
//
//	オブジェクトメッシュの処理[objectmesh.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "objectmesh.h"
#include "manager.h"
#include "game.h"

//オブジェクトメッシュクラスの定数の初期化
const D3DXVECTOR3 CObjectMesh::BLOCK = {2, 0, 2};						//ブロック数
const D3DXVECTOR3 CObjectMesh::SIZE = { 15000.0f, 100.0f, 10000.0f };	//サイズ

//============================
//オブジェクトメッシュのコンストラクタ
//============================
CObjectMesh::CObjectMesh(int nPriority) : CObject(nPriority)
{
	//パラメータの初期化
	m_rot = { 0.0f, 0.0f, 0.0f };	//向き
	m_mtxWorld = {};				//ワールドマトリックス
	m_pTexture = nullptr;			//テクスチャ
	m_nIndex = 0;					//番号の数
	m_nPolygon = 0;					//ポリゴンの数
	m_nVertex = 0;					//頂点の数
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//色の設定
}

//============================
//オブジェクトメッシュのデストラクタ
//============================
CObjectMesh::~CObjectMesh()
{

}

//============================
//オブジェクトメッシュの初期化
//============================
HRESULT CObjectMesh::Init()
{
	//ローカル変数
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ
	m_nIndex = (int)(2 * (BLOCK.x + 1) * BLOCK.z + (BLOCK.z - 1) * 2);	//インデックス数
	m_nVertex = (int)((BLOCK.x + 1) * (BLOCK.z + 1));						//頂点数
	m_nPolygon = (int)((BLOCK.x * BLOCK.z) * 2 + (BLOCK.z - 1) * 4);		//ポリゴン数

	//デバイスを取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得

	//テクスチャの読み込む
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Block00.png",
		&m_pTexture);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (m_nVertex),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nIndex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	VERTEX_3D* pVtx; //追加情報のポインタ

	//インデックスバッファをロック
	WORD* pIdx; //追加のポインタ
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	
	int nX = 0;
	int nHeightCount = 0;

	//頂点の数だけ回す
	for (int nCount = 0; nCount < m_nVertex; nCount++)
	{
		//位置の設定
		pVtx[nCount].pos = D3DXVECTOR3(SIZE.x * (nX / (float)BLOCK.x) - (SIZE.x * 0.5f), 0.0f, -SIZE.z * (nHeightCount / (float)BLOCK.z) + (SIZE.z * 0.5f));

		//pVtx[nCount].pos.y += 200.0f - nX * 10.0f;

		//テクスチャの読み込み
		pVtx[nCount].tex = D3DXVECTOR2(1.0f * (nX / (float)BLOCK.x), 1.0f * (nHeightCount / (float)BLOCK.z));

		nX++;

		if (nX == BLOCK.x + 1)
		{
			nX = 0;
			nHeightCount++;
		}

		//法線ベクトルの設定
		pVtx[nCount].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[nCount].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//インデックスの計算用の変数
	nX = 0;
	nHeightCount = 0;
	int nX2 = 0;

	//インデックスの計算
	for (int nCount = 0; nCount < m_nIndex; nCount++)
	{
		//縮退ポリゴンの場合とそれ以外
		if (nCount == ((int)(BLOCK.x + 1) * 2 + 2) * (nHeightCount + 1) - 2)
		{
			pIdx[nCount] = pIdx[nCount - 1];
		}
		else if (nCount == ((int)(BLOCK.x + 1) * 2 + 2) * (nHeightCount + 1) - 1)
		{
			pIdx[nCount] = pIdx[nCount - 1] + (WORD)BLOCK.x + 2;
			nHeightCount++;
		}
		else
		{
			if (nCount % 2 == 0)//偶数の場合
			{
				pIdx[nCount] = (WORD)(BLOCK.x + 1 + nX);
				nX++;
			}
			else//奇数の場合
			{
				pIdx[nCount] = (WORD)nX2;
				nX2++;
			}
		}
	}

	//ポリゴンの数だけ回す
	for (int i = 0; i < m_nPolygon; i++)
	{
		//縮退ならコンティニュー
		if ((pIdx[i] == pIdx[i + 1]) || (pIdx[i + 1] == pIdx[i + 2]))
		{
			continue;
		}

		//法線ベクトルを格納する変数
		D3DXVECTOR3 SurfaceNorVec; //面法線のベクトル
		D3DXVECTOR3 vecNormal; //正規化したベクトル
		D3DXVECTOR3 vector1; //１つ目のベクトルの保管用
		D3DXVECTOR3 vector2; //２つ目のベクトルの保管用

		//インデックスを格納する変数
		WORD index0 = pIdx[i + 0];
		WORD index1 = pIdx[i + 1];
		WORD index2 = pIdx[i + 2];

		//頂点を格納する変数
		VERTEX_3D* vtx0 = pVtx + index0;
		VERTEX_3D* vtx1 = pVtx + index1;
		VERTEX_3D* vtx2 = pVtx + index2;

		//法線ベクトルの算出
		if ((i & 1) == 0) //偶数
		{
			vector1 = vtx1->pos - vtx0->pos;
			vector2 = vtx2->pos - vtx0->pos;
		}
		else //奇数
		{
			vector1 = vtx2->pos - vtx0->pos;
			vector2 = vtx1->pos - vtx0->pos;
		}

		//ベクトルの計算
		D3DXVec3Cross(&SurfaceNorVec, &vector1, &vector2);

		//ベクトルの正規化
		D3DXVec3Normalize(&vecNormal, &SurfaceNorVec);

		//ベクトルを加算
		vtx0->nor += vecNormal;
		vtx1->nor += vecNormal;
		vtx2->nor += vecNormal;

		////面法線ベクトルを保存
		//m_SurfaceNorVec.push_back(vecNormal);
	}

	//加算したベクトルを正規化
	for (int nCount = 0; nCount < m_nVertex; nCount++)
	{
		//ベクトルの正規化
		D3DXVec3Normalize(&pVtx[nCount].nor, &pVtx[nCount].nor);
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//インデックスバッファのアンロック
	m_pIdxBuff->Unlock();

	return S_OK;
}

//============================
//オブジェクトメッシュの初期化
//============================
HRESULT CObjectMesh::Init(int widthblock, int heightblock, float widthsize, float heightsize, MESHTYPE meshtype)
{
	//ローカル変数
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ
	m_nIndex = (int)(2 * (widthblock + 1) * heightblock + (heightblock - 1) * 2);		//インデックス数
	m_nVertex = (int)((widthblock + 1) * (heightblock + 1));							//頂点数
	m_nPolygon = (int)((widthblock * heightblock) * 2 + (heightblock - 1) * 4);			//ポリゴン数

	//位置の設定
	switch (meshtype)
	{
		//フィールド
	case MESHTYPE_FIELD:
		//引数の情報の代入
		m_block = { (float)widthblock, 0.0f, (float)heightblock };	//ブロック数
		m_size = { widthsize, 0.0f, heightsize };		//メッシュのサイズ
		break;

		//壁
	case MESHTYPE_WALL:
		//引数の情報の代入
		m_block = { (float)widthblock, (float)heightblock, 0.0f };	//ブロック数
		m_size = { widthsize, heightsize, 0.0f };		//メッシュのサイズ
		break;
	}
	

	//デバイスを取得
	pDevice = CManager::GetInstance()-> GetRenderer()->GetDevice();	//デバイスの取得

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (m_nVertex),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nIndex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	//頂点情報の計算
	//VtxPosCluculation(meshtype);

	VERTEX_3D* pVtx; //追加情報のポインタ

	//インデックスバッファをロック
	WORD* pIdx; //追加のポインタ
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//インデックスの計算用の変数
	int nX = 0;
	int nHeightCount = 0;
	int nX2 = 0;

	//インデックスの計算
	for (int nCount = 0; nCount < m_nIndex; nCount++)
	{
		//縮退ポリゴンの場合とそれ以外
		if (nCount == ((int)(widthblock + 1) * 2 + 2) * (nHeightCount + 1) - 2)
		{
			pIdx[nCount] = pIdx[nCount - 1];
		}
		else if (nCount == ((int)(widthblock + 1) * 2 + 2) * (nHeightCount + 1) - 1)
		{
			pIdx[nCount] = pIdx[nCount - 1] + (WORD)widthblock + 2;
			nHeightCount++;
		}
		else
		{
			if (nCount % 2 == 0)//偶数の場合
			{
				pIdx[nCount] = (WORD)(widthblock + 1 + nX);
				nX++;
			}
			else//奇数の場合
			{
				pIdx[nCount] = (WORD)nX2;
				nX2++;
			}
		}
	}

	//ポリゴンの数だけ回す
	for (int i = 0; i < m_nPolygon; i++)
	{
		//縮退ならコンティニュー
		if ((pIdx[i] == pIdx[i + 1]) || (pIdx[i + 1] == pIdx[i + 2]))
		{
			continue;
		}

		//法線ベクトルを格納する変数
		D3DXVECTOR3 SurfaceNorVec;	//面法線のベクトル
		D3DXVECTOR3 vecNormal;		//正規化したベクトル
		D3DXVECTOR3 vector1;		//１つ目のベクトルの保管用
		D3DXVECTOR3 vector2;		//２つ目のベクトルの保管用

		//インデックスを格納する変数
		WORD index0 = pIdx[i + 0];
		WORD index1 = pIdx[i + 1];
		WORD index2 = pIdx[i + 2];

		//頂点を格納する変数
		VERTEX_3D* vtx0 = pVtx + index0;
		VERTEX_3D* vtx1 = pVtx + index1;
		VERTEX_3D* vtx2 = pVtx + index2;

		//法線ベクトルの算出
		if ((i & 1) == 0) //偶数
		{
			vector1 = vtx1->pos - vtx0->pos;
			vector2 = vtx2->pos - vtx0->pos;
		}
		else //奇数
		{
			vector1 = vtx2->pos - vtx0->pos;
			vector2 = vtx1->pos - vtx0->pos;
		}

		//ベクトルの計算
		D3DXVec3Cross(&SurfaceNorVec, &vector1, &vector2);

		//ベクトルの正規化
		D3DXVec3Normalize(&vecNormal, &SurfaceNorVec);

		//ベクトルを加算
		vtx0->nor += vecNormal;
		vtx1->nor += vecNormal;
		vtx2->nor += vecNormal;
	}

	//加算したベクトルを正規化
	for (int nCount = 0; nCount < m_nVertex; nCount++)
	{
		//ベクトルの正規化
		D3DXVec3Normalize(&pVtx[nCount].nor, &pVtx[nCount].nor);
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//インデックスバッファのアンロック
	m_pIdxBuff->Unlock();

	return S_OK;
}

//============================
//頂点の計算
//============================
void CObjectMesh::VtxPosCluculation(MESHTYPE meshtype)
{
	VERTEX_3D* pVtx; //追加情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//ローカル変数宣言
	int nWidthCount = 0;
	int nHeightCount = 0;

	//頂点の数だけ回す
	for (int nCount = 0; nCount < m_nVertex; nCount++)
	{
		//位置の設定
		switch (meshtype)
		{
			//フィールド
		case MESHTYPE_FIELD:
			pVtx[nCount].pos = D3DXVECTOR3(m_size.x * (nWidthCount / (float)m_block.x) - (m_size.x * 0.5f), 0.0f, -m_size.z * (nHeightCount / (float)m_block.z) + (m_size.z * 0.5f));

			//テクスチャの読み込み
			pVtx[nCount].tex = D3DXVECTOR2(1.0f * (nWidthCount / (float)m_block.x), 1.0f * (nHeightCount / (float)m_block.z));

			//法線ベクトルの設定
			pVtx[nCount].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
			break;

			//壁
		case MESHTYPE_WALL:
			pVtx[nCount].pos = D3DXVECTOR3(m_size.x * (nWidthCount / (float)m_block.x) - (m_size.x * 0.5f), -m_size.y * (nHeightCount / (float)m_block.y) + (m_size.y * 0.5f), 0.0f);

			//テクスチャの読み込み
			pVtx[nCount].tex = D3DXVECTOR2(1.0f * (nWidthCount / (float)m_block.x), 1.0f * (nHeightCount / (float)m_block.y));

			//法線ベクトルの設定
			pVtx[nCount].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			break;
		}

		//カウントアップ
		nWidthCount++;

		//横のカウントアップ
		if (nWidthCount == m_block.x + 1)
		{
			nWidthCount = 0;
			nHeightCount++;
		}

		//頂点カラーの設定
		pVtx[nCount].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//============================
//オブジェクトメッシュの終了処理
//============================
void CObjectMesh::Uninit()
{
	//頂点の破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//インデックスバッファの破棄
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}

	//テクスチャの破棄
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	//自分の開放
	if (this != nullptr)
	{
		//消去
		SetDeath();
	}
}

//============================
//オブジェクトメッシュの更新
//============================
void CObjectMesh::Update()
{
	
}

//============================
//オブジェクトメッシュの描画
//============================
void CObjectMesh::Draw()
{
	//ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;														//計算用マトリックス
	
	//ワールドの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVertex, 0, m_nPolygon);
}

//============================
//オブジェクトメッシュの描画
//============================
void CObjectMesh::Draw(const char* pfilepath)
{
	//ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;														//計算用マトリックス
	CTexture* pTexture = CManager::GetInstance()->GetTexture();							//テクスチャの読み込み

	//ワールドの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetAddress(pTexture->Regist(pfilepath)));

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVertex, 0, m_nPolygon);
}

//================================
//オブジェクトメッシュのクリエイト
//================================
CObjectMesh* CObjectMesh::Create(D3DXVECTOR3 pos)
{
	//ポインタ用の変数
	CObjectMesh* pObjectX;

	//メモリの確保
	pObjectX = new CObjectMesh;

	//パラメータの設定
	pObjectX->SetPos(pos);	//位置の設定

	//初期化
	pObjectX->Init();

	return pObjectX;
}

//================================
//頂点の位置設定
//================================
void CObjectMesh::SetVtxPos(int index, D3DXVECTOR3 pos)
{
	//頂点情報が無いなら関数を抜ける
	if (m_pVtxBuff == nullptr)
	{
		return;
	}

	//頂点用のローカル変数
	VERTEX_3D* pVtx; //追加情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点に位置を設定
	pVtx[index].pos = pos;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================
//頂点の色設定
//================================
void CObjectMesh::SetVtxColor(int index, D3DXCOLOR color)
{
	//頂点情報が無いなら関数を抜ける
	if (m_pVtxBuff == nullptr)
	{
		return;
	}

	//頂点用のローカル変数
	VERTEX_3D* pVtx; //追加情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点に位置を設定
	pVtx[index].col = color;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================
//頂点の色設定
//================================
void CObjectMesh::SetVtxTex(int index, D3DXVECTOR2 tex)
{
	//頂点情報が無いなら関数を抜ける
	if (m_pVtxBuff == nullptr)
	{
		return;
	}

	//頂点用のローカル変数
	VERTEX_3D* pVtx; //追加情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点に位置を設定
	pVtx[index].tex = tex;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//================================
//ポリゴンの色設定
//================================
void CObjectMesh::SetColor(D3DXCOLOR color)
{
	//頂点情報が無いなら関数を抜ける
	if (m_pVtxBuff == nullptr)
	{
		return;
	}

	//色を設定
	m_Color = color;

	//頂点用のローカル変数
	VERTEX_3D* pVtx; //追加情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点数だけ周回
	for (int i = 0; i < m_nVertex; i++)
	{
		//頂点に位置を設定
		pVtx[i].col = color;
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}