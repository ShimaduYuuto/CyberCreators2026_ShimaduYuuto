//================================
//
//explosion.cppに必要な宣言[explosion.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _EXPLOSION_H_ //このマクロ定義がされていなかったら
#define _EXPLOSION_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "objectdome.h"
#include "collision.h"

//爆発クラス
class CExplosion : public CObjectDome
{
public:

	//定数
	static const std::string FILEPATH;					//ファイルパス
	static constexpr float SIZE_RADIUS{ 100.0f };		//サイズの半径
	static constexpr float LIFE{ 40.0 };				//生存時間

	static constexpr float SIZE_STRAT_RATE{ 0.3f };		//最初のサイズ倍率
	static constexpr float INCREASE_RATE_LIFE{ 20.0f };	//サイズ倍率が増加する生存時間
	static constexpr float INCREASE_VALUE{ 0.1f };		//増加する値
	static constexpr float DECREASE_RATE_LIFE{ 10.0f };	//サイズ倍率が減少する生存時間
	static constexpr float DECREASE_VALUE{ 0.1f };		//減少する値
	static constexpr float MAX_SIZE_VALUE{ 1.0f };		//最大サイズ倍率
	static constexpr float MIN_SIZE_VALUE{ 0.0f };		//最小サイズ倍率

	//メンバ関数
	CExplosion(int nPriority = 3);			//コンストラクタ
	~CExplosion() override;					//デストラクタ
	HRESULT Init() override;				//初期化
	void Uninit() override;					//終了
	void Update() override;					//更新
	void Draw() override;					//描画
	static CExplosion* Create(D3DXVECTOR3 pos);		//爆発の生成

private:
	float m_fLife;				//寿命
	float m_fSizeRate;			//爆発のサイズ倍率
	CCollision* m_pCollision;	//当たり判定

};

#endif