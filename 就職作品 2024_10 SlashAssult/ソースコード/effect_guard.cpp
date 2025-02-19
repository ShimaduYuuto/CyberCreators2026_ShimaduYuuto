//======================================
//
//	ガードエフェクトの描画[effect_guard.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "effect_guard.h"
#include "manager.h"

//定数
const std::string CEffect_Guard::TEXTURE_PATH = "data\\TEXTURE\\barrier003.png";

//============================
//コンストラクタ
//============================
CEffect_Guard::CEffect_Guard() :
	m_bEnd(false),
	m_nRatioInterpolationCount(0),
	m_pTargetPos(nullptr)
{
	//情報の初期化
	CAnimation::TextureInfo Info = { VERTICAL, HORIZONTAL, SPEED_UPDATE, LOOP };
	GetAnim().SetTextureInfo(Info);

	//ゲームタグを設定
	SetTag(CObject::TAG_GAME);
}

//============================
//デストラクタ
//============================
CEffect_Guard::~CEffect_Guard()
{
	m_pTargetPos = nullptr;
}

//============================
//初期化
//============================
HRESULT CEffect_Guard::Init()
{
	CObjectBillboard::Init();

	return S_OK;
}

//============================
//終了処理
//============================
void CEffect_Guard::Uninit()
{
	CObjectBillboard::Uninit();
}

//============================
//更新処理
//============================
void CEffect_Guard::Update()
{
	//基底の更新
	CEffect_Billboard::Update();

	//位置の設定
	SetPos(*m_pTargetPos);

	//サイズ倍率の更新
	UpdateSizeRatio();
}

//============================
//サイズ倍率の更新
//============================
void CEffect_Guard::UpdateSizeRatio()
{
	//発動中なら倍率を更新
	if (!m_bEnd)
	{
		//補間が終わっていたら抜ける
		if (m_nRatioInterpolationCount > TIME_INTERPOLATION_RATIO)
		{
			return;
		}

		//倍率を設定してカウントアップ
		SetRatio(m_nRatioInterpolationCount / (float)TIME_INTERPOLATION_RATIO);
		m_nRatioInterpolationCount++;
	}
	else
	{
		//補間が終わっていたら破棄
		if (m_nRatioInterpolationCount < 0)
		{
			Uninit();
			return;
		}

		//倍率を設定してカウントダウン
		SetRatio(m_nRatioInterpolationCount / (float)TIME_INTERPOLATION_RATIO);
		m_nRatioInterpolationCount--;
	}
}

//============================
//描画処理
//============================
void CEffect_Guard::Draw()
{
	//描画用のローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice;		//デバイスの取得用

	//デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//ライティングオフ
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//αテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	//テクスチャ描画
	CObjectBillboard::Draw(TEXTURE_PATH.c_str());

	//ライティングオン
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//αテストを元に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//============================
//生成処理
//============================
CEffect_Guard* CEffect_Guard::Create(D3DXVECTOR3* pos)
{
	//ポインタ用の変数
	CEffect_Guard* pObject;

	//メモリの確保
	pObject = new CEffect_Guard;

	//初期化
	pObject->Init();							//初期化
	pObject->m_pTargetPos = pos;				//対象の位置
	pObject->SetPos(*pObject->m_pTargetPos);	//位置
	pObject->SetSize(D3DXVECTOR3(RADIUS, RADIUS, 0.0f));	//サイズ
	pObject->SetRatio(0.0f);//倍率を0からスタートさせる

	return pObject;
}