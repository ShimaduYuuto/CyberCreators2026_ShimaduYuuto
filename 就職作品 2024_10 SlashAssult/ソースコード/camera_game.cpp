//======================================
//
//	ゲームカメラの処理[camera_game.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "camera_game.h"
#include "game.h"
#include "manager.h"

//============================
//カメラのコンストラクタ
//============================
CCamera_Game::CCamera_Game() :
	m_GoalPosR()
{
	
}

//============================
//カメラのデストラクタ
//============================
CCamera_Game::~CCamera_Game()
{

}

//============================
//カメラの初期化
//============================
HRESULT CCamera_Game::Init()
{
	//基底の初期化
	CCamera::Init();

	//取得
	D3DXVECTOR3 PosR = GetPosR();
	D3DXVECTOR3 PosV = GetPos();
	D3DXVECTOR3 Rot = GetRot();
	float fLength = GetLength();

	Rot.y = atan2f(PosR.x - PosV.x, PosR.z - PosV.z);
	Rot.x = D3DX_PI * -0.1f;
	fLength = LENGTH_NORMAL;

	//設定
	SetPosR(PosR);
	SetPosV(PosV);
	SetRot(Rot);
	SetLength(fLength);

	return S_OK;
}

//============================
//カメラの終了処理
//============================
void CCamera_Game::Uninit()
{

}

//============================
//カメラの更新処理
//============================
void CCamera_Game::Update()
{
	//ゲームシーンのプレイヤーの位置を取得
	CGame* pGame = nullptr;
	pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());	//ゲームシーンの取得

	//演出中もしくはポーズ中なら抜ける
	if (pGame->GetDirectioning() || pGame->GetPause())
	{
		return;
	}

	//取得
	D3DXVECTOR3 PosR = GetPosR();
	D3DXVECTOR3 PosV = GetPos();
	D3DXVECTOR3 Rot = GetRot();
	float fLength = GetLength();
	
	//プレイヤーの位置を注視点に代入
	if (pGame->GetGamePlayer()->GetCollision() != nullptr)
	{
		m_GoalPosR = pGame->GetGamePlayer()->GetCollision()->GetPos();
	}

	//マウスの移動量で向きを変更
	{
		//マウスの移動量の取得
		D3DXVECTOR3 MouseMove = CManager::GetInstance()->GetMouse()->GetMove();

		//カメラに反映
		Rot.y += MouseMove.x * 0.004f;
	}

	//ジョイパッドの操作
	if (CManager::GetInstance()->GetJoypad()->GetStick().afTplDiameter[CInputJoypad::STICKTYPE_RIGHT] > 0.0f)
	{
		//カメラに反映
		float fAngle = CManager::GetInstance()->GetJoypad()->GetStick().afAngle[CInputJoypad::STICKTYPE_RIGHT];
		Rot.y += sinf(fAngle) * 0.04f * CManager::GetInstance()->GetJoypad()->GetStick().afTplDiameter[CInputJoypad::STICKTYPE_RIGHT];
	}

	//向きの補正
	if (Rot.y > D3DX_PI)
	{
		Rot.y -= D3DX_PI * 2.0f;
	}
	if (Rot.y < -D3DX_PI)
	{
		Rot.y += D3DX_PI * 2.0f;
	}

	//移動量の計算
	D3DXVECTOR3 Move = (m_GoalPosR - PosR) * MOVE_RATE;

	//時間の状態に応じて距離を変更
	if (pGame->GetRushJudge())
	{
		fLength -= 0.05f * fLength;

		if (fLength < LENGTH_RUSH)
		{
			fLength = LENGTH_RUSH;
		}
	}
	else
	{
		fLength += 0.05f * fLength;

		if (fLength > LENGTH_NORMAL)
		{
			fLength = LENGTH_NORMAL;
		}
	}

	/*fLength += 0.03f * fLength;

	if (fLength > LENGTH_NORMAL)
	{
		fLength = LENGTH_NORMAL;
	}*/

	PosV.y = -sinf(Rot.x) * fLength;
	PosV.x = sinf(Rot.y + D3DX_PI) * cosf(Rot.x) * fLength;
	PosV.z = cosf(Rot.y + D3DX_PI) * cosf(Rot.x) * fLength;
	PosV += PosR + Move;

	//設定
	SetPosR(PosR + Move);
	SetPosV(PosV);
	SetRot(Rot);
	SetLength(fLength);
}