//======================================
//
//	オブジェクト3Dの処理[object3D.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "object3D.h"
#include "manager.h"

//============================
//オブジェクト3Dのコンストラクタ
//============================
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{
	//ポインタの初期化
	m_pVtxBuff = nullptr;

	//パラメータの初期化
	m_polygon.move = { 0.0f, 0.0f, 0.0f };
	m_polygon.rot = { 0.0f, 0.0f, 0.0f };
	m_polygon.size = { 0.0f, 0.0f, 0.0f };
	m_polygon.fRate = 1.0f;
}

//============================
//オブジェクト3Dのデストラクタ
//============================
CObject3D::~CObject3D()
{
	//頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//============================
//オブジェクト3Dの初期化
//============================
HRESULT CObject3D::Init()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスを取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D* pVtx; //追加情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の更新
	pVtx[0].pos.x = 0.0f;
	pVtx[0].pos.y = 0.0f;
	pVtx[1].pos.x = 0.0f;
	pVtx[1].pos.y = 0.0f;
	pVtx[2].pos.x = 0.0f;
	pVtx[2].pos.y = 0.0f;
	pVtx[3].pos.x = 0.0f;
	pVtx[3].pos.y = 0.0f;

	//rhwの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);//u.v
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//============================
//オブジェクト3Dの終了処理
//============================
void CObject3D::Uninit()
{
	//自分の開放
	if (this != nullptr)
	{
		//消去
		SetDeath();
	}
}

//============================
//オブジェクト3Dの更新
//============================
void CObject3D::Update()
{
	
}

//============================
//オブジェクト3Dの描画
//============================
void CObject3D::Draw()
{
	//位置の取得
	D3DXVECTOR3 Pos = GetPos();

	//描画用の変数
	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//ワールドの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_polygon.rot.y, m_polygon.rot.x, m_polygon.rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, Pos.x, Pos.y, Pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//位置の設定
	SetPos(Pos);
}

//============================
//オブジェクト3Dの描画
//============================
void CObject3D::Draw(const char* texturepath)
{
	//位置の取得
	D3DXVECTOR3 Pos = GetPos();

	//テクスチャの読み込み
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//ワールドの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_polygon.rot.y, m_polygon.rot.x, m_polygon.rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, Pos.x, Pos.y, Pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetAddress(pTexture->Regist(texturepath)));

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//位置の設定
	SetPos(Pos);
}

//============================
//オブジェクト3Dのクリエイト
//============================
CObject3D* CObject3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//ポインタ用の変数
	CObject3D* pObject;

	//メモリの確保
	pObject = new CObject3D;

	//初期化
	pObject->Init();
	pObject->SetPos(pos);
	pObject->SetSize(size);

	return pObject;
}

//============================
//色の設定
//============================
void CObject3D::SetColor(D3DXCOLOR color)
{
	VERTEX_3D* pVtx; //追加情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//============================
//サイズの設定
//============================
void CObject3D::SetSize(D3DXVECTOR3 size, TYPE type)
{
	//サイズの設定
	m_polygon.size = size;

	//計算用の変数
	float fLength = 0.0f;	//対角線の長さを算出する
	float fAngle = 0.0f;	//対角線の角度を算出

	VERTEX_3D* pVtx; //追加情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//計算の変更
	switch (type)
	{
	case TYPE_FLOOR:
		fLength = sqrtf(m_polygon.size.x * m_polygon.size.x + m_polygon.size.z * m_polygon.size.z) * 0.5f * m_polygon.fRate; //対角線の長さを算出する
		fAngle = atan2f(m_polygon.size.x, m_polygon.size.z);	//対角線の角度を算出

		//ポリゴンのサイズ
		pVtx[0].pos.x = sinf(m_polygon.rot.y + (D3DX_PI - fAngle)) * fLength;
		pVtx[0].pos.z = cosf(m_polygon.rot.y + (D3DX_PI - fAngle)) * fLength;
		pVtx[1].pos.x = sinf(m_polygon.rot.y + -(D3DX_PI - fAngle)) * fLength;
		pVtx[1].pos.z = cosf(m_polygon.rot.y + -(D3DX_PI - fAngle)) * fLength;
		pVtx[2].pos.x = sinf(m_polygon.rot.y + fAngle) * fLength;
		pVtx[2].pos.z = cosf(m_polygon.rot.y + fAngle) * fLength;
		pVtx[3].pos.x = sinf(m_polygon.rot.y + -fAngle) * fLength;
		pVtx[3].pos.z = cosf(m_polygon.rot.y + -fAngle) * fLength;
	break;

	case TYPE_WALL:
		fLength = sqrtf(m_polygon.size.x * m_polygon.size.x + m_polygon.size.y * m_polygon.size.y) * 0.5f * m_polygon.fRate; //対角線の長さを算出する
		fAngle = atan2f(m_polygon.size.x, m_polygon.size.y);	//対角線の角度を算出

		//ポリゴンのサイズ
		pVtx[0].pos.x = sinf(m_polygon.rot.z + -(D3DX_PI - fAngle)) * fLength;
		pVtx[0].pos.y = cosf(m_polygon.rot.z + -(D3DX_PI - fAngle)) * -fLength;
		pVtx[1].pos.x = sinf(m_polygon.rot.z + (D3DX_PI - fAngle)) * fLength;
		pVtx[1].pos.y = cosf(m_polygon.rot.z + (D3DX_PI - fAngle)) * -fLength;
		pVtx[2].pos.x = sinf(m_polygon.rot.z + -fAngle) * fLength;
		pVtx[2].pos.y = cosf(m_polygon.rot.z + -fAngle) * -fLength;
		pVtx[3].pos.x = sinf(m_polygon.rot.z + fAngle) * fLength;
		pVtx[3].pos.y = cosf(m_polygon.rot.z + fAngle) * -fLength;
	break;
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//============================
//ポリゴンの計算
//============================
void CObject3D::Calculation(D3DXVECTOR3 rot, TYPE type)
{
	VERTEX_3D* pVtx; //追加情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//計算の変更
	switch (type)
	{
	case TYPE_FLOOR:
		//法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		break;

	case TYPE_WALL:

		{
			//角度の最大を１とした向きを算出
			float fNorVec = rot.y / D3DX_PI;

			//法線の設定
			pVtx[0].nor = D3DXVECTOR3(sinf(fNorVec), 0.0f,cosf(fNorVec));
			pVtx[1].nor = D3DXVECTOR3(sinf(fNorVec), 0.0f,cosf(fNorVec));
			pVtx[2].nor = D3DXVECTOR3(sinf(fNorVec), 0.0f,cosf(fNorVec));
			pVtx[3].nor = D3DXVECTOR3(sinf(fNorVec), 0.0f,cosf(fNorVec));
				
		}
		
		break;
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//============================
//テクスチャの座標設定
//============================
void CObject3D::SetTextureUV(float u1, float u2, float v1, float v2)
{
	VERTEX_3D* pVtx; //追加情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(u1, v1);//u.v
	pVtx[1].tex = D3DXVECTOR2(u2, v1);
	pVtx[2].tex = D3DXVECTOR2(u1, v2);
	pVtx[3].tex = D3DXVECTOR2(u2, v2);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}