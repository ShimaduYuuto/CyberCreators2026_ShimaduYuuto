//================================
//
//tree.cppに必要な宣言[tree.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _TREE_H_ //このマクロ定義がされていなかったら
#define _TREE_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "model.h"

//ツリークラス
class CTree : public CModel
{
public:

	//テクスチャパス
	static const std::string MODEL_PATH;

	//描画
	void Draw() override;
};

#endif