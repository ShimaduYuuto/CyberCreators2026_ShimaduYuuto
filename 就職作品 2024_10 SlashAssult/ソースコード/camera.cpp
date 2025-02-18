//======================================
//
//	カメラの処理[camera.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "camera.h"
#include "manager.h"
#include "main.h"

//定数の設定
const float CCamera::LENGTH_NORMAL = 320.0f;				//通常カメラの距離
const float CCamera::LENGTH_RUSH = LENGTH_NORMAL * 0.7f;	//ラッシュカメラの距離

//============================
//カメラのコンストラクタ
//============================
CCamera::CCamera() :
	m_posV(),									//視点の初期化
	m_posR(),									//注視点の初期化
	m_vecU(D3DXVECTOR3(0.0f, 1.0f, 0.0f)),		//上ベクトルの初期化
	m_mtxProjection(),							//プロジェクションマトリックスの初期化
	m_mtxView(),								//ビューマトリックスの初期化
	m_Viewport(),								//ビューポートの初期化
	m_fShakeFrameCount(0.0f),					//揺れる時間
	m_rot(),									//向き
	m_fLength(0.0f)								//距離
{

}

//============================
//カメラのデストラクタ
//============================
CCamera::~CCamera()
{

}

//============================
//カメラの初期化
//============================
HRESULT CCamera::Init()
{
	//メンバ変数の初期設定
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//視点の初期化
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//注視点の初期化
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			//上ベクトルの初期化
	m_mtxProjection = {};							//プロジェクションマトリックスの初期化
	m_mtxView = {};									//ビューマトリックスの初期化
	m_fShakeFrameCount = 0.0f;						//揺らす時間
	m_rot = { VEC3_RESET_ZERO };					//向き
	m_fLength = LENGTH_NORMAL;						//距離

	//ビューポートの初期化
	m_Viewport.X = 0;
	m_Viewport.Y = 0;
	m_Viewport.Width = SCREEN_WIDTH;
	m_Viewport.Height = SCREEN_HEIGHT;
	m_Viewport.MaxZ = 1.0f;
	m_Viewport.MinZ = 0.0f;

	return S_OK;
}

//============================
//カメラの終了処理
//============================
void CCamera::Uninit()
{
	
}

//============================
//カメラの更新処理
//============================
void CCamera::Update()
{
	
}

//============================
//カメラの設定処理
//============================
void CCamera::SetCamera()
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ

	//デバイスを取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//カメラに描画する距離
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		20000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//揺れの大きさの設定
	D3DXVECTOR3 adjust = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//揺れのカウントが残っているなら処理
	if (m_fShakeFrameCount > 0.0f)
	{
		//デクリメント
		m_fShakeFrameCount--;
		
		//揺れの大きさの設定
		adjust = D3DXVECTOR3(CRandom::GetRandom(0.0f, m_fShakeMagnitude), CRandom::GetRandom(0.0f, m_fShakeMagnitude), 0.0f);
	}

	//カメラの揺れた時の変数
	D3DXVECTOR3 ShakePosV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 ShakePosR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//カメラの揺れた時の位置
	ShakePosV = m_posV + adjust;
	ShakePosR = m_posR + adjust;

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&ShakePosV, //視点
		&ShakePosR, //注視点
		&m_vecU);//上方向のベクトル

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	pDevice->SetViewport(&m_Viewport);
}

//============================
//カメラに映っているかを返す
//============================
bool CCamera::GetViewObject(D3DXMATRIX mtx)
{
	//返す用の変数
	bool bScreen = false;

	D3DXVECTOR3 ScreenPos, MtxPos;
	ScreenPos = MtxPos = { 0.0f, 0.0f, 0.0f };
	
	D3DXVec3Project(
		&ScreenPos,
		&MtxPos,
		&m_Viewport,
		&m_mtxProjection,
		&m_mtxView,
		&mtx
	);

	//画面の範囲内にいるなら
	if (ScreenPos.x >= 0.0f && ScreenPos.x <= SCREEN_WIDTH
		&& ScreenPos.y >= 0.0f && ScreenPos.y <= SCREEN_HEIGHT)
	{
		bScreen = true;
	}

	return bScreen;
}

//============================
//カメラに映っているかを返す
//============================
bool CCamera::GetViewObject(D3DXVECTOR3 pos)
{
	//返す用の変数
	bool bScreen = false;

	D3DXVECTOR3 ScreenPos, MtxPos;
	ScreenPos = MtxPos = { 0.0f, 0.0f, 0.0f };
	D3DXMATRIX mtx;

	//位置を反映
	D3DXMatrixTranslation(&mtx, pos.x, pos.y, pos.z);

	D3DXVec3Project(
		&ScreenPos,
		&MtxPos,
		&m_Viewport,
		&m_mtxProjection,
		&m_mtxView,
		&mtx
	);

	//画面の範囲内にいるなら
	if (ScreenPos.x >= 0.0f && ScreenPos.x <= SCREEN_WIDTH
		&& ScreenPos.y >= 0.0f && ScreenPos.y <= SCREEN_HEIGHT)
	{
		bScreen = true;
	}

	return bScreen;
}

//============================
//カメラの揺れの設定
//============================
void CCamera::SetShake(float frame, float magnitude)
{
	//パラメータの設定
	m_fShakeFrameCount = frame;		//フレームカウント
	m_fShakeMagnitude = magnitude;	//揺れの大きさ
}