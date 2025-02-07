//======================================
//
//	シリンダーオブジェクトの処理[objectcylinder.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "objectcylinder.h"
#include "manager.h"
#include "game.h"

//オブジェクトメッシュクラスの定数の初期化
const int CObjectCylinder::NUM_CORNER = 10;			//角の数
const float CObjectCylinder::HEIGHT = 50.0f;		//高さ

//============================
//オブジェクトメッシュのコンストラクタ
//============================
CObjectCylinder::CObjectCylinder(int nPriority) : CObject(nPriority),
	m_Color(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)),
	m_fRadius(0.0f),
	m_fRate(1.0f),
	m_mtxWorld(),
	m_nIndex(),
	m_nPolygon(),
	m_nVertex(),
	m_pIdxBuff(),
	m_pVtxBuff(),
	m_rot(),
	m_fHeight(0.0f)
{
	//パラメータの初期化
	m_rot = { 0.0f, 0.0f, 0.0f };	//向き
	m_mtxWorld = {};				//ワールドマトリックス
	m_nIndex = 0;					//番号の数
	m_nPolygon = 0;					//ポリゴンの数
	m_nVertex = 0;					//頂点の数
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//色の設定
	m_fHeight = HEIGHT;				//高さ
}

//============================
//オブジェクトメッシュのデストラクタ
//============================
CObjectCylinder::~CObjectCylinder()
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
}

//============================
//オブジェクトメッシュの初期化
//============================
HRESULT CObjectCylinder::Init()
{
	//ローカル変数
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ
	m_nIndex = ((NUM_CORNER + 1) * 2);	//インデックス数
	m_nVertex = ((NUM_CORNER + 1) * 2);		//頂点数
	m_nPolygon = (NUM_CORNER * 2);		//ポリゴン数

	//デバイスを取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得

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

	//上下の数周回
	for (int j = 0; j < 2; j++)
	{
		//角の数だけ周回
		for (int i = 0; i < NUM_CORNER + 1; i++)
		{
			//角度を算出
			float fAngle = (D3DX_PI * 2) * (float)(i / (float)NUM_CORNER);

			//各変数に値を代入
			pVtx[i + (NUM_CORNER + 1) * j].pos = D3DXVECTOR3(sinf(fAngle) * m_fRadius, m_fHeight - (m_fHeight * j), cosf(fAngle) * m_fRadius);	//位置
			pVtx[i + (NUM_CORNER + 1) * j].tex = D3DXVECTOR2(1.0f * (i / (float)NUM_CORNER), static_cast<float>(j));	//UV座標
			pVtx[i + (NUM_CORNER + 1) * j].nor = D3DXVECTOR3(sinf(fAngle + D3DX_PI) / D3DX_PI,
				0.0f,
				cosf(fAngle + D3DX_PI) / D3DX_PI);	//法線ベクトル
			pVtx[i + NUM_CORNER * j].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);				//色
		}
	}

	//インデックスの計算用の変数
	nX = 0;
	nHeightCount = 0;
	int nAngleCount = 0;

	//インデックスの計算
	for (int i = 0; i < m_nIndex; i++)
	{
		//偶数の場合
		if ((i & 1) == 0)
		{
			pIdx[i] = (WORD)((NUM_CORNER + 1) + nAngleCount);
		}
		else//奇数の場合
		{
			pIdx[i] = (WORD)nAngleCount;
			nAngleCount++;
		}

		//1週する時にカウントの初期化
		if (nAngleCount == NUM_CORNER)
		{
			//nAngleCount = 0;
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
//オブジェクトメッシュの終了処理
//============================
void CObjectCylinder::Uninit()
{
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
void CObjectCylinder::Update()
{

	VERTEX_3D* pVtx; //追加情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//上下の数周回
	for (int j = 0; j < 2; j++)
	{
		//角の数だけ周回
		for (int i = 0; i < (NUM_CORNER + 1); i++)
		{
			//角度を算出
			float fAngle = (D3DX_PI * 2) * (float)(i / (float)NUM_CORNER);

			//各変数に値を代入
			pVtx[i + (NUM_CORNER + 1) * j].pos = D3DXVECTOR3(sinf(fAngle) * m_fRadius * m_fRate, m_fHeight - (m_fHeight * j), cosf(fAngle) * m_fRadius * m_fRate);	//位置
		}
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//============================
//オブジェクトメッシュの描画
//============================
void CObjectCylinder::Draw()
{
	//ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得
	CTexture* pTexture = CManager::GetInstance()->GetTexture();							//テクスチャの読み込み

	//マトリックスの計算
	MtxCalculation();

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
void CObjectCylinder::Draw(const char* path)
{
	//ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得
	CTexture* pTexture = CManager::GetInstance()->GetTexture();							//テクスチャの読み込み

	//マトリックスの計算
	MtxCalculation();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetAddress(pTexture->Regist(path)));

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVertex, 0, m_nPolygon);
}

//============================
//マトリックスの計算
//============================
void CObjectCylinder::MtxCalculation()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

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
}

//================================
//オブジェクトメッシュのクリエイト
//================================
CObjectCylinder* CObjectCylinder::Create(D3DXVECTOR3 pos, float radius)
{
	//ポインタ用の変数
	CObjectCylinder* pObject;

	//メモリの確保
	pObject = new CObjectCylinder;

	//パラメータの設定
	pObject->SetPos(pos);			//位置の設定
	pObject->m_fRadius = radius;	//半径の設定

	//初期化
	pObject->Init();

	return pObject;
}

//================================
//頂点カラーの設定
//================================
void CObjectCylinder::SetColor(D3DXCOLOR color)
{
	VERTEX_3D* pVtx; //追加情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//上下の数周回
	for (int j = 0; j < 2; j++)
	{
		//角の数だけ周回
		for (int i = 0; i < (NUM_CORNER + 1); i++)
		{
			pVtx[i + (NUM_CORNER + 1) * j].col = color;	//色
		}
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//変数に保存
	m_Color = color;
}