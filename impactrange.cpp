//======================================
//
//	インパクトの範囲処理[impactrange.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "impactrange.h"
#include "manager.h"

//定数の初期化
const float CImpactRange::MAX_SIZERATE = 50.0f;

//============================
//コンストラクタ
//============================
CImpactRange::CImpactRange(int nPriority) : CObject3D(nPriority),m_pImpactMesh(nullptr)
{
	
}

//============================
//デストラクタ
//============================
CImpactRange::~CImpactRange()
{
	
}

//============================
//初期化
//============================
HRESULT CImpactRange::Init()
{
	//初期化
	CObject3D::Init();

	return S_OK;
}

//============================
//終了処理
//============================
void CImpactRange::Uninit()
{
	if (m_pImpactMesh != nullptr)
	{
		m_pImpactMesh->Uninit();
		m_pImpactMesh = nullptr;
	}

	//終了処理
	CObject3D::Uninit();
}

//============================
//更新
//============================
void CImpactRange::Update()
{
	//現在のサイズの倍率を取得
	float fRate = GetRate();

	//最大倍率じゃないなら
	if (fRate < MAX_SIZERATE)
	{
		//倍率を加算
		fRate += 0.3f;

		//最大倍率を超えたら
		if (fRate > MAX_SIZERATE)
		{
			fRate = MAX_SIZERATE;
		}
	}
	

	//倍率の設定
	SetRate(fRate);

	//更新処理
	CObject3D::Update();

	//メッシュ倍率の設定
	if (m_pImpactMesh != nullptr)
	{
		m_pImpactMesh->SetRate(fRate);
	}
}

//============================
//描画
//============================
void CImpactRange::Draw()
{
	//描画処理
	CObject3D::Draw("data\\TEXTURE\\circle000.png");
}

//============================
//描画
//============================
void CImpactRange::Draw(const char* texturepath)
{
	//描画処理
	CObject3D::Draw(texturepath);
}

//============================
//クリエイト
//============================
CImpactRange* CImpactRange::Create(D3DXVECTOR3 pos)
{
	//ポインタ用の変数
	CImpactRange* pObject;

	//メモリの確保
	pObject = new CImpactRange;

	//初期化
	pObject->Init();

	//パラメータの設定
	pObject->SetPos(pos);	//位置
	pObject->SetSize({ 10.0f, 0.0f, 10.0f });

	pObject->m_pImpactMesh = CImpactMesh::Create(pos, 10.0f * 0.5f);

	return pObject;
}