//======================================
//
//	軌跡の処理[orbit.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "orbit.h"
#include "manager.h"
#include "game.h"

//軌跡クラスの定数の初期化
const D3DXVECTOR3 COrbit::BLOCK = { NUM_ORBIT - 1, 1, 0 };			//ブロック数
const D3DXVECTOR3 COrbit::SIZE = { 0.0f, 0.0f, 0.0f };				//サイズ

//============================
//軌跡のコンストラクタ
//============================
COrbit::COrbit(int nPriority) : CObjectMesh(nPriority)
{
	//周回して初期化
	for (int i = 0; i < NUM_VTX; i++)
	{
		//頂点情報の初期化
		m_SaveVtx[i].pos = { 0.0f, 0.0f, 0.0f };
		m_SaveVtx[i].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.7f);
		m_SaveVtx[i].nor = { 0.0f, 0.0, -1.0f };

		if ((i & 1) == 0) //偶数
		{
			m_SaveVtx[i].tex = { 0.0f, 0.0f };
		}
		else
		{
			m_SaveVtx[i].tex = { 0.0f, 1.0f };
		}
	}

	//初めての設定かの判定
	m_bFirstSet = false;
}

//============================
//軌跡のデストラクタ
//============================
COrbit::~COrbit()
{

}

//============================
//軌跡の初期化
//============================
HRESULT COrbit::Init()
{
	//初期化
	CObjectMesh::Init(BLOCK.x, BLOCK.y, SIZE.x, SIZE.y, CObjectMesh::MESHTYPE_WALL);
	return S_OK;
}

//============================
//軌跡の終了処理
//============================
void COrbit::Uninit()
{
	//終了処理
	CObjectMesh::Uninit();
}

//============================
//軌跡の更新
//============================
void COrbit::Update()
{
	//親クラスの頂点に反映
	for (int i = 0; i < NUM_VTX; i++)
	{
		//位置と色を反映
		CObjectMesh::SetVtxPos(i, m_SaveVtx[i].pos);
		CObjectMesh::SetVtxColor(i, m_SaveVtx[i].col);
	}
}

//============================
//軌跡の描画
//============================
void COrbit::Draw()
{
	//親クラスで描画
	CObjectMesh::Draw("data\\TEXTURE\\SmashMesh000.png");
}

//================================
//軌跡のクリエイト
//================================
COrbit* COrbit::Create()
{
	//ポインタ用の変数
	COrbit* pOrbit;

	//メモリの確保
	pOrbit = new COrbit;

	//初期化
	pOrbit->Init();

	//パラメータの設定
	pOrbit->SetPos({ 0.0f, 0.0f, 0.0f });	//位置の設定

	//周回して初期化
	for (int i = 0; i < NUM_VTX; i++)
	{
		pOrbit->SetVtxTex(i, pOrbit->m_SaveVtx[i].tex);
	}

	//ポインタを返す
	return pOrbit;
}

//================================
//軌跡の位置設定
//================================
void COrbit::SetOrbit(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1)
{
	//古い頂点を更新
	for (int i = NUM_VTX - 1; i > 1; i--)
	{
		//先頭以外の頂点の情報を上書き
		m_SaveVtx[i].pos = m_SaveVtx[i - 2].pos;
	}

	//先頭の頂点の位置更新
	m_SaveVtx[1].pos = pos1;	//オフセット分移動した位置を代入
	m_SaveVtx[0].pos = pos0;	//軌跡を出す親モデルの位置を代入

	//初めて設定するなら
	if (!m_bFirstSet)
	{
		//設定済み
		m_bFirstSet = true;

		//古い頂点を更新
		for (int i = NUM_VTX - 1; i > 1; i--)
		{
			//頂点の上書き
			if ((i & 1) == 0) //偶数
			{
				m_SaveVtx[i].pos = pos0;
			}
			else //奇数
			{
				m_SaveVtx[i].pos = pos1;
			}
		}
	}
}