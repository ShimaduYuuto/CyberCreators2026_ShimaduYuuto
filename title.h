//================================
//
//title.cppに必要な宣言[title.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _TITLE_H_ //このマクロ定義がされていなかったら
#define _TITLE_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "scene.h"

//タイトルクラス
class CTitle : public CScene
{
public:

	//メンバ関数
	CTitle();						//コンストラクタ
	~CTitle() override;				//デストラクタ
	HRESULT Init() override;		//初期化
	void Uninit() override;			//終了
	void Update() override;			//更新
	void Draw() override;			//描画

private:

};

#endif