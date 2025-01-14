//======================================
//
//	ビルボードの処理[objectbillboard.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "objectbillboard.h"
#include "manager.h"

//============================
//ビルボードのコンストラクタ
//============================
CObjectBillboard::CObjectBillboard(int nPriority) : CObject(nPriority)
{
	//ポインタの初期化
	m_pVtxBuff = nullptr;

	//パラメータの初期化
	m_polygon.move = { 0.0f, 0.0f, 0.0f };
	m_polygon.size = { 0.0f, 0.0f, 0.0f };
	m_polygon.ratio = 1.0f;
}

//============================
//ビルボードのデストラクタ
//============================
CObjectBillboard::~CObjectBillboard()
{
	//頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//============================
//ビルボードの初期化
//============================
HRESULT CObjectBillboard::Init()
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
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
//ビルボードの終了処理
//============================
void CObjectBillboard::Uninit()
{
	//自分の開放
	if (this != nullptr)
	{
		//消去
		SetDeath();
	}
}

//============================
//ビルボードの更新
//============================
void CObjectBillboard::Update()
{
	//位置の取得
	D3DXVECTOR3 Pos = GetPos();

	//移動量の加算
	Pos += m_polygon.move;

	//位置の設定
	SetPos(Pos);
}

//============================
//ビルボードの描画
//============================
void CObjectBillboard::Draw()
{
	//位置の取得
	D3DXVECTOR3 Pos = GetPos();

	//描画用のローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice;		//デバイスの取得用
	D3DXMATRIX mtxTrans;			//計算用マトリックス
	D3DXMATRIX mtxView;				//ビューマトリックス取得用

	//デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//Zの比較方法変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	//Zバッファに書き込まない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//ワールドの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに対してを正面に向ける
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

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

	//Zの比較方法変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//Zバッファに書き込む
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//位置の設定
	SetPos(Pos);
}

//============================
//ビルボードの描画
//============================
void CObjectBillboard::Draw(const char* texturepath)
{
	//位置の取得
	D3DXVECTOR3 Pos = GetPos();

	//テクスチャの読み込み
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	//描画用のローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice;		//デバイスの取得用
	D3DXMATRIX mtxTrans;			//計算用マトリックス
	D3DXMATRIX mtxView;				//ビューマトリックス取得用

	//デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//Zバッファに書き込まない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//ワールドの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに対してを正面に向ける
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

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

	//Zバッファに書き込む
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//位置の設定
	SetPos(Pos);
}

//============================
//ビルボードのクリエイト
//============================
CObjectBillboard* CObjectBillboard::Create()
{
	//ポインタ用の変数
	CObjectBillboard* pObject;

	//メモリの確保
	pObject = new CObjectBillboard;

	//初期化
	pObject->Init();

	return pObject;
}

//============================
//色の設定
//============================
void CObjectBillboard::SetColor(D3DXCOLOR color)
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
//テクスチャの座標設定
//============================
void CObjectBillboard::SetTextureUV(float u1, float u2, float v1, float v2)
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

//============================
//サイズの設定
//============================
void CObjectBillboard::SetSize(D3DXVECTOR3 size)
{
	//サイズの設定
	m_polygon.size = size;

	VERTEX_3D* pVtx; //追加情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fLength = sqrtf(m_polygon.size.x * m_polygon.size.x + m_polygon.size.y * m_polygon.size.y) * 0.5f * m_polygon.ratio; //対角線の長さを算出する
	float fAngle = atan2f(m_polygon.size.x, m_polygon.size.y);	//対角線の角度を算出

	//ポリゴンのサイズ
	pVtx[0].pos.x = sinf(-(D3DX_PI - fAngle)) * fLength;
	pVtx[0].pos.y = cosf(-(D3DX_PI - fAngle)) * -fLength;
	pVtx[1].pos.x = sinf((D3DX_PI - fAngle)) * fLength;
	pVtx[1].pos.y = cosf((D3DX_PI - fAngle)) * -fLength;
	pVtx[2].pos.x = sinf(-fAngle) * fLength;
	pVtx[2].pos.y = cosf(-fAngle) * -fLength;
	pVtx[3].pos.x = sinf(fAngle) * fLength;
	pVtx[3].pos.y = cosf(fAngle) * -fLength;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//============================
//倍率の設定
//============================
void CObjectBillboard::SetRatio(float ratio)
{
	//サイズの設定
	m_polygon.ratio = ratio;

	VERTEX_3D* pVtx; //追加情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fLength = sqrtf(m_polygon.size.x * m_polygon.size.x + m_polygon.size.y * m_polygon.size.y) * 0.5f * m_polygon.ratio; //対角線の長さを算出する
	float fAngle = atan2f(m_polygon.size.x, m_polygon.size.y);	//対角線の角度を算出

	//ポリゴンのサイズ
	pVtx[0].pos.x = sinf(-(D3DX_PI - fAngle)) * fLength;
	pVtx[0].pos.y = cosf(-(D3DX_PI - fAngle)) * -fLength;
	pVtx[1].pos.x = sinf((D3DX_PI - fAngle)) * fLength;
	pVtx[1].pos.y = cosf((D3DX_PI - fAngle)) * -fLength;
	pVtx[2].pos.x = sinf(-fAngle) * fLength;
	pVtx[2].pos.y = cosf(-fAngle) * -fLength;
	pVtx[3].pos.x = sinf(fAngle) * fLength;
	pVtx[3].pos.y = cosf(fAngle) * -fLength;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}