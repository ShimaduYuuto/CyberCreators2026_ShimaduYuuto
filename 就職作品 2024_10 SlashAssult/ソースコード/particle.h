//================================
//
//particle.cppに必要な宣言[particle.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _PARTICLE_H_ //このマクロ定義がされていなかったら
#define _PARTICLE_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "objectbillboard.h"

//パーティクルクラス
class CParticle : public CObjectBillboard
{
public:

	//定数
	static constexpr int MAX_LIFE = 30;		//体力の最大値
	static const D3DXVECTOR3 SIZE;			//サイズ
	static const std::string TEXTUREPATH;	//テクスチャパス

	//メンバ関数
	CParticle(int nPriority = 3);						//コンストラクタ
	~CParticle() override;								//デストラクタ
	HRESULT Init() override;							//初期化
	void Uninit() override;								//終了
	void Update() override;								//更新
	void Draw() override;								//描画
	void Draw(const char* texturepath) override;		//引数のテクスチャで描画
	static CParticle* Create(D3DXVECTOR3 pos);			//Particleの生成

	//寿命
	void SetMaxLife(int life) { m_nMaxLife = life; m_nLife = life; }	//設定
	int GetMaxLife() { return m_nMaxLife; }			//取得

	//通常サイズ
	void SetNormalSize(float size) { m_fNormalSize = size; }	//設定

	//減衰量
	void SetAttenuationValue(float value) { m_fAttenuationValue = value; }	//設定
	float GetAttenuationValue() { return m_fAttenuationValue; }				//取得
	
private:
	int m_nLife;				//寿命
	int m_nMaxLife;				//寿命の最大
	float m_fNormalSize;		//通常のサイズ
	float m_fAttenuationValue;	//減衰量
};

#endif