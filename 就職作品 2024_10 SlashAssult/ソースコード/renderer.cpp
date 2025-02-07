//======================================
//
//	レンダラーの処理[renderer.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "renderer.h"
#include "object.h"
#include "manager.h"

//============================
//レンダラーのコンストラクタ
//============================
CRenderer::CRenderer()
{
	//ポインタの初期化
	m_pD3D = nullptr;
	m_pD3DDevice = nullptr;
}

//============================
//レンダラーのデストラクタ
//============================
CRenderer::~CRenderer()
{

}

//============================
//レンダラーの初期化
//============================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;    //ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp; //プレゼンテーションパラメータ

	//Direct3Dオブジェクトの生成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}
	//現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));			//パラメータのゼロクリア
	d3dpp.BackBufferWidth = SCREEN_WIDTH;		//ゲーム画面サイズ（幅）
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;		//ゲーム画面のサイズ（高さ）
	d3dpp.BackBufferFormat = d3ddm.Format;		//バックバッファの形式
	d3dpp.BackBufferCount = 1;					//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//ダブルバッファの切り替え
	d3dpp.EnableAutoDepthStencil = TRUE;		//デプスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	//デプスのバッファとして16bitを使う
	d3dpp.Windowed = bWindow;					//ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	//リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//インターバル

	//Direct3Dデバイスの作成（描画処理と頂点処理をハードウェアで行う）
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		//Direct3Dデバイスの生成（描画処理はハードウェア、頂点処理はCPUで行う
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			//Direct3Dデバイスの作成（描画処理と頂点処理をCPUで行う）
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//サンプラーステートの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//テクスチャステージステート
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	return S_OK;
}

//============================
//レンダラーの終了処理
//============================
void CRenderer::Uninit()
{
	//Direct3Dデバイスの破棄
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}

	//Direct3Dオブジェクトの破棄
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
}

//============================
//レンダラーの更新処理
//============================
void CRenderer::Update()
{
	//オブジェクトの更新
	CObject::UpdateAll();

	//フェードの更新
	CManager::GetInstance()->GetFade()->Update();
}

//============================
//レンダラーの描画処理
//============================
void CRenderer::Draw()
{
	//画面クリア(バックバッファ&Zバッファのクリア)
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(100, 100, 100, 100), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		//デバッグプロックの描画
		//CManager::GetInstance()->GetDebugProc()->Draw();

		//カメラの設定
		CManager::GetInstance()->GetCamera()->SetCamera();

		//描画開始が成功した場合
		CObject::DrawAll();

		//シーンの描画
		CManager::GetInstance()->GetScene()->Draw();

		//フェードの描画
		CManager::GetInstance()->GetFade()->Draw();

		//描画終了
		m_pD3DDevice->EndScene();
	}
	//バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//============================
//デバイスの取得
//============================
LPDIRECT3DDEVICE9 CRenderer::GetDevice()
{
	return m_pD3DDevice;
}