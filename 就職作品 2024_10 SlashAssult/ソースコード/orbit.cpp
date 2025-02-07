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

//軌跡クラスの定数
const std::string COrbit::TEXTUREPATH = "data\\TEXTURE\\SmashMesh000.png";	//テクスチャ
const D3DXVECTOR3 COrbit::BLOCK = { NUM_ORBIT - 1, 1, 0 };					//ブロック数
const D3DXVECTOR3 COrbit::SIZE = { 100.0f, 100.0f, 0.0f };						//サイズ

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
		m_SaveVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
		m_SaveVtx[i].nor = { 0.0f, 0.0, -1.0f };

		float fTextureU = (i / 2) / (float)((NUM_VTX / 2) - 1);

		if ((i & 1) == 0) //偶数
		{
			m_SaveVtx[i].tex = { fTextureU , 0.0f };
		}
		else
		{
			m_SaveVtx[i].tex = { fTextureU , 1.0f };
		}
	}

	//初めての設定かの判定
	m_bFirstSet = false;

	//ゲームタグを設定
	SetTag(CObject::TAG_GAME);
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
	CObjectMesh::Init(static_cast<int>(BLOCK.x), static_cast<int>(BLOCK.y), SIZE.x, SIZE.y, CObjectMesh::MESHTYPE_WALL);

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
	m_SaveVtx[0].pos = { -100.0f, 50.0f, 0.0f };
	m_SaveVtx[1].pos = { -100.0f, 0.0f, 0.0f };
	m_SaveVtx[2].pos = { -50.0f, 50.0f, 0.0f };
	m_SaveVtx[3].pos = { -50.0f, 0.0f, 0.0f };
	m_SaveVtx[4].pos = { -0.0f, 50.0f, 0.0f };
	m_SaveVtx[5].pos = { -0.0f, 0.0f, 0.0f };
	m_SaveVtx[6].pos = { 50.0f, 50.0f, 0.0f };
	m_SaveVtx[7].pos = { 50.0f, 0.0f, 0.0f };
	m_SaveVtx[8].pos = { 100.0f, 50.0f, 0.0f };
	m_SaveVtx[9].pos = { 100.0f, 0.0f, 0.0f };
	m_SaveVtx[10].pos = { 150.0f, 50.0f, 0.0f };
	m_SaveVtx[11].pos = { 150.0f, 0.0f, 0.0f };
	
	//親クラスの頂点に反映
	for (int i = 0; i < 8; i++)
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
	//ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得

	//カリング方法を変更
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//Zの比較方法変更
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	//Zバッファに書き込まない
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//親クラスで描画
	CObjectMesh::Draw(TEXTUREPATH.c_str());

	//Zの比較方法変更
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//Zバッファに書き込む
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//カリング方法を変更
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
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

			//位置と色を反映
			CObjectMesh::SetVtxPos(i, m_SaveVtx[i].pos);
		}
	}
}