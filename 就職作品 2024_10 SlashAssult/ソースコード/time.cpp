//======================================
//
//	時間の処理[time.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "time.h"
#include "manager.h"
#include "game.h"

//定数の初期化
const float CTime::SLOWRATE = 0.1f;

//============================
//時間のコンストラクタ
//============================
CTime::CTime() :
	m_bEndTimer(true),
	m_nTimeCount(0),
	m_TimeState(TIME_NORMAL)
{
	
}

//============================
//時間のデストラクタ
//============================
CTime::~CTime()
{

}

//============================
//時間の初期化
//============================
HRESULT CTime::Init()
{

	return S_OK;
}

//============================
//時間の更新
//============================
void CTime::Update()
{
	//タイマーのカウントがあるなら
	if (m_nTimeCount > 0)
	{
		//カウントダウン
		m_nTimeCount--;

		//カウントが0になったら
		if (m_nTimeCount <= 0)
		{
			m_nTimeCount = 0;	//0に補正

			//タイマーの終了判定をオン
			if (!m_bEndTimer)
			{
				m_bEndTimer = true;
				m_TimeState = TIME_NORMAL;
			}
		}
	}
}

//============================
//時間の状態を設定
//============================
void CTime::SetTimeState(CTime::TIME state)
{
	//時間の状態を設定
	m_TimeState = state;
}

//============================
//状態タイマーの設定
//============================
void CTime::SetStateTimer(TIME state, int time)
{
	//状態の代入
	m_TimeState = state;

	//タイマーの設定
	m_nTimeCount = time;

	//タイマー終了フラグをオフ
	if (m_bEndTimer)
	{
		m_bEndTimer = false;
	}
}

//============================
//タイマーの設定
//============================
void CTime::SetTimer(int time)
{
	//タイマーの設定
	m_nTimeCount = time;

	//タイマー終了フラグをオフ
	if (m_bEndTimer)
	{
		m_bEndTimer = false;
	}
}