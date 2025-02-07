//================================
//
//gauge_playerlife.cppに必要な宣言[gauge_playerlife.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _GAUGE_PLAYERLIFE_H_ //このマクロ定義がされていなかったら
#define _GAUGE_PLAYERLIFE_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "lifegauge.h"

//プレイヤーライフゲージクラス
class CGauge_PlayerLife : public CObject2D
{
public:

	//定数
	static const std::string TEXTURE_PATH;		//テクスチャパス
	static const D3DXVECTOR3 POS;				//位置
	static const D3DXVECTOR3 SIZE;				//サイズ
	static const D3DXVECTOR3 SIZE_GAUGE;		//サイズ

	//メンバ関数
	CGauge_PlayerLife(int nPriority = 3);	//コンストラクタ
	~CGauge_PlayerLife() override;			//デストラクタ
	HRESULT Init() override;				//初期化
	void Uninit() override;					//終了
	void Update() override;					//更新
	void Draw() override;					//描画
	static CGauge_PlayerLife* Create(float max);	//ゲージの生成

	//ゲージの取得
	CGauge* GetGauge() { return m_pGauge; }

private:

	//メンバ関数
	void SetGauge(float max);	//ゲージの設定

	CLifeGauge* m_pGauge;	//ゲージのポインタ
};

#endif