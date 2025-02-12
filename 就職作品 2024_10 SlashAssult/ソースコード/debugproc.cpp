//======================================
//
//	デバッグプロックの処理[Debugproc.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "Debugproc.h"
#include "manager.h"
#include <tchar.h>

//定数の初期化
const std::string CDebugProc::m_apOnOff[DEBUGTYPE_MAX] = 
{//デバッグonoff表示メッセージ
	"OFF",
	"ON",
};		

const std::string CDebugProc::m_apMode[CScene::MODE_MAX] = 
{//現在のシーンの表示
	"タイトル",
	"ゲーム",
	"リザルト",
};	

//============================
//デバッグプロックのコンストラクタ
//============================
CDebugProc::CDebugProc()
{
	
}

//============================
//デバッグプロックのデストラクタ
//============================
CDebugProc::~CDebugProc()
{

}

//============================
//デバッグプロックの初期化
//============================
HRESULT CDebugProc::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//デバイスへのポインタを取得

	//デバッグ表示用フォントの生成
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

	//デバッグ表示情報のクリア
	memset(&m_aStrDebug[0], NULL, sizeof(m_aStrDebug));

	//初期表示設定
//#if _DEBUG
//	m_bDispDebug = true;
//#else NDEBUG
//	g_bDispDebug = false;
//#endif

	return S_OK;
}

//============================
//デバッグプロックの終了処理
//============================
void CDebugProc::Uninit()
{
	//デバッグ表示用フォントの廃棄
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
}

//============================
//デバッグプロックの更新処理
//============================
void CDebugProc::Update()
{
	//操作説明設定
	SetManual();

	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_F1))
	{//F1キーが押されたとき
		m_bDispDebug = m_bDispDebug ? false : true;
	}
}

//============================
//デバッグプロックの描画処理
//============================
void CDebugProc::Draw()
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	if (m_bDispDebug == true)
	{//デバックモードがオンの時
	 //テキストの描画
		m_pFont->DrawText(NULL, &m_aStrDebug[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	}

	//デバッグ表示情報のクリア
	//memset(&m_aStrDebug[0], NULL, sizeof(m_aStrDebug));
	m_aStrDebug.clear();
}

//==========================================================
//デバッグ表示の設定処理
//==========================================================
void CDebugProc::Print(const char *fmt, ...)
{
	// ローカル変数宣言
	va_list args;
	va_start(args, fmt);

	// 出力用バッファを確保
	char buffer[1024];
	vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);

	// デバッグ文字列に追加
	m_aStrDebug += buffer;
}

//==========================================================
//デバッグ表示の設定処理
//==========================================================
const TCHAR* CDebugProc::String(const TCHAR* format, ...)
{
	static TCHAR strBuffer_g[1024];
	va_list args;
	va_start(args, format);

#if _DEBUG
	int len = _vsctprintf(format, args);
	if (len >= static_cast<int>(std::size(strBuffer_g))) {
		_ASSERT(0); // サイズオーバーチェック
	}
#endif

	_vstprintf(strBuffer_g, format, args);
	va_end(args);

	return strBuffer_g;
}

//==========================================================
//表示するテキスト設定
//==========================================================
void CDebugProc::SetManual(void)
{
	
}