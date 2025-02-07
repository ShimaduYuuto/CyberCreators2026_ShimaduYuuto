//================================
//
//scene.cppに必要な宣言[scene.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _SCENE_H_ //このマクロ定義がされていなかったら
#define _SCENE_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"

//シーンクラス
class CScene
{
public:

	//画面の種類
	typedef enum
	{
		MODE_TITLE = 0,	//タイトル
		MODE_GAME,		//ゲーム
		MODE_RESULT,	//リザルト
		MODE_MAX,		//列挙の最大
	}MODE;

	//メンバ関数
	CScene();								//コンストラクタ
	virtual ~CScene();						//デストラクタ
	virtual HRESULT Init();					//初期化
	virtual void Uninit();					//終了
	virtual void Update();					//更新
	virtual void Draw();					//描画
	static CScene* Create(MODE mode);		//生成
	MODE GetMode() { return m_Mode; }		//モードの取得

	//各シーンのモデルとテクスチャの読み込み
	virtual void Load();	//読み込み
	
private:
	//メンバ変数
	static MODE m_Mode;	//現在のモード
};

#endif