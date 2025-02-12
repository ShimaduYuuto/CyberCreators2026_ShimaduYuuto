//================================
//
//particle_rush.cppに必要な宣言[particle_rush.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _PARTICLE_RUSH_H_ //このマクロ定義がされていなかったら
#define _PARTICLE_RUSH_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "particle.h"

//ラッシュパーティクルクラス
class CParticle_Rush : public CParticle
{
public:

	//定数
	static constexpr int MAX_LIFE{ 30 };		//体力の最大値
	static const D3DXVECTOR3 SIZE;				//サイズ
	static const std::string TEXTUREPATH;		//テクスチャパス
	static const D3DXCOLOR COLOR;				//色
	static constexpr float NORMAL_SIZE{ 5.0f };	//通常のサイズ

	//メンバ関数
	CParticle_Rush(int nPriority = 3);					//コンストラクタ
	~CParticle_Rush() override;							//デストラクタ
	HRESULT Init() override;							//初期化
	void Uninit() override;								//終了
	void Update() override;								//更新
	void Draw() override;								//描画
	static CParticle_Rush* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//Particleの生成

};

#endif