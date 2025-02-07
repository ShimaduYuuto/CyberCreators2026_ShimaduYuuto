//================================
//
//particle_spawn.cppに必要な宣言[particle_spawn.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _PARTICLE_SPAWN_H_ //このマクロ定義がされていなかったら
#define _PARTICLE_SPAWN_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"

//パーティクルエディタークラス
class CParticle_Spawn
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
	CParticle_Spawn();			//コンストラクタ
	~CParticle_Spawn();			//デストラクタ
	void Update();				//更新

	//生成処理
	static CParticle_Spawn* Create(D3DXVECTOR3 pos); //生成

private:
	void Load();	//読み込み処理

	ParticleInfo m_Info;	//情報

	//パラメーター
	int m_nCount;			//カウント
	D3DXVECTOR3 m_Pos;		//位置
};

#endif