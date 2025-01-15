//======================================
//
//	パーティクルエディターの描画[particle_spawn.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "particle_spawn.h"
#include "particle.h"
#include "manager.h"

//============================
//コンストラクタ
//============================
CParticle_Spawn::CParticle_Spawn() :
	m_Info(),
	m_nCount(0)
{
	//読み込み
	Load();
}

//============================
//デストラクタ
//============================
CParticle_Spawn::~CParticle_Spawn()
{
	
}

//============================
//更新処理
//============================
void CParticle_Spawn::Update()
{
	//一定間隔ごとにパーティクルを生成
	m_nCount++;

	if (m_nCount >= m_Info.nCreateInterval)
	{
		CParticle* pParticle = CParticle::Create(m_Pos);
		pParticle->SetMaxLife(m_Info.nParticleLife);
		pParticle->SetNormalSize(m_Info.fParticleSize);
		pParticle->SetAttenuationValue(m_Info.fAttenuationValue);
		pParticle->SetColor(m_Info.Color);

		std::random_device rd;		// シード生成器
		std::mt19937 gen(rd());		// メルセンヌ・ツイスタ乱数エンジン

		// 整数型の一様分布を指定
		std::uniform_int_distribution<> dist(-314, 314); // -314～314の範囲
		float fRandom = dist(gen) * 0.01f;

		pParticle->SetMove({ sinf(fRandom) * m_Info.fMoveValue, 0.0f, cosf(fRandom) * m_Info.fMoveValue });

		m_nCount = 0;
	}
}

//============================
//読み込み処理
//============================
void CParticle_Spawn::Load()
{
	//ローカル変数宣言
	FILE* pFile;

	//ファイルを開く
	pFile = fopen("data\\FILE\\Particle000.bin", "rb");

	//ファイルに情報を書き出す
	if (pFile != NULL)
	{
		//データの記録
		fread(&m_Info, sizeof(ParticleInfo), 1, pFile);

		//ファイルを閉じる
		fclose(pFile);
	}
}

//============================
//パーティクルのクリエイト
//============================
CParticle_Spawn* CParticle_Spawn::Create(D3DXVECTOR3 pos)
{
	//ポインタ用の変数
	CParticle_Spawn* pObject;

	//メモリの確保
	pObject = new CParticle_Spawn;

	//パラメータの設定
	pObject->m_Pos = pos;	//位置の設定

	return pObject;
}