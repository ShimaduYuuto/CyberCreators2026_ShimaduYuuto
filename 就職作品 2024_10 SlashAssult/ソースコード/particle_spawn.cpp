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

	//インターバルを終えたら生成
	if (m_nCount >= m_Info.nCreateInterval)
	{
		//パーティクルの生成
		CreateParticle();

		//カウントを初期化
		m_nCount = 0;
	}
}

//============================
//パーティクルの生成
//============================
void CParticle_Spawn::CreateParticle()
{
	//パラメータの設定
	CParticle* pParticle = CParticle::Create(m_Pos);			//生成
	pParticle->SetMaxLife(m_Info.nParticleLife);				//寿命
	pParticle->SetNormalSize(m_Info.fParticleSize);				//サイズ
	pParticle->SetAttenuationValue(m_Info.fAttenuationValue);	//減衰量
	pParticle->SetColor(m_Info.Color);							//色

	// -314～314の範囲
	float fRandom = CManager::GetInstance()->GetRundom(-314, 314) * 0.01f;

	//移動量の設定
	pParticle->SetMove({ sinf(fRandom) * m_Info.fMoveValue, 0.0f, cosf(fRandom) * m_Info.fMoveValue });

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