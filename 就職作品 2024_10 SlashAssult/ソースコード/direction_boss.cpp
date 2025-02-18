//======================================
//
//	登場演出の処理[direction_boss.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "direction_boss.h"
#include "manager.h"
#include "game.h"

const D3DXVECTOR3 CDirection_Boss::CAMERA_POSR = { 0.0f, 50.0f, 3500.0f };
const D3DXVECTOR3 CDirection_Boss::CAMERA_POSV = { 0.0f, 50.0f, 3300.0f };

//============================
//演出のコンストラクタ
//============================
CDirection_Boss::CDirection_Boss()
{
	//カメラの位置を固定
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	pCamera->SetPosR(CAMERA_POSR);
	pCamera->SetPosV(CAMERA_POSV);

	//ゲームシーンなら判定
	if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
	{
		//ボス戦が始まった合図を出す
		CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());
		pGame->SetBossBattleJudge(true);
	}

	//終了時間
	SetEndTime(END_TIME);
}

//============================
//演出のデストラクタ
//============================
CDirection_Boss::~CDirection_Boss()
{
	CManager::GetInstance()->GetSound()->Stop(CSound::SOUND_LABEL_RUMBLING);
}

//============================
//演出の初期化
//============================
HRESULT CDirection_Boss::Init()
{
	return S_OK;
}

//============================
//演出の更新
//============================
bool CDirection_Boss::TimeUpdate()
{
	//揺らす時間
	if (GetCount() == START_SHAKE_FRAME)
	{
		//カメラを揺らす
		CCamera* pCamera = CManager::GetInstance()->GetCamera();
		pCamera->SetShake(SHAKE_FRAME, SHAKE_MAGNITUDE);
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_RUMBLING);
	}

	//終了時間の処理
	if (GetCount() == END_TIME)
	{
		CManager::GetInstance()->GetSound()->Stop(CSound::SOUND_LABEL_RUMBLING);
	}

	//演出の更新
	return CDirection::TimeUpdate();
}