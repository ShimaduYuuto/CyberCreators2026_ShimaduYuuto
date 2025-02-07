//================================
//
//venue.cppに必要な宣言[venue.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _VENUE_H_ //このマクロ定義がされていなかったら
#define _VENUE_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "model.h"

//会場クラス
class CVenue : public CModel
{
public:

	//テクスチャパス
	static const std::string MODEL_PATH;
	static const std::string BOSSBATTLE_MODEL_PATH;

	//描画
	void Draw() override;
};

#endif