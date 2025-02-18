//======================================
//
//	フィールドの処理[field.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "field.h"
#include "manager.h"

//フィールドクラスの定数の初期化
const std::string CField::TEXTUREPATH = "data\\TEXTURE\\FieldTexture000.png";	//テクスチャパス
const std::string CField::FILEPATH = "data\\FILE\\Field.bin";					//ファイルパス
const D3DXVECTOR3 CField::BLOCK = { 50.0f, 0, 50.0f };							//ブロック数
const D3DXVECTOR3 CField::SIZE = { 10000.0f, -2.0f, 10000.0f };					//サイズ

//============================
//フィールドのコンストラクタ
//============================
CField::CField(int nPriority) : CObject(nPriority)
{
	m_nIndex = (int)(2 * (BLOCK.x + 1) * BLOCK.z + (BLOCK.z - 1) * 2);	//インデックス数
	m_nVertex = (int)((BLOCK.x + 1) * (BLOCK.z + 1));					//頂点数
	m_nPolygon = (int)((BLOCK.x * BLOCK.z) * 2 + (BLOCK.z - 1) * 4);	//ポリゴン数
}

//============================
//フィールドのデストラクタ
//============================
CField::~CField()
{

}

//============================
//フィールドの初期化
//============================
HRESULT CField::Init()
{
	//フィールド情報の読み込み
	Load();

	VERTEX_3D* pVtx; //追加情報のポインタ

	//インデックスバッファをロック
	WORD* pIdx; //追加のポインタ
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

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

		//面法線ベクトルを保存
		m_SurfaceNorVec.push_back(vecNormal);
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
//フィールドの終了処理
//============================
void CField::Uninit()
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

	//消去
	CObject::Uninit();

	//面法線ベクトル情報を破棄
	m_SurfaceNorVec.clear();
}

//============================
//フィールドの更新
//============================
void CField::Update()
{

}

//============================
//フィールドの当たり判定
//============================
bool CField::MeshCollision(D3DXVECTOR3& pos)
{
	//返す用の変数
	bool bHit = false;	//当たったかの判定
	int nCnt = 0;		//メッシュのカウント

	float PlayerHeight = pos.y;	//キャラクターの高さ

	//メッシュ用変数
	WORD* pIdx; //追加のポインタ
	VERTEX_3D* pVtx; //追加情報のポインタ

	//インデックスバッファをロック
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//ポリゴンの数だけ回す
	for (int i = 0; i < m_nPolygon; i++)
	{
		//縮退ならコンティニュー
		if ((pIdx[i] == pIdx[i + 1]) || (pIdx[i + 1] == pIdx[i + 2]))
		{
			continue;
		}

		//当たり判定の確認
		if (CheckHit(i, pos, pVtx, pIdx))
		{
			//インデックスを格納する変数
			WORD index0 = pIdx[i + 0];

			//頂点を格納する変数
			VERTEX_3D* vtx0 = pVtx + index0;

			//内積の計算から高さを算出
			PlayerHeight = MeshIPCluculation(pos - vtx0->pos, m_SurfaceNorVec[nCnt]) + vtx0->pos.y;

			//現在の高さの方が下なら補正
			if (PlayerHeight >= pos.y)
			{
				//高さを合わせる
				pos.y = PlayerHeight;
				bHit = true;
			}

			//計算後周回を抜ける
			break;
		}

		//カウントアップ
		nCnt++;
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//インデックスバッファのアンロック
	m_pIdxBuff->Unlock();

	//当たり判定を返す
	return bHit;
}

//============================
//フィールドの当たり判定
//============================
bool CField::MeshCollision(D3DXVECTOR3& pos, D3DXVECTOR3& rot)
{
	//返す用の変数
	bool bHit = false;	//当たったかの判定
	int nCnt = 0;		//メッシュのカウント

	float PlayerHeight = pos.y;	//キャラクターの高さ

	//メッシュ用変数
	WORD* pIdx; //追加のポインタ
	VERTEX_3D* pVtx; //追加情報のポインタ

	//インデックスバッファをロック
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//ポリゴンの数だけ回す
	for (int i = 0; i < m_nPolygon; i++)
	{
		//縮退ならコンティニュー
		if ((pIdx[i] == pIdx[i + 1]) || (pIdx[i + 1] == pIdx[i + 2]))
		{
			continue;
		}

		//当たり判定の確認
		if (CheckHit(i, pos, pVtx, pIdx))
		{
			//インデックスを格納する変数
			WORD index0 = pIdx[i + 0];

			//頂点を格納する変数
			VERTEX_3D* vtx0 = pVtx + index0;

			//内積の計算から高さを算出
			PlayerHeight = MeshIPCluculation(pos - vtx0->pos, m_SurfaceNorVec[nCnt]) + vtx0->pos.y;

			//高さを合わせる
			pos.y = PlayerHeight;
			bHit = true;

			//向きを合わせる
			rot = m_SurfaceNorVec[nCnt];

			//計算後周回を抜ける
			break;
		}

		//カウントアップ
		nCnt++;
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//インデックスバッファのアンロック
	m_pIdxBuff->Unlock();

	//当たり判定を返す
	return bHit;
}

//=================================
//フィールドの位置に変換
//=================================
D3DXVECTOR3 CField::ConvertMeshPos(D3DXVECTOR3 pos)
{
	//計算に必要な変数
	float PlayerHeight = pos.y;	//キャラクターの高さ
	int nCnt = 0;		//メッシュのカウント

	//メッシュ用変数
	WORD* pIdx; //追加のポインタ
	VERTEX_3D* pVtx; //追加情報のポインタ

	//インデックスバッファをロック
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//ポリゴンの数だけ回す
	for (int i = 0; i < m_nPolygon; i++)
	{
		//縮退ならコンティニュー
		if ((pIdx[i] == pIdx[i + 1]) || (pIdx[i + 1] == pIdx[i + 2]))
		{
			continue;
		}

		//当たり判定の確認
		if (CheckHit(i, pos, pVtx, pIdx))
		{
			//インデックスを格納する変数
			WORD index0 = pIdx[i + 0];

			//頂点を格納する変数
			VERTEX_3D* vtx0 = pVtx + index0;

			//内積の計算から高さを算出
			PlayerHeight = MeshIPCluculation(pos - vtx0->pos, m_SurfaceNorVec[nCnt]) + vtx0->pos.y;

			//高さを合わせる
			pos.y = PlayerHeight;

			//計算後周回を抜ける
			break;
		}

		//カウントアップ
		nCnt++;
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//インデックスバッファのアンロック
	m_pIdxBuff->Unlock();

	//当たり判定を返す
	return pos;
}

//===================================
//当たり判定の確認
//===================================
bool CField::CheckHit(int count, D3DXVECTOR3 pos, VERTEX_3D* vtx, WORD* idx)
{
	//法線ベクトルを格納する変数
	D3DXVECTOR3 SurfaceNorVec;	//面法線のベクトル
	D3DXVECTOR3 vecNormal;		//正規化したベクトル
	D3DXVECTOR3 vector1;		//1つ目のベクトルの保管用
	D3DXVECTOR3 vector2;		//2つ目のベクトルの保管用
	D3DXVECTOR3 vector3;		//3つ目のベクトルの保管用
	D3DXVECTOR3 targetvector1;	//1つ目の対象ベクトルの保管用
	D3DXVECTOR3 targetvector2;	//2つ目の対象ベクトルの保管用
	D3DXVECTOR3 targetvector3;	//3つ目の対象ベクトルの保管用 
	D3DXVECTOR3 VecCross1;		//1つ目のベクトルの外積結果
	D3DXVECTOR3 VecCross2;		//2つ目のベクトルの外積結果
	D3DXVECTOR3 VecCross3;		//3つ目のベクトルの外積結果 

	//インデックスを格納する変数
	WORD index0 = idx[count + 0];
	WORD index1 = idx[count + 1];
	WORD index2 = idx[count + 2];

	//頂点を格納する変数
	VERTEX_3D* vtx0 = vtx + index0;
	VERTEX_3D* vtx1 = vtx + index1;
	VERTEX_3D* vtx2 = vtx + index2;

	//法線ベクトルの算出
	if ((count & 1) == 0) //偶数
	{
		//ポリゴンのベクトルを計算
		vector1 = vtx2->pos - vtx0->pos;
		vector2 = vtx1->pos - vtx2->pos;
		vector3 = vtx0->pos - vtx1->pos;

		//対象のベクトルを計算
		targetvector1 = pos - vtx0->pos;
		targetvector2 = pos - vtx2->pos;
		targetvector3 = pos - vtx1->pos;
	}
	else //奇数
	{
		//ポリゴンのベクトルを計算
		vector1 = vtx1->pos - vtx0->pos;
		vector2 = vtx2->pos - vtx1->pos;
		vector3 = vtx0->pos - vtx2->pos;

		//対象のベクトルを計算
		targetvector1 = pos - vtx0->pos;
		targetvector2 = pos - vtx1->pos;
		targetvector3 = pos - vtx2->pos;
	}

	//ベクトルの計算
	D3DXVec3Cross(&VecCross1, &targetvector1, &vector1);
	D3DXVec3Cross(&VecCross2, &targetvector2, &vector2);
	D3DXVec3Cross(&VecCross3, &targetvector3, &vector3);

	//ベクトルの正規化
	D3DXVec3Normalize(&VecCross1, &VecCross1);
	D3DXVec3Normalize(&VecCross2, &VecCross2);
	D3DXVec3Normalize(&VecCross3, &VecCross3);

	//ポリゴンの中にいたら色を変化
	if (VecCross1.y >= 0.0f && VecCross2.y >= 0.0f && VecCross3.y >= 0.0f)
	{
		return true;
	}

	return false;
}

//===================================
//内積の計算結果を返す
//===================================
float CField::MeshIPCluculation(D3DXVECTOR3 vec1, D3DXVECTOR3 vec2)
{
	//内積後の高さを格納する変数
	float Vec1_y = 0.0f;

	//内積の計算結果から高さを算出
	Vec1_y = (-(vec1.x * vec2.x) - (vec1.z * vec2.z)) / vec2.y;

	//高さを返す
	return Vec1_y;
}

//===================================
//横の判定
//===================================
D3DXVECTOR3 CField::WidthCollision(D3DXVECTOR3 pos, float radius)
{
	//返す用の位置
	D3DXVECTOR3 Pos = pos;

	//左の判定
	if (Pos.x < GetPos().x + COLLISION_WIDTH * -0.5f + radius)
	{
		Pos.x = GetPos().x + COLLISION_WIDTH * -0.5f + radius;
	}
	//右の判定
	else if (Pos.x > GetPos().x + COLLISION_WIDTH * 0.5f - radius)
	{
		Pos.x = GetPos().x + COLLISION_WIDTH * 0.5f - radius;
	}

	return Pos;
}

//============================
//フィールドの描画
//============================
void CField::Draw()
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
	pDevice->SetTexture(0, pTexture->GetAddress(pTexture->Regist(TEXTUREPATH.c_str())));

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVertex, 0, m_nPolygon);
}

//================================
//フィールドのクリエイト
//================================
CField* CField::Create(D3DXVECTOR3 pos)
{
	//ポインタ用の変数
	CField* pObjectX;

	//メモリの確保
	pObjectX = new CField;

	//パラメータの設定
	pObjectX->SetPos(pos);	//位置の設定

	//初期化
	pObjectX->Init();

	return pObjectX;
}

//============================
//フィールドの読み込み
//============================
void CField::Load()
{
	//ローカル変数宣言
	FILE* pFile;

	//ファイルを開く
	pFile = fopen(FILEPATH.c_str(), "rb");

	//ファイルに情報を書き出す
	if (pFile != NULL)
	{
		//ローカル変数
		LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ
		pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得

		//データの記録
		fread(&m_nVertex, sizeof(int), 1, pFile);	//頂点数
		fread(&m_nIndex, sizeof(int), 1, pFile);	//番号
		fread(&m_nPolygon, sizeof(int), 1, pFile);	//ポリゴン数

		//バーテックスバッファの生成
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

		//メッシュ用変数
		WORD* pIdx; //追加のポインタ
		VERTEX_3D* pVtx; //追加情報のポインタ

		//インデックスバッファをロック
		m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

		//頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		fread(pVtx, sizeof(VERTEX_3D), m_nVertex, pFile);	//頂点バッファ
		fread(pIdx, sizeof(WORD), m_nIndex, pFile);	//インデックスバッファ

		//頂点バッファをアンロックする
		m_pVtxBuff->Unlock();

		//インデックスバッファのアンロック
		m_pIdxBuff->Unlock();

		//ファイルを閉じる
		fclose(pFile);
	}
}