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
	static const std::string FILEPATH;

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