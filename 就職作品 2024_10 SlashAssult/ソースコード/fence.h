//================================
//
//fence.cppに必要な宣言[fence.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _FENCE_H_ //このマクロ定義がされていなかったら
#define _FENCE_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "model.h"

//フェンスクラス
class CFence : public CModel
{
public:

	//テクスチャパス
	static const std::string MODEL_PATH;

	//描画
	void Draw() override;
};

#endif