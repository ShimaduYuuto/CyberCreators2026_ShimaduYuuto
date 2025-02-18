//======================================
//
//	パーティクルの処理[particle.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "particle.h"
#include "manager.h"

//定数
const D3DXVECTOR3 CParticle::SIZE = { 5.0f, 5.0f, 0.0f };
const std::string CParticle::TEXTUREPATH = "data\\TEXTURE\\effect000.jpg";

//============================
//パーティクルのコンストラクタ
//============================
CParticle::CParticle(int nPriority) : CObjectBillboard(nPriority),
	m_nLife(MAX_LIFE),
	m_fNormalSize(0.0f),
	m_nMaxLife(MAX_LIFE),
	m_fAttenuationValue(0.1f)
{
	//ゲームタグを設定
	SetTag(CObject::TAG_GAME);
}

//============================
//パーティクルのデストラクタ
//============================
CParticle::~CParticle()
{

}

//============================
//パーティクルの初期化
//============================
HRESULT CParticle::Init()
{
	//基底初期化
	CObjectBillboard::Init();

	//設定
	SetSize(SIZE);	//サイズ			
	return S_OK;
}

//============================
//パーティクルの終了処理
//============================
void CParticle::Uninit()
{
	//基底終了
	CObjectBillboard::Uninit();
}

//============================
//パーティクルの更新
//============================
void CParticle::Update()
{
	//寿命を減らす
	m_nLife--;

	//サイズの設定
	float fSize = ((float)m_nLife / m_nMaxLife) * m_fNormalSize;

	SetSize({ fSize, fSize , 0.0f });

	//寿命が尽きたら更新を終える
	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}

	//減速処理
	D3DXVECTOR3 Move = GetMove();
	Move.x += (0.0f - Move.x) * m_fAttenuationValue;
	Move.z += (0.0f - Move.z) * m_fAttenuationValue;
	SetMove(Move);

	//ビルボードの更新処理
	CObjectBillboard::Update();
}

//============================
//パーティクルの描画
//============================
void CParticle::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//ライティングをoff
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//αブレンディングを加算
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//フォグの設定
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	CObjectBillboard::Draw(TEXTUREPATH.c_str());
	
	//α値を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//ライティングをon
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//フォグの設定
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
}

//============================
//パーティクルの描画
//============================
void CParticle::Draw(const char* texturepath)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//αブレンディングを加算
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//フォグの設定
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	CObjectBillboard::Draw(texturepath);

	//α値を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//フォグの設定
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
}

//============================
//ビルボードのクリエイト
//============================
CParticle* CParticle::Create(D3DXVECTOR3 pos)
{
	//ポインタ用の変数
	CParticle* pObject;

	//メモリの確保
	pObject = new CParticle;

	pObject->SetPos(pos);

	//初期化
	pObject->Init();

	return pObject;
}