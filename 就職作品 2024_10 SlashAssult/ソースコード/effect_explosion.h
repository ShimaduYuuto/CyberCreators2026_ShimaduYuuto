//================================
//
//effect_explosion.cppに必要な宣言[effect_explosion.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _EFFECT_EXPLOSION_H_ //このマクロ定義がされていなかったら
#define _EFFECT_EXPLOSION_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "objectdome.h"

//爆発エフェクトクラス
class CEffect_Explosion : public CObjectDome
{
public:

	//定数
	static const std::string FILEPATH;

	//メンバ関数
	CEffect_Explosion(int nPriority = 3);				//コンストラクタ
	~CEffect_Explosion() override;						//デストラクタ
	HRESULT Init() override;							//初期化
	void Uninit() override;								//終了
	void Update() override;								//更新
	void Draw() override;								//描画
	static CEffect_Explosion* Create(D3DXVECTOR3 pos);	//爆発の生成

private:
	float m_fSizeRate;			//爆発のサイズ倍率

};

#endif