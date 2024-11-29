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
#include "player.h"
#include "game.h"

//定数の設定
const float CCamera::LENGTH_NORMAL = 400.0f;				//通常カメラの距離
const float CCamera::LENGTH_SLOW = LENGTH_NORMAL * 0.7f;	//スローカメラの距離

//============================
//カメラのコンストラクタ
//============================
CCamera::CCamera()
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
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//視点の初期化
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//注視点の初期化
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			//上ベクトルの初期化
	m_mtxProjection = {};							//プロジェクションマトリックスの初期化
	m_mtxView = {};									//ビューマトリックスの初期化
	m_Viewport.X = 0;
	m_Viewport.Y = 0;
	m_Viewport.Width = SCREEN_WIDTH;
	m_Viewport.Height = SCREEN_HEIGHT;
	m_Viewport.MaxZ = 1.0f;
	m_Viewport.MinZ = 0.0f;
	m_fShakeFrameCount = 0.0f;
	m_rot.y = atan2f(m_posR.x - m_posV.x, m_posR.z - m_posV.z);
	m_rot.x = 0.0f;
	m_fLength = LENGTH_NORMAL;

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
	//モードの取得
	CScene::MODE Mode = CManager::GetInstance()->GetScene()->GetMode();

	//シーンによって処理を変更
	switch (Mode)
	{
	case CScene::MODE_TITLE:	//タイトル
		break;

	case CScene::MODE_GAME:		//ゲーム

		{
			//ゲームシーンのプレイヤーの位置を取得
			CGame* pGame = nullptr;
			pGame = (CGame*)CManager::GetInstance()->GetScene();	//ゲームシーンの取得

			//プレイヤーの位置を注視点に代入
			m_posR = pGame->GetGamePlayer()->GetPos();				//プレイヤーの位置を注視点に代入
			//m_posV.y = pGame->GetGamePlayer()->GetPos().y + 50.0f;
			

			//マウスの移動量で向きを変更
			{
				//マウスの移動量の取得
				D3DXVECTOR3 MouseMove = CManager::GetInstance()->GetMouse()->GetMove();

				//カメラに反映
				m_rot.y += MouseMove.x / 100.0f;
				m_rot.x -= MouseMove.y / 500.0f;
			}

			//向きの補正
			if (m_rot.y > D3DX_PI)
			{
				m_rot.y -= D3DX_PI * 2.0f;
			}
			if (m_rot.y < -D3DX_PI)
			{
				m_rot.y += D3DX_PI * 2.0f;
			}

			if (m_rot.x > D3DX_PI * 0.4f)
			{
				m_rot.x = D3DX_PI * 0.4f;
			}
			if (m_rot.x < D3DX_PI * -0.4f)
			{
				m_rot.x = D3DX_PI * -0.4f;
			}

			//時間の状態に応じて距離を変更
			if (pGame->GetTime()->GetTimeState() == pGame->GetTime()->TIME_SLOW)
			{
				m_fLength -= 0.03f * m_fLength;

				if (m_fLength < LENGTH_SLOW)
				{
					m_fLength = LENGTH_SLOW;
				}
			}
			else
			{
				m_fLength += 0.03f * m_fLength;

				if (m_fLength > LENGTH_NORMAL)
				{
					m_fLength = LENGTH_NORMAL;
				}
			}

			//注視点の更新
			/*m_posR.y = sinf(m_rot.x) * LENGTH_POSR;
			m_posR.x = sinf(m_rot.y + D3DX_PI) * cosf(m_rot.x) * LENGTH_POSR;
			m_posR.z = cosf(m_rot.y + D3DX_PI) * cosf(m_rot.x) * LENGTH_POSR;
			m_posR += pGame->GetGamePlayer()->GetPos();*/

			//m_posR.y = -sinf(m_rot.x + D3DX_PI) * LENGTH_POSR;
			//m_posR.x = sinf(m_rot.y) * cosf(m_rot.x + D3DX_PI) * LENGTH_POSR;
			//m_posR.z = cosf(m_rot.y) * cosf(m_rot.x + D3DX_PI) * LENGTH_POSR;
			//m_posR += pGame->GetGamePlayer()->GetPos();
			
			//視点の更新(今までのやつ)
			/*m_posV.y = m_posR.y + -sinf(m_rot.x) * m_fLength;
			m_posV.x = m_posR.x + sinf(m_rot.y + D3DX_PI) * cosf(m_rot.x) * m_fLength;
			m_posV.z = m_posR.z + cosf(m_rot.y + D3DX_PI) * cosf(m_rot.x) * m_fLength;*/

			m_posV.y =/* m_posR.y + */-sinf(m_rot.x) * m_fLength;
			m_posV.x =/* m_posR.x + */sinf(m_rot.y + D3DX_PI) * cosf(m_rot.x) * m_fLength;
			m_posV.z =/* m_posR.z + */cosf(m_rot.y + D3DX_PI) * cosf(m_rot.x) * m_fLength;
			m_posV += pGame->GetGamePlayer()->GetPos();

			//視点の更新
			D3DXVECTOR3 PosVLength = pGame->GetGamePlayer()->GetPos() - m_posR;
			PosVLength = m_posR - pGame->GetGamePlayer()->GetPos();
			float fAngleY = atan2f(PosVLength.x, PosVLength.z);	//y軸の角度を算出
			float fAngleX = atan2f(PosVLength.z, PosVLength.y);	//x軸の角度を算出
			float fAngleZ = atan2f(PosVLength.x, PosVLength.y);	//z軸の角度を算出

			//m_posV.y = cosf(fAngleX/* + D3DX_PI * 0.5f*/)/* * cosf(fAngleY)*/ * m_fLength;
			//m_posV.y = pGame->GetGamePlayer()->GetPos().y;
			//m_posV.x = sinf(fAngleY)/* * sinf(fAngleX)*/ * m_fLength;
			//m_posV.z = cosf(fAngleY)/* * sinf(fAngleX)*/ * m_fLength;

			//m_posV.y = m_fLength * cos(fAngleX) * sin(fAngleZ);
			//m_posV.x = m_fLength * cos(fAngleX) * cos(fAngleZ);
			//m_posV.z = m_fLength * sin(fAngleX);
			//m_posV += pGame->GetGamePlayer()->GetPos();
		}
		
		break;

	case CScene::MODE_RESULT:	//リザルト
		break;
	};
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
		adjust = D3DXVECTOR3(rand() % (int)m_fShakeMagnitude, rand() % (int)m_fShakeMagnitude, 0.0f);
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