//======================================
//
//	ドームオブジェクトの処理[objectdome.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "objectdome.h"
#include "manager.h"

//オブジェクトメッシュクラスの定数の初期化
const int CObjectDome::NUM_CORNER = 4;			//角の数
const float CObjectDome::HEIGHT = 50.0f;		//高さ

//============================
//オブジェクトメッシュのコンストラクタ
//============================
CObjectDome::CObjectDome(int nPriority) : CObject(nPriority),
m_Color(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)),
m_fRadius(0.0f),
m_fRate(1.0f),
m_mtxWorld(),
m_nIndex(),
m_nPolygon(),
m_nVertex(),
m_pIdxBuff(),
m_pVtxBuff(),
m_rot()
{
	//パラメータの初期化
	m_rot = { 0.0f, 0.0f, 0.0f };	//向き
	m_mtxWorld = {};				//ワールドマトリックス
	m_nIndex = 0;					//番号の数
	m_nPolygon = 0;					//ポリゴンの数
	m_nVertex = 0;					//頂点の数
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//色の設定
}

//============================
//オブジェクトメッシュのデストラクタ
//============================
CObjectDome::~CObjectDome()
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

	CObject::Uninit();
}

//============================
//オブジェクトメッシュの初期化
//============================
HRESULT CObjectDome::Init()
{
	//ローカル変数
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ
	m_nIndex = ((NUM_CORNER * 2 + 2) * (NUM_VIRTICAL - 1)) + 2 * (NUM_VIRTICAL - 2);	//インデックス数
	m_nVertex = NUM_CORNER * (NUM_VIRTICAL - 1) + 1;									//頂点数(角の数*高さ+一番上の頂点)
	m_nPolygon = (NUM_CORNER * 2 * ((NUM_VIRTICAL - 1)) + 4 * (NUM_VIRTICAL - 2));		//ポリゴン数

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

	//一番上の頂点を別で初期化する
	pVtx[0].pos = D3DXVECTOR3(0.0f, m_fRadius, 0.0f);
	pVtx[0].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx++;	//次のポインタに進める

	//上下の数周回
	for (int j = 1; j < NUM_VIRTICAL; j++)
	{
		//倍率
		float fHeightRate = 1.0f - ((float)j / (NUM_VIRTICAL - 1));
		float fWidthRate = ((float)j / (NUM_VIRTICAL - 1));

		//角の数だけ周回
		for (int i = 0; i < NUM_CORNER; i++)
		{
			//角度を算出
			float fAngle = (D3DX_PI * 2) * (float)(i / (float)NUM_CORNER);

			//各変数に値を代入
			pVtx[i + NUM_CORNER * (j - 1)].pos = D3DXVECTOR3(
				sinf(fAngle) * m_fRadius * cosf(fHeightRate * D3DX_PI * 0.5f),
				sinf(fHeightRate * D3DX_PI * 0.5f) * m_fRadius,
				cosf(fAngle) * m_fRadius * cosf(fHeightRate * D3DX_PI * 0.5f));


			pVtx[i + NUM_CORNER * (j - 1)].tex = D3DXVECTOR2(1.0f * (i / NUM_CORNER), fWidthRate);	//UV座標
			pVtx[i + NUM_CORNER * (j - 1)].nor = D3DXVECTOR3(sinf(fAngle + D3DX_PI) / D3DX_PI,
				0.0f,
				cosf(fAngle + D3DX_PI) / D3DX_PI);	//法線ベクトル
			pVtx[i + NUM_CORNER * (j - 1)].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);				//色
		}
	}

	pVtx--;	//ポインタを元に戻す

	//インデックスの計算用の変数
	nX = 0;
	nHeightCount = 0;
	int nAngleCount = 0;

	//インデックスの計算
	for (int i = 0; i < NUM_VIRTICAL - 1; i++)
	{
		//カウントの初期化
		nAngleCount = 0;
		int nAddCount = i * (NUM_CORNER * 2 + 4);

		//縮退の計算
		if (i > 0)
		{
			pIdx[nAddCount - 2] = (WORD)1 + ((i - 1) * NUM_CORNER);
			pIdx[nAddCount - 1] = (WORD)1 + ((i - 1) * NUM_CORNER);
		}

		for (int j = 0; j < NUM_CORNER * 2; j++)
		{
			//偶数の場合
			if ((j & 1) == 0)
			{
				pIdx[j + nAddCount] = (WORD)1 + nAngleCount + (i * NUM_CORNER);
			}
			else//奇数の場合
			{
				//最初の周回なら0を設定
				if (i == 0)
				{
					pIdx[j + nAddCount] = (WORD)0;
				}
				else
				{
					pIdx[j + nAddCount] = (WORD)nAngleCount + NUM_CORNER * (i - 1) + 1;
				}
				
				nAngleCount++;
			}
		}

		//一周の最後(後で各集会の最初のIdxを代入する)
		pIdx[NUM_CORNER * 2 + nAddCount] = pIdx[0 + nAddCount];
		pIdx[NUM_CORNER * 2 + 1 + nAddCount] = pIdx[1 + nAddCount];
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
void CObjectDome::Uninit()
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
void CObjectDome::Update()
{
	VERTEX_3D* pVtx; //追加情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	int nX = 0;
	int nHeightCount = 0;

	//一番上の頂点を別で初期化する
	pVtx[0].pos = D3DXVECTOR3(0.0f, m_fRadius * m_fRate, 0.0f);
	pVtx++;	//次のポインタに進める

	//上下の数周回
	for (int j = 1; j < NUM_VIRTICAL; j++)
	{
		//倍率
		float fHeightRate = 1.0f - ((float)j / (NUM_VIRTICAL - 1));
		float fWidthRate = ((float)j / (NUM_VIRTICAL - 1));

		//角の数だけ周回
		for (int i = 0; i < NUM_CORNER; i++)
		{
			//角度を算出
			float fAngle = (D3DX_PI * 2) * (float)(i / (float)NUM_CORNER);

			//各変数に値を代入
			pVtx[i + NUM_CORNER * (j - 1)].pos = D3DXVECTOR3(
				sinf(fAngle) * m_fRadius * cosf(fHeightRate * D3DX_PI * 0.5f) * m_fRate,
				sinf(fHeightRate * D3DX_PI * 0.5f) * m_fRadius * m_fRate,
				cosf(fAngle) * m_fRadius * cosf(fHeightRate * D3DX_PI * 0.5f) * m_fRate);
		}
	}

	pVtx--;	//ポインタを元に戻す

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//============================
//オブジェクトメッシュの描画
//============================
void CObjectDome::Draw()
{
	//ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;														//計算用マトリックス
	CTexture* pTexture = CManager::GetInstance()->GetTexture();							//テクスチャの読み込み

	//カリング方法を変更
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

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

	//カリング方法を変更
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//============================
//オブジェクトメッシュの描画
//============================
void CObjectDome::Draw(const char* path)
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
	pDevice->SetTexture(0, pTexture->GetAddress(pTexture->Regist(path)));

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVertex, 0, m_nPolygon);
}

//================================
//オブジェクトメッシュのクリエイト
//================================
CObjectDome* CObjectDome::Create(D3DXVECTOR3 pos, float radius)
{
	//ポインタ用の変数
	CObjectDome* pObject;

	//メモリの確保
	pObject = new CObjectDome;

	//パラメータの設定
	pObject->SetPos(pos);			//位置の設定
	pObject->m_fRadius = radius;	//半径の設定

	//初期化
	pObject->Init();

	return pObject;
}