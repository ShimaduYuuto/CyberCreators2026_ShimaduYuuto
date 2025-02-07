//======================================
//
//	マネージャーの処理[manager.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "manager.h"
#include "object.h"
#include "renderer.h"

//============================
//マネージャーのコンストラクタ
//============================
CManager::CManager() :
	m_pCamera(nullptr),
	m_pFade(nullptr),
	m_pJoypad(nullptr),
	m_pKeyboard(nullptr),
	m_pLight(nullptr),
	m_pMouse(nullptr),
	m_pRenderer(nullptr),
	m_pScene(nullptr),
	m_pSound(nullptr),
	m_pTexture(nullptr),
	m_pXfile(nullptr)
{
	
}

//============================
//マネージャーのデストラクタ
//============================
CManager::~CManager()
{

}

//============================
//マネージャーの初期化処理
//============================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//レンダラーの生成
	m_pRenderer = new CRenderer();		//生成
	m_pRenderer->Init(hWnd, bWindow);	//初期化

	//キーボードデバイスの生成
	m_pKeyboard = new CInputKeyboard();				//生成
	if (FAILED(m_pKeyboard->Init(hInstance, hWnd)))	//初期化
	{
		return E_FAIL;
	}

	//マウスデバイスの生成
	m_pMouse = new CInputMouse();					//生成
	if (FAILED(m_pMouse->Init(hInstance, hWnd)))	//初期化
	{
		return E_FAIL;
	}

	//ジョイパッドの生成
	m_pJoypad = new CInputJoypad();
	if (FAILED(m_pJoypad->Init()))
	{
		return E_FAIL;
	}

	//サウンドの生成
	m_pSound = new CSound();
	m_pSound->Init(hWnd);

	//カメラの生成
	m_pCamera = new CCamera();	//メモリ確保
	m_pCamera->Init();			//初期化

	//ライトの生成
	m_pLight = new CLight();	//メモリ確保
	m_pLight->Init();			//初期化

	//フェードの生成
	m_pFade = new CFade();		//メモリ確保
	m_pFade->Init();			//初期設定

	//テクスチャ管理クラスの生成
	m_pTexture = new CTexture();	//メモリ確保

	//Xファイルの管理
	m_pXfile = new CXfile();		//メモリの確保

	return S_OK;
}

//============================
//マネージャーの終了処理
//============================
void CManager::Uninit()
{
	//フェードのインスタンスを使用中なら
	if (m_pFade != nullptr)
	{
		//終了処理後に開放
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = nullptr;
	}

	//全オブジェクトの開放
	CObject::ReleaseAll();

	//シーンのインスタンスを使用中なら
	if (m_pScene != nullptr)
	{
		//終了処理後に開放
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	//テクスチャのインスタンスを使用中なら
	if (m_pTexture != nullptr)
	{
		//終了処理後に開放
		m_pTexture->Unload();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	//Xファイルのインスタンスを使用中なら
	if (m_pXfile != nullptr)
	{
		//終了処理後に開放
		m_pXfile->Unload();
		delete m_pXfile;
		m_pXfile = nullptr;
	}

	//レンダラーのインスタンスを使用中なら
	if (m_pRenderer != nullptr)
	{
		//終了処理後に開放
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	//キーボードのインスタンスを使用中なら
	if (m_pKeyboard != nullptr)
	{
		//終了処理後に開放
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}

	//マウスのインスタンスを使用中なら
	if (m_pMouse != nullptr)
	{
		//終了処理後に開放
		m_pMouse->Uninit();
		delete m_pMouse;
		m_pMouse = nullptr;
	}

	//ジョイパッドのインスタンスを使用中なら
	if (m_pJoypad != nullptr)
	{
		//終了処理後に開放
		m_pJoypad->Uninit();
		delete m_pJoypad;
		m_pJoypad = nullptr;
	}

	//サウンドのインスタンスを使用中なら
	if (m_pSound != nullptr)
	{
		//終了処理後に開放
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	//カメラのインスタンスを使用中なら
	if (m_pCamera != nullptr)
	{
		//終了処理後に開放
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	//ライトのインスタンスを使用中なら
	if (m_pLight != nullptr)
	{
		//終了処理後に開放
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}
}

//============================
//マネージャーの更新処理
//============================
void CManager::Update()
{
	//レンダラーの更新処理
	m_pRenderer->Update();

	//シーンの更新処理
	m_pScene->Update();

	//キーボードの更新処理
	m_pKeyboard->Update();

	//ジョイパッドの更新処理
	m_pJoypad->Update();

	//マウスの更新処理
	m_pMouse->Update();

	//カメラの更新処理
	m_pCamera->Update();

	//フェードの更新処理
	m_pFade->Update();
}

//============================
//マネージャーの描画処理
//============================
void CManager::Draw()
{
	//レンダラーの描画処理
	m_pRenderer->Draw();
}

//============================
//レンダラーの取得
//============================
CRenderer* CManager::GetRenderer()
{
	return m_pRenderer;
}

//============================
//サウンドの取得
//============================
CSound* CManager::GetSound()
{
	return m_pSound;
}

//============================
//キーボードの取得
//============================
CInputKeyboard* CManager::GetKeyboard()
{
	return m_pKeyboard;
}

//============================
//ジョイパッドの取得
//============================
CInputJoypad* CManager::GetJoypad()
{
	return m_pJoypad;
}

//============================
//ジョイパッドの取得
//============================
CInputMouse* CManager::GetMouse()
{
	return m_pMouse;
}

//============================
//カメラの取得
//============================
CCamera* CManager::GetCamera()
{
	//ビュー情報を返す
	return m_pCamera;
}

//============================
//カメラの切り替え
//============================
void CManager::ChangeCamera(CCamera* camera)
{
	SafeDelete(m_pCamera);	//削除
	m_pCamera = camera;
	m_pCamera->Init();
}

//============================
//ライトの取得
//============================
CLight* CManager::GetLight()
{
	//ライトの情報を返す
	return m_pLight;
}

//============================
//テクスチャの取得
//============================
CTexture* CManager::GetTexture()
{
	//テクスチャの情報を返す
	return m_pTexture;
}

//============================
//Xファイルの取得
//============================
CXfile* CManager::GetXfile()
{
	//Xファイルの情報を返す
	return m_pXfile;
}

//============================
//フェードの取得
//============================
CFade* CManager::GetFade()
{
	//フェードの情報を返す
	return m_pFade;
}

//============================
//シーンの取得
//============================
CScene* CManager::GetScene()
{
	//シーンの情報を返す
	return m_pScene;
}

//============================
//シーンの設定
//============================
void CManager::SetScene(CScene::MODE mode)
{

	//現在のシーンの終了処理
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	//次のシーン生成
	m_pScene = CScene::Create(mode);
}

//============================
//デバッグプロックの設定
//============================
void CManager::SetFPS(int fps)
{
	//m_nFPSCount = fps;
}