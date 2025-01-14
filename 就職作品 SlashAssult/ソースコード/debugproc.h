//==========================================================
//
//デバッグ表示処理 [debugproc.h]
//Author:Yuuto Shimadu
//
//==========================================================
#ifndef _DEBUGPROC_H_		//このマクロが定義されていない場合
#define _DEBUGPROC_H_

//ヘッダーのインクルード
#include "main.h"
#include "scene.h"

//ライトクラス
class CDebugProc
{
public:

	//スイッチ列挙型の定義
	typedef enum
	{
		DEBUGTYPE_OFF = 0,	//対象機能が動作していない状態
		DEBUGTYPE_ON,		//対象機能が動作している状態
		DEBUGTYPE_MAX
	}DEBUGTYPE;

	//定数
	static const int MAX_FLOATNUM = 2;	//表示する小数点の桁
	static const std::string m_apOnOff[DEBUGTYPE_MAX];		//デバッグonoff表示メッセージ
	static const std::string m_apMode[CScene::MODE_MAX];	//シーンの表示

	//メンバ関数
	CDebugProc();			//コンストラクタ
	~CDebugProc();			//デストラクタ
	HRESULT Init();			//初期化
	void Uninit();			//終了
	void Update();			//更新
	void Draw();			//描画
	void Print(const char* fmt, ...);	//表示
	const TCHAR* String(const TCHAR* format, ...);	//表示

private:

	//メンバ関数
	void SetManual();		//説明

	//メンバ変数
	LPD3DXFONT m_pFont = NULL;	//フォントへのポインタ
	std::string m_aStrDebug;	//デバッグ表示用の文字列
	bool m_bDispDebug = false;	//デバッグ表示のON/OFF
};

#endif