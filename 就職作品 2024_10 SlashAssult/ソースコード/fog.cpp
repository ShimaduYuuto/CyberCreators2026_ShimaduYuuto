//======================================
//
//	フォグの設定[fog.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "fog.h"
#include "manager.h"

//定数の初期化
const D3DXCOLOR CFog::DEFAULT_COLOR = D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.1f);

//============================
//コンストラクタ
//============================
CFog::CFog() :
	m_Color(COLOR_RESET_ONE),	//色
	m_fDensity(FLOAT_ZERO)		//密度
{
	//初期化
	m_Color = DEFAULT_COLOR;		//色
	m_fDensity = DEFAULT_DENDITY;	//密度
}

//============================
//デストラクタ
//============================
CFog::~CFog()
{

}

//============================
//フォグを設定
//============================
void CFog::SetFog()
{
	//フォグの設定
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//デバイスの取得
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);						//有効
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP);			//フォグモードの設定
	pDevice->SetRenderState(D3DRS_FOGCOLOR, m_Color);					//色の設定
	pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&m_fDensity));	//密度の設定
}

//============================
//フォグを解除
//============================
void CFog::ClearFog()
{
	//フォグの解除
	LPDIRECT3DDEVICE9 pDevice;										//デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);				//フォグを解除
}