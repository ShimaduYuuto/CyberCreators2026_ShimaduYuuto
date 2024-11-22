//================================
//
//result.cppに必要な宣言[result.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _RESULT_H_ //このマクロ定義がされていなかったら
#define _RESULT_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "scene.h"

//リザルトクラス
class CResult : public CScene
{
public:

	//メンバ関数
	CResult();						//コンストラクタ
	~CResult() override;			//デストラクタ
	HRESULT Init() override;		//初期化
	void Uninit() override;			//終了
	void Update() override;			//更新
	void Draw() override;			//描画

private:
};

#endif