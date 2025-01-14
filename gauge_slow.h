//================================
//
//gauge_slow.cppに必要な宣言[gauge_slow.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _GAUGE_SLOW_H_ //このマクロ定義がされていなかったら
#define _GAUGE_SLOW_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "gauge.h"

//2Dオブジェクトクラス
class CGauge_Slow : public CGauge
{
public:

	//定数
	static const std::string TEXTUREPATH;		//読み込むファイル

	//メンバ関数
	CGauge_Slow(int nPriority = 3);				//コンストラクタ
	~CGauge_Slow() override;					//デストラクタ
	HRESULT Init() override;					//初期化
	void Uninit() override;						//終了
	void Update() override;						//更新
	void Draw() override;						//描画
	static CGauge_Slow* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float max);	//スローゲージの生成

private:
	D3DXVECTOR3 m_MaxSize;	//最大サイス
};

#endif