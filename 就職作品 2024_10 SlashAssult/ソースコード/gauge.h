//================================
//
//gauge.cppに必要な宣言[gauge.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _GAUGE_H_ //このマクロ定義がされていなかったら
#define _GAUGE_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "object2D.h"

//ゲージクラス
class CGauge : public CObject2D
{
public:
	//メンバ関数
	CGauge(int nPriority = 3);	//コンストラクタ
	~CGauge() override;			//デストラクタ
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画
	static CGauge* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float max);	//ゲージの生成

	//パラメーター関連の関数
	void SetMaxGauge(float max) { m_fMaxGauge = max; }		//ゲージの最大を設定
	float GetMaxGauge() { return m_fMaxGauge; }				//ゲージの最大を取得
	void SetNowGauge(float value);							//ゲージの設定
	float GetNowGauge() { return m_fNowGauge; }				//ゲージの取得
	void AddGauge(float value);								//ゲージの加算

private:
	float m_fMaxGauge;		//ゲージの最大値
	float m_fNowGauge;		//現在のゲージの値
};

#endif