//================================
//
//select_title.cppに必要な宣言[select_title.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _SELECT_TITLE_H_ //このマクロ定義がされていなかったら
#define _SELECT_TITLE_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "pause_select.h"

//ポーズ選択クラス
class CSelect_Title : public CPause_Select
{
public:

	//定数
	static const std::string TEXTURE_PATH;	//テクスチャパス

	//メンバ関数
	CSelect_Title(int nPriority = 6);	//コンストラクタ
	~CSelect_Title() override;			//デストラクタ
	void Draw() override;					//描画
	void Decision() override;				//決定時の処理
};

#endif