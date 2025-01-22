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
	CCamera* GetCamera();			//カメラの取得
	void ChangeCamera(CCamera* camera);	//カメラの切り替え
	CLight* GetLight();				//ライトの情報
	CTexture* GetTexture();			//テクスチャの情報
	CXfile* GetXfile();				//Xファイルの取得
	CFade* GetFade();				//フェードの取得
	CScene* GetScene();				//シーンの取得
	void SetScene(CScene::MODE mode);//シーンの設定

	template<typename T>
	constexpr T GetRundom(T min, T max)
	{
		// メルセンヌ・ツイスター法による擬似乱数生成器を、
		// ハードウェア乱数をシードにして初期化
		std::random_device seed_gen;
		std::mt19937 engine(seed_gen());

		std::uniform_real_distribution<float> Rundom(min, max);
		T Value = Rundom(engine);

		return Value;
	}

	//FPSの設定と取得
	void SetFPS(int fps);			//設定

private:

	//メンバ変数
	CRenderer* m_pRenderer;				//レンダラー
	CInputKeyboard* m_pKeyboard;		//キーボード
	CInputJoypad* m_pJoypad;			//ジョイパッド
	CInputMouse* m_pMouse;				//マウス
	CSound* m_pSound;					//サウンド
	CCamera* m_pCamera;					//カメラ
	CLight* m_pLight;					//ライト
	CTexture* m_pTexture;				//テクスチャ
	CXfile* m_pXfile;					//Xファイル
	CFade* m_pFade;						//フェード
	CScene* m_pScene;					//シーン
};

#endif