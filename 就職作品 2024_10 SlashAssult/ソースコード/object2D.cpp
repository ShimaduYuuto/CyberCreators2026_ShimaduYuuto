//======================================
//
//	オブジェクト2Dの処理[object2D.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "object2D.h"
#include "manager.h"

//============================
//オブジェクト2Dのコンストラクタ
//============================
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	//ポインタの初期化
	m_pVtxBuff = nullptr;

	//パラメータの初期化
	m_polygon.move = { 0.0f, 0.0f, 0.0f };
	m_polygon.rot = { 0.0f, 0.0f, 0.0f };
	m_polygon.size = { 100.0f, 0.0f, 100.0f };
}

//============================
//オブジェクト2Dのデストラクタ
//============================
CObject2D::~CObject2D()
{
	//頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//============================
//オブジェクト2Dの初期化
//============================
HRESULT CObject2D::Init()
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスを取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D* pVtx; //追加情報のポインタ

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
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

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
//オブジェクト2Dの終了処理
//============================
void CObject2D::Uninit()
{
	//自分の開放
	if (this != nullptr)
	{
		//消去
		SetDeath();
	}
}

//============================
//オブジェクト2Dの更新
//============================
void CObject2D::Update()
{
	//位置の取得
	D3DXVECTOR3 Pos = GetPos();

	//移動量の加算
	Pos += m_polygon.move;

	//位置の設定
	SetPos(Pos);

	//頂点情報の更新
	UpdateVertex();
}

//============================
//オブジェクト2Dの割合更新
//============================
void CObject2D::Update(float max, float value)
{
	//ローカル変数
	float fRate = value / max;	//ポリゴンの割合
	VERTEX_2D* pVtx;			//追加情報のポインタ
	D3DXVECTOR3 Pos = GetPos();	//位置の取得

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点情報の更新
	pVtx[0].pos.x = Pos.x - (m_polygon.size.x * 0.5f);
	pVtx[0].pos.y = Pos.y - (m_polygon.size.y * 0.5f);
	pVtx[1].pos.x = Pos.x + (m_polygon.size.x * fRate) - (m_polygon.size.x * 0.5f);
	pVtx[1].pos.y = Pos.y - (m_polygon.size.y * 0.5f);
	pVtx[2].pos.x = Pos.x - (m_polygon.size.x * 0.5f);
	pVtx[2].pos.y = Pos.y + (m_polygon.size.y * 0.5f);
	pVtx[3].pos.x = Pos.x + (m_polygon.size.x * fRate) - (m_polygon.size.x * 0.5f);
	pVtx[3].pos.y = Pos.y + (m_polygon.size.y * 0.5f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f * fRate, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f * fRate, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//位置の設定
	CObject::SetPos(Pos);
}

//============================
//オブジェクト2Dの描画
//============================
void CObject2D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//αテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);

	//αテストを元に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//============================
//オブジェクト2Dの描画
//============================
void CObject2D::Draw(const char* texturepath)
{
	//テクスチャの読み込み
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//αテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetAddress(pTexture->Regist(texturepath)));

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);

	//αテストを元に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//============================
//オブジェクト2Dのクリエイト
//============================
CObject2D* CObject2D::Create()
{
	//ポインタ用の変数
	CObject2D* pObject;

	//メモリの確保
	pObject = new CObject2D;

	//初期化
	pObject->Init();

	return pObject;
}

//============================
//色の設定
//============================
void CObject2D::SetColor(D3DXCOLOR color)
{
	//中身がないなら抜ける
	if (m_pVtxBuff == nullptr)
	{
		return;
	}

	VERTEX_2D* pVtx; //追加情報のポインタ

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
void CObject2D::SetTextureUV(float u1, float u2, float v1, float v2)
{
	//中身がないなら抜ける
	if (m_pVtxBuff == nullptr)
	{
		return;
	}

	VERTEX_2D* pVtx; //追加情報のポインタ

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
//頂点情報の更新
//============================
void CObject2D::UpdateVertex()
{
	//位置の取得
	D3DXVECTOR3 Pos = GetPos();

	VERTEX_2D* pVtx; //追加情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//ローカル変数で長さを計算
	float fLength = sqrtf(m_polygon.size.x * m_polygon.size.x + m_polygon.size.y * m_polygon.size.y) * 0.5f; //対角線の長さを算出する
	float fAngle = atan2f(m_polygon.size.x, m_polygon.size.y);//対角線の角度を算出

	//頂点情報の更新
	pVtx[0].pos.x = Pos.x + sinf(m_polygon.rot.z + -(D3DX_PI - fAngle)) * fLength;
	pVtx[0].pos.y = Pos.y + cosf(m_polygon.rot.z + -(D3DX_PI - fAngle)) * fLength;
	pVtx[1].pos.x = Pos.x + sinf(m_polygon.rot.z + (D3DX_PI - fAngle)) * fLength;
	pVtx[1].pos.y = Pos.y + cosf(m_polygon.rot.z + (D3DX_PI - fAngle)) * fLength;
	pVtx[2].pos.x = Pos.x + sinf(m_polygon.rot.z + -fAngle) * fLength;
	pVtx[2].pos.y = Pos.y + cosf(m_polygon.rot.z + -fAngle) * fLength;
	pVtx[3].pos.x = Pos.x + sinf(m_polygon.rot.z + fAngle) * fLength;
	pVtx[3].pos.y = Pos.y + cosf(m_polygon.rot.z + fAngle) * fLength;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//============================
//向きの設定
//============================
void CObject2D::SetRot(D3DXVECTOR3 rot) 
{ 
	//向きを設定
	m_polygon.rot = rot; 

	//頂点の更新
	if (m_pVtxBuff != nullptr)
	{
		UpdateVertex();
	}
}		

//============================
//向きの設定
//============================
void CObject2D::SetSize(D3DXVECTOR3 size) 
{ 
	//サイズの設定
	m_polygon.size = size; 

	//頂点の更新
	if (m_pVtxBuff != nullptr)
	{
		UpdateVertex();
	}
}

//============================
//位置の設定
//============================
void CObject2D::SetPos(D3DXVECTOR3 pos)
{
	//位置の設定
	CObject::SetPos(pos);

	//頂点の更新
	if (m_pVtxBuff != nullptr)
	{
		UpdateVertex();
	}
}