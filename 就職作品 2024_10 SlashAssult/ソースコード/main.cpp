//======================================
//
//	メイン処理[main.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "main.h"
#include "manager.h"

//マクロ定義
#define WINDOW_NAME "SlashAssault" //ウィンドウの名前（キャプションに表示）
#define FPS (1000) //FPSの基準
#define FPS_NUMBER (60) //FPSの基準

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND nWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	//ウィンドウプロシージャ
//緊急
void ToggleFullscreen(HWND hWnd);// ウィンドウをフルスクリーンにする

bool g_isFullscreen = false;// ウィンドウを切り替えるためのフラグ
RECT g_windowRect;// ウィンドウを切り替えるための変数

//===================================
//メイン関数
//===================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpcmpLine, _In_ int nCmdShow)
{
	//カーソルの非表示
	ShowCursor(FALSE);

	CManager* pManager = nullptr;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX), //WNDCLASSEXのメモリのサイズ
		CS_CLASSDC,         //ウィンドウのスタイル
		WindowProc,         //ウィンドウプロシージャ
		0,                  //0にする
		0,                  //0にする
		hInstance,          //インスタンスハンドル
		LoadIcon(NULL, IDI_APPLICATION), //タスクバーのアイコン
		LoadCursor(NULL, IDC_ARROW),     //マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),      //クライアント領域の背景の色
		NULL,                            //メニューバー
		CLASS_NAME,                      //ウィンドウクラスの名前
		LoadIcon(NULL, IDI_APPLICATION)  //ファイルのアイコン
	};

	HWND hWnd;				//ウィンドウハンドル(識別子)
	MSG msg;				//メッセージを格納する変数
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }; //画面サイズ構造体

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウを生成
	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);

	//分解能を設定
	timeBeginPeriod(1);

	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//生成と初期化
	pManager = CManager::GetInstance();		//レンダラー生成
	pManager->Init(hInstance, hWnd, TRUE);	//初期化

	//ランダムで進行方向を決める
	srand((unsigned int)time(NULL));

	DWORD dwCurrentTime = 0;	//現在時刻
	DWORD dwExecLastTime = timeGetTime();	//最後に処理した時刻
	DWORD dwFrameCount = 0;
	DWORD dwFPSLastTime = timeGetTime();

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windowsの処理
			if (msg.message == WM_QUIT)
			{//WM_QUIT メッセージを受け取ったらメッセージループを抜ける
				break;
			}
			else
			{//メッセージの設定
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

		}
		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime(); //現在時刻を取得

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過
				//FPSを観測
				int nFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				pManager->SetFPS(nFPS);
				dwFPSLastTime = dwCurrentTime;	//FPSを観測した時刻を保存
				dwFrameCount = 0;				//フレームカウントをクリア
			}
			if ((dwCurrentTime - dwExecLastTime) >= (FPS / FPS_NUMBER))
			{//60分の1秒経過
				dwExecLastTime = dwCurrentTime;//処理開始の時刻を保存
				//更新処理
				pManager->Update();

				//描画処理
				pManager->Draw();

				dwFrameCount++;//フレームカウントを加算
			}

		}

	}

	//終了処理
	pManager->Uninit();
	
	//分解能を戻す
	timeEndPeriod(1);

	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;

}

//==========================
//ウインドウプロシージャ
//==========================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;//返り値を格納

	switch (uMsg)
	{
	case WM_DESTROY:
		//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:	//キー押下のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE: //[ESCキーが押された
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);
			if (nID == IDYES)
			{
				//ウィンドウを破棄する(WM_DESTROYメッセージを送る
				DestroyWindow(hWnd);
			}
			break;
		case VK_F11:
			ToggleFullscreen(hWnd);
			break;
		}
		break;

	case WM_CLOSE: //閉じるボタン押下メッセージ
		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);
		if (nID == IDYES)
		{
			//ウィンドウを破棄する
			DestroyWindow(hWnd);
		}
		else
		{
			return 0; //0を返さないと終了してしまう
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//************************************************
// ウィンドウをフルスクリーンに変える処理
//************************************************
void ToggleFullscreen(HWND hWnd)
{
	// 現在のウィンドウスタイルを取得
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (g_isFullscreen)
	{
		// ウィンドウモードに切り替え
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, g_windowRect.left, g_windowRect.top,
			g_windowRect.right - g_windowRect.left, g_windowRect.bottom - g_windowRect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		// フルスクリーンモードに切り替え
		GetWindowRect(hWnd, &g_windowRect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}

	g_isFullscreen = !g_isFullscreen;
}