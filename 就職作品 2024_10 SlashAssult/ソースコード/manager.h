//================================
//
//manager.cppに必要な宣言[manager.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _MANAGER_H_ //このマクロ定義がされていなかったら
#define _MANAGER_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "xfile.h"
#include "fade.h"
#include "scene.h"
#include "time.h"
#include "debugproc.h"

//マネージャークラス
class CManager
{

private:

	//メンバ関数
	CManager();								//コンストラクタ

public:

	//メンバ関数
	~CManager();							//デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);		//初期化
	void Uninit();							//終了処理
	void Update();							//更新処理
	void Draw();							//描画処理

	//インスタンスの生成
	static CManager* GetInstance()
	{
		static CManager instance;	//静的インスタンス
		return &instance;
	}

	CRenderer* GetRenderer();		//レンダラーの取得
	CSound* GetSound();				//シーンの取得
	CInputKeyboard* GetKeyboard();	//キーボードの取得
	CInputJoypad* GetJoypad();		//ジョイパッドの取得
	CInputMouse* GetMouse();		//マウスの取得
	CCamera* GetCamera();			//ビュー情報の取得
	CLight* GetLight();				//ライトの情報
	CTexture* GetTexture();			//テクスチャの情報
	CXfile* GetXfile();				//Xファイルの取得
	CFade* GetFade();				//フェードの取得
	CScene* GetScene();				//シーンの取得
	void SetScene(CScene::MODE mode);//シーンの設定

	//FPSの設定と取得
	void SetFPS(int fps);			//設定

private:

	//メンバ変数
	CRenderer* m_pRenderer;				//レンダラーのインスタンス
	CInputKeyboard* m_pKeyboard;		//キーボードのインスタンス
	CInputJoypad* m_pJoypad;			//ジョイパッドのインスタンス
	CInputMouse* m_pMouse;				//マウスのインスタンス
	CSound* m_pSound;					//サウンドのインスタンス
	CCamera* m_pCamera;					//ビュー情報のインスタンス
	CLight* m_pLight;					//ライト情報のインスタンス
	CTexture* m_pTexture;				//テクスチャのインスタンス
	CXfile* m_pXfile;					//Xファイルのインスタンス
	CFade* m_pFade;						//フェードのインスタンス
	CScene* m_pScene;					//シーンのインスタンス
};

#endif