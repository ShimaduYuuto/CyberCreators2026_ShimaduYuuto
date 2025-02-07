//================================
//
//pause_bg.cppに必要な宣言[pause_bg.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _PAUSE_BG_H_ //このマクロ定義がされていなかったら
#define _PAUSE_BG_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "object2D.h"

//ポーズ背景クラス
class CPause_Bg : public CObject2D
{
public:

	//定数
	static const std::string TEXTURE_PATH;	//テクスチャパス

	//メンバ関数
	CPause_Bg(int nPriority = 5);	//コンストラクタ
	~CPause_Bg() override;			//デストラクタ
	HRESULT Init() override;		//初期化
	void Uninit() override;			//終了
	void Update() override;			//更新
	void Draw() override;			//描画
	static CPause_Bg* Create();		//生成
};

#endif