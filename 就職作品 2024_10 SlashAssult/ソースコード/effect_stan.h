//================================
//
//effect_stan.cppに必要な宣言[effect_stan.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _EFFECT_STAN_H_ //このマクロ定義がされていなかったら
#define _EFFECT_STAN_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "objectcylinder.h"

//スタンエフェクトクラス
class CEffect_Stan : public CObjectCylinder
{
public:

	//定数
	static const std::string TEXTURE_PATH;			//テクスチャパス
	static constexpr float RADIUS{ 20.0f };			//サイズ半径
	static constexpr float HEIGHT{ 30.0f };			//高さ
	static constexpr float ROTATE_SPEED{ 0.05f };	//回転速度

	//メンバ関数
	CEffect_Stan();			//コンストラクタ
	~CEffect_Stan() override;	//デストラクタ
	HRESULT Init() override;		//初期化
	void Uninit() override;			//終了
	void Update() override;			//更新
	void Draw() override;			//描画

	//生成
	static CEffect_Stan* Create(D3DXVECTOR3 pos, D3DXMATRIX* mtx);

private:

	//関数
	void MtxCalculation() override;		//マトリックスの計算
	
	//変数
	D3DXMATRIX* m_pmtxParent;
};

#endif