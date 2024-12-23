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
const std::string CField::FILEPATH = "data\\MODEL\\Block001.x";		//テクスチャパス
const D3DXVECTOR3 CField::BLOCK = { 50.0f, 0, 50.0f };				//ブロック数
const D3DXVECTOR3 CField::SIZE = { 10000.0f, -2.0f, 10000.0f };		//サイズ

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
	//ローカル変数
	//LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスを取得
	//pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得

	//フィールド情報の読み込み
	Load();

	//pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (m_nVertex),
	//	D3DUSAGE_WRITEONLY,
	//	FVF_VERTEX_3D,
	//	D3DPOOL_MANAGED,
	//	&m_pVtxBuff,
	//	NULL);

	////インデックスバッファの生成
	//pDevice->CreateIndexBuffer(sizeof(WORD) * m_nIndex,
	//	D3DUSAGE_WRITEONLY,
	//	D3DFMT_INDEX16,
	//	D3DPOOL_MANAGED,
	//	&m_pIdxBuff,
	//	NULL);

	VERTEX_3D* pVtx; //追加情報のポインタ

	//インデックスバッファをロック
	WORD* pIdx; //追加のポインタ
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//int nX = 0;
	//int nZ = 0;

	//頂点の数だけ回す
	//for (int nCount = 0; nCount < m_nVertex; nCount++)
	//{
	//	//位置の設定
	//	pVtx[nCount].pos = D3DXVECTOR3(SIZE.x * (nX / (float)BLOCK.x) - (SIZE.x * 0.5f), 0.0f, -SIZE.z * (nZ / (float)BLOCK.z) + (SIZE.z * 0.5f));

	//	//テクスチャの読み込み
	//	pVtx[nCount].tex = D3DXVECTOR2(1.0f * (nX / (float)BLOCK.x), 1.0f * (nZ / (float)BLOCK.z));
	//	pVtx[nCount].tex = D3DXVECTOR2(nX, nZ);

	//	nX++;

	//	//Zを進める
	//	if (nX == BLOCK.x + 1)
	//	{
	//		nX = 0;
	//		nZ++;
	//	}

	//	//法線ベクトルの設定
	//	pVtx[nCount].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//	//頂点カラーの設定
	//	pVtx[nCount].col = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	//}

	////インデックスの計算用の変数
	//nX = 0;
	//nZ = 0;
	//int nX2 = 0;

	////インデックスの計算
	//for (int nCount = 0; nCount < m_nIndex; nCount++)
	//{
	//	//縮退ポリゴンの場合とそれ以外
	//	if (nCount == ((int)(BLOCK.x + 1) * 2 + 2) * (nZ + 1) - 2)
	//	{
	//		pIdx[nCount] = pIdx[nCount - 1];
	//	}
	//	else if (nCount == ((int)(BLOCK.x + 1) * 2 + 2) * (nZ + 1) - 1)
	//	{
	//		pIdx[nCount] = pIdx[nCount - 1] + (WORD)BLOCK.x + 2;
	//		nZ++;
	//	}
	//	else
	//	{
	//		if (nCount % 2 == 0)//偶数の場合
	//		{
	//			pIdx[nCount] = (WORD)(BLOCK.x + 1 + nX);
	//			nX++;
	//		}
	//		else//奇数の場合
	//		{
	//			pIdx[nCount] = (WORD)nX2;
	//			nX2++;
	//		}
	//	}
	//}

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

		//法線ベクトルを格納する変数
		D3DXVECTOR3 SurfaceNorVec; //面法線のベクトル
		D3DXVECTOR3 vecNormal; //正規化したベクトル
		D3DXVECTOR3 vector1; //1つ目のベクトルの保管用
		D3DXVECTOR3 vector2; //2つ目のベクトルの保管用
		D3DXVECTOR3 vector3; //3つ目のベクトルの保管用
		D3DXVECTOR3 playervector1; //1つ目のベクトルの保管用
		D3DXVECTOR3 playervector2; //2つ目のベクトルの保管用
		D3DXVECTOR3 playervector3; //3つ目のベクトルの保管用 
		D3DXVECTOR3 Vec1; //1つ目のベクトルの保管用
		D3DXVECTOR3 Vec2; //2つ目のベクトルの保管用
		D3DXVECTOR3 Vec3; //3つ目のベクトルの保管用 

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
			//ポリゴンのベクトルを計算
			vector1 = vtx2->pos - vtx0->pos;
			vector2 = vtx1->pos - vtx2->pos;
			vector3 = vtx0->pos - vtx1->pos;

			//プレイヤーのベクトルを計算
			playervector1 = pos - vtx0->pos;
			playervector2 = pos - vtx2->pos;
			playervector3 = pos - vtx1->pos;
		}
		else //奇数
		{
			//ポリゴンのベクトルを計算
			vector1 = vtx1->pos - vtx0->pos;
			vector2 = vtx2->pos - vtx1->pos;
			vector3 = vtx0->pos - vtx2->pos;

			//プレイヤーのベクトルを計算
			playervector1 = pos - vtx0->pos;
			playervector2 = pos - vtx1->pos;
			playervector3 = pos - vtx2->pos;
		}

		//ベクトルの計算
		D3DXVec3Cross(&Vec1, &playervector1, &vector1);
		D3DXVec3Cross(&Vec2, &playervector2, &vector2);
		D3DXVec3Cross(&Vec3, &playervector3, &vector3);

		//ベクトルの正規化
		D3DXVec3Normalize(&Vec1, &Vec1);
		D3DXVec3Normalize(&Vec2, &Vec2);
		D3DXVec3Normalize(&Vec3, &Vec3);

		//ポリゴンの中にいたら色を変化
		if (Vec1.y >= 0.0f && Vec2.y >= 0.0f && Vec3.y >= 0.0f)
		{
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

	//高さを返す
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

		//法線ベクトルを格納する変数
		D3DXVECTOR3 SurfaceNorVec; //面法線のベクトル
		D3DXVECTOR3 vecNormal; //正規化したベクトル
		D3DXVECTOR3 vector1; //1つ目のベクトルの保管用
		D3DXVECTOR3 vector2; //2つ目のベクトルの保管用
		D3DXVECTOR3 vector3; //3つ目のベクトルの保管用
		D3DXVECTOR3 playervector1; //1つ目のベクトルの保管用
		D3DXVECTOR3 playervector2; //2つ目のベクトルの保管用
		D3DXVECTOR3 playervector3; //3つ目のベクトルの保管用 
		D3DXVECTOR3 Vec1; //1つ目のベクトルの保管用
		D3DXVECTOR3 Vec2; //2つ目のベクトルの保管用
		D3DXVECTOR3 Vec3; //3つ目のベクトルの保管用 

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
			//ポリゴンのベクトルを計算
			vector1 = vtx2->pos - vtx0->pos;
			vector2 = vtx1->pos - vtx2->pos;
			vector3 = vtx0->pos - vtx1->pos;

			//プレイヤーのベクトルを計算
			playervector1 = pos - vtx0->pos;
			playervector2 = pos - vtx2->pos;
			playervector3 = pos - vtx1->pos;
		}
		else //奇数
		{
			//ポリゴンのベクトルを計算
			vector1 = vtx1->pos - vtx0->pos;
			vector2 = vtx2->pos - vtx1->pos;
			vector3 = vtx0->pos - vtx2->pos;

			//プレイヤーのベクトルを計算
			playervector1 = pos - vtx0->pos;
			playervector2 = pos - vtx1->pos;
			playervector3 = pos - vtx2->pos;
		}

		//ベクトルの計算
		D3DXVec3Cross(&Vec1, &playervector1, &vector1);
		D3DXVec3Cross(&Vec2, &playervector2, &vector2);
		D3DXVec3Cross(&Vec3, &playervector3, &vector3);

		//ベクトルの正規化
		D3DXVec3Normalize(&Vec1, &Vec1);
		D3DXVec3Normalize(&Vec2, &Vec2);
		D3DXVec3Normalize(&Vec3, &Vec3);

		//ポリゴンの中にいたら色を変化
		if (Vec1.y >= 0.0f && Vec2.y >= 0.0f && Vec3.y >= 0.0f)
		{
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

	//高さを返す
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

		//法線ベクトルを格納する変数
		D3DXVECTOR3 SurfaceNorVec; //面法線のベクトル
		D3DXVECTOR3 vecNormal; //正規化したベクトル
		D3DXVECTOR3 vector1; //1つ目のベクトルの保管用
		D3DXVECTOR3 vector2; //2つ目のベクトルの保管用
		D3DXVECTOR3 vector3; //3つ目のベクトルの保管用
		D3DXVECTOR3 playervector1; //1つ目のベクトルの保管用
		D3DXVECTOR3 playervector2; //2つ目のベクトルの保管用
		D3DXVECTOR3 playervector3; //3つ目のベクトルの保管用 
		D3DXVECTOR3 Vec1; //1つ目のベクトルの保管用
		D3DXVECTOR3 Vec2; //2つ目のベクトルの保管用
		D3DXVECTOR3 Vec3; //3つ目のベクトルの保管用 

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
			//ポリゴンのベクトルを計算
			vector1 = vtx2->pos - vtx0->pos;
			vector2 = vtx1->pos - vtx2->pos;
			vector3 = vtx0->pos - vtx1->pos;

			//プレイヤーのベクトルを計算
			playervector1 = pos - vtx0->pos;
			playervector2 = pos - vtx2->pos;
			playervector3 = pos - vtx1->pos;
		}
		else //奇数
		{
			//ポリゴンのベクトルを計算
			vector1 = vtx1->pos - vtx0->pos;
			vector2 = vtx2->pos - vtx1->pos;
			vector3 = vtx0->pos - vtx2->pos;

			//プレイヤーのベクトルを計算
			playervector1 = pos - vtx0->pos;
			playervector2 = pos - vtx1->pos;
			playervector3 = pos - vtx2->pos;
		}

		//ベクトルの計算
		D3DXVec3Cross(&Vec1, &playervector1, &vector1);
		D3DXVec3Cross(&Vec2, &playervector2, &vector2);
		D3DXVec3Cross(&Vec3, &playervector3, &vector3);

		//ベクトルの正規化
		D3DXVec3Normalize(&Vec1, &Vec1);
		D3DXVec3Normalize(&Vec2, &Vec2);
		D3DXVec3Normalize(&Vec3, &Vec3);

		//ポリゴンの中にいたら色を変化
		if (Vec1.y >= 0.0f && Vec2.y >= 0.0f && Vec3.y >= 0.0f)
		{
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

	//高さを返す
	return pos;
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
D3DXVECTOR3 CField::WidthCollision(D3DXVECTOR3 pos)
{
	//返す用の位置
	D3DXVECTOR3 Pos = pos;

	//左の判定
	if (Pos.x < GetPos().x + COLLISION_WIDTH * -0.5f + 30.0f)
	{
		Pos.x = GetPos().x + COLLISION_WIDTH * -0.5f + 30.0f;
	}
	//右の判定
	else if (Pos.x > GetPos().x + COLLISION_WIDTH * 0.5f - 30.0f)
	{
		Pos.x = GetPos().x + COLLISION_WIDTH * 0.5f - 30.0f;
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
	pDevice->SetTexture(0, pTexture->GetAddress(pTexture->Regist("data\\TEXTURE\\FieldTexture000.png")));
	

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
	pFile = fopen("data\\FILE\\Field.bin", "rb");

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