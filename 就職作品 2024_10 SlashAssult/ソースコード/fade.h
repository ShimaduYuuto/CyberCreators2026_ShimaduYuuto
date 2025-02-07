//================================
//
//fade.cppに必要な宣言[fade.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _FADE_H_ //このマクロ定義がされていなかったら
#define _FADE_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "scene.h"

//フェードクラス
class CFade
{
public:

	//定数
	static const int FADE_TIME = 90;	//フェードにかかるフレーム

	//フェードの列挙型
	typedef enum
	{
		FADE_NONE = 0,	//なし
		FADE_OUT,		//フェードアウト
		FADE_IN,		//フェードイン
		FADE_MAX,		//列挙の最大
	}FADE;

	//メンバ関数
	CFade();									//コンストラクタ
	~CFade();									//デストラクタ
	HRESULT Init();								//初期化
	void Uninit();								//終了
	void Update();								//更新
	void Draw();								//描画
	static void SetFade(CScene::MODE mode);		//シーンの設定と切り替え

	//フェードが終わっているかを返す
	bool GetEnd() { return m_bEndFade; }		//フェードが終わっているか

private:

	//メンバ関数
	void SetAlpha(float falpha);				//α値を設定

	//メンバ変数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファ
	float m_fAlpha;								//α値
	static FADE m_FadeState;					//フェードの状態
	static bool m_bEndFade;						//フェードが終わったか
	static CScene::MODE m_Mode;					//現在のモード
};

#endif