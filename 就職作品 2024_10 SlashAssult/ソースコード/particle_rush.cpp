//======================================
//
//	パーティクルの処理[particle.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "particle_rush.h"
#include "manager.h"

//定数
const D3DXVECTOR3 CParticle_Rush::SIZE = { 50.0f, 50.0f, 0.0f };
const std::string CParticle_Rush::TEXTUREPATH = "data\\TEXTURE\\effect000.jpg";
const D3DXCOLOR CParticle_Rush::COLOR = { 0.3f, 0.1f, 0.1f, 0.5f };

//============================
//パーティクルのコンストラクタ
//============================
CParticle_Rush::CParticle_Rush(int nPriority) : CParticle(nPriority)
{
	//ゲームタグを設定
	SetTag(CObject::TAG_GAME);
}

//============================
//パーティクルのデストラクタ
//============================
CParticle_Rush::~CParticle_Rush()
{

}

//============================
//パーティクルの初期化
//============================
HRESULT CParticle_Rush::Init()
{
	//初期化
	CParticle::Init();

	//パラメータの設定
	SetColor(COLOR);			//色
	SetMaxLife(MAX_LIFE);		//寿命
	SetNormalSize(NORMAL_SIZE);	//サイズ
	return S_OK;
}

//============================
//パーティクルの終了処理
//============================
void CParticle_Rush::Uninit()
{
	CParticle::Uninit();
}

//============================
//パーティクルの更新
//============================
void CParticle_Rush::Update()
{
	CParticle::Update();
}

//============================
//パーティクルの描画
//============================
void CParticle_Rush::Draw()
{
	CParticle::Draw(TEXTUREPATH.c_str());
}

//============================
//パーティクルのクリエイト
//============================
CParticle_Rush* CParticle_Rush::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//ポインタ用の変数
	CParticle_Rush* pObject;

	//メモリの確保
	pObject = new CParticle_Rush;

	pObject->SetPos(pos);

	//初期化
	pObject->Init();

	return pObject;
}