//======================================
//
//	フェードの処理[fade.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "fade.h"
#include "manager.h"

//静的メンバの初期化
CScene::MODE CFade::m_Mode = CScene::MODE_TITLE;	//モードの初期化
bool CFade::m_bEndFade = false;						//フェードをしていない判定
CFade::FADE CFade::m_FadeState = CFade::FADE_NONE;	//フェードの状態を初期化

//============================
//フェードのコンストラクタ
//============================
CFade::CFade() :
	m_fAlpha(1.0f)
{
	//メンバ変数の初期化
	m_pVtxBuff = nullptr;			//頂点ポインタの初期化
	m_Mode = CScene::MODE_TITLE;	//モードの初期化
	m_bEndFade = true;				//フェードをしていない判定
	m_FadeState = CFade::FADE_NONE;	//フェードの状態を初期化
}

//============================
//フェードのデストラクタ
//============================
CFade::~CFade()
{

}

//============================
//フェードの初期化
//============================
HRESULT CFade::Init()
{
	//メンバ変数の初期化
	m_fAlpha = 1.0f;

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
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = (float)SCREEN_WIDTH;
	pVtx[1].pos.y = 0.0f;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = 0.0f;
	pVtx[2].pos.y = (float)SCREEN_HEIGHT;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = (float)SCREEN_WIDTH;
	pVtx[3].pos.y = (float)SCREEN_HEIGHT;
	pVtx[3].pos.z = 0.0f;

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//最初のシーンの設定
	SetFade(m_Mode);

	return S_OK;
}

//============================
//フェードの終了処理
//============================
void CFade::Uninit()
{
	//使用していたら破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//============================
//フェードの更新処理
//============================
void CFade::Update()
{
	//フェードが終わっていなかったら
	if (!m_bEndFade)
	{
		//フェードの状態によって処理を変更
		switch (m_FadeState)
		{
		case FADE_NONE:	//何もなし
			break;

		case FADE_OUT:	//フェードアウト

			//透明度が最大じゃないなら
			if (m_fAlpha <= 1.0f)
			{
				//α値を増加
				m_fAlpha += 1.0f / (float)FADE_TIME;

				//α値の設定
				SetAlpha(m_fAlpha);

				//透明度が最大になったら
				if (m_fAlpha >= 1.0f)
				{
					//最大値に補正
					m_fAlpha = 1.0f;

					//シーンの設定
					CManager::GetInstance()->SetScene(m_Mode);
					CManager::GetInstance()->GetScene()->Init();

					//フェードインの処理に移る
					m_FadeState = FADE_IN;
					
				}
			}

			break;

		case FADE_IN:	//フェードイン

			//透明度が0.0fじゃないなら
			if (m_fAlpha >= 0.0f)
			{
				//α値を増加
				m_fAlpha -= 1.0f / (float)FADE_TIME;

				//α値の設定
				SetAlpha(m_fAlpha);

				//透明度が0.0f以下になったら
				if (m_fAlpha <= 0.0f)
				{
					//最小値に補正
					m_fAlpha = 0.0f;

					//フェードインの処理に移る
					m_FadeState = FADE_NONE;
					m_bEndFade = true;	//処理が終わった判定に
				}
			}
			break;
		}
	}
}

//============================
//α値の設定
//============================
void CFade::SetAlpha(float falpha)
{
	VERTEX_2D* pVtx; //追加情報のポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, falpha);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, falpha);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, falpha);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, falpha);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//============================
//フェードの描画処理
//============================
void CFade::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

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
}

//============================
//シーンの切り替え処理
//============================
void CFade::SetFade(CScene::MODE mode)
{
	//フェードのboolをfalseに
	m_bEndFade = false;
	m_FadeState = FADE_OUT;

	//モードを設定
	m_Mode = mode;
}