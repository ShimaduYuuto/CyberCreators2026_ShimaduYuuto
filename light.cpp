//======================================
//
//	ライトの処理[light.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "light.h"
#include "manager.h"

//============================
//ライトのコンストラクタ
//============================
CLight::CLight():
	m_aLight()
{
	
}

//============================
//ライトのデストラクタ
//============================
CLight::~CLight()
{

}

//============================
//ライトの初期化
//============================
HRESULT CLight::Init()
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスを取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DXVECTOR3 vecDir; //設定用方向ベクトル

	pDevice->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//ライト情報をクリアする
	ZeroMemory(&m_aLight, sizeof(D3DLIGHT9));

	for (int nLightCnt = 0; nLightCnt < MAX_LIGHT; nLightCnt++)
	{
		//ライトの種類を設定
		m_aLight[nLightCnt].Type = D3DLIGHT_DIRECTIONAL;
		
		
		//ライトの拡散光を設定
		m_aLight[nLightCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		
		//ライトの方向を設定
		if (nLightCnt == 0)
		{
			vecDir = D3DXVECTOR3(0.0f, -1.0f, 1.0f);
		}

		if (nLightCnt == 1)
		{
			vecDir = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		}

		if (nLightCnt == 2)
		{
			vecDir = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
		}

		D3DXVec3Normalize(&vecDir, &vecDir); //ベクトルを正規化する
		m_aLight[nLightCnt].Direction = vecDir;

		//ライトを設定する
		pDevice->SetLight(nLightCnt, &m_aLight[nLightCnt]);

		//ライトを有効にする
		pDevice->LightEnable(nLightCnt, TRUE);
	}

	return S_OK;
}

//============================
//ライトの終了処理
//============================
void CLight::Uninit()
{
	
}

//============================
//ライトの更新処理
//============================
void CLight::Update()
{
	
}