//================================
//
//particle_charge.cppに必要な宣言[particle_charge.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _PARTICLE_CHARGE_H_ //このマクロ定義がされていなかったら
#define _PARTICLE_CHARGE_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"

//チャージパーティクルクラス
class CParticle_Charge
{
public:

	//パーティクル情報
	struct ParticleInfo
	{
		int nCreateInterval;	//生成の間隔
		float fMoveValue;		//移動量
		float fAttenuationValue;//減衰量
		float fParticleSize;	//パーティクルのサイズ
		D3DXCOLOR Color;		//パーティクルの色
		int nParticleLife;		//寿命
	};

	//関数
	//メンバ関数
	CParticle_Charge();			//コンストラクタ
	~CParticle_Charge();			//デストラクタ
	void Update();				//更新

	//生成処理
	static CParticle_Charge* Create(D3DXVECTOR3 pos); //生成

private:
	void Load();	//読み込み処理

	ParticleInfo m_Info;	//情報

	//パラメーター
	int m_nCount;			//カウント
	D3DXVECTOR3 m_Pos;		//位置
};

#endif