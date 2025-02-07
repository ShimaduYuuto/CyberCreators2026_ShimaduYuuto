//================================
//
//lifegauge.cppに必要な宣言[lifegauge.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _LIFEGAUGE_H_ //このマクロ定義がされていなかったら
#define _LIFEGAUGE_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "gauge.h"

//ゲージクラス
class CLifeGauge : public CGauge
{
public:

	//定数
	static const std::string TEXTUREPATH;	//読み込むパス

	//メンバ関数
	CLifeGauge(int nPriority = 3);	//コンストラクタ
	~CLifeGauge() override;			//デストラクタ
	void Draw() override;		//描画
	static CLifeGauge* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float max);	//ゲージの生成
};

#endif