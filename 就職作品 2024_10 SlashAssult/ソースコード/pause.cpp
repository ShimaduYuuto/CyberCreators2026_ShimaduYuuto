//======================================
//
//	ポーズの処理[pause.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "pause.h"
#include "pause_bg.h"
#include "pause_select.h"
#include "manager.h"
#include "useful.h"

//============================
//コンストラクタ
//============================
CPause::CPause() :
	m_nSelect(0),
	m_pPauseSelect(),
	m_pPauseBg(nullptr)
{

}

//============================
//デストラクタ
//============================
CPause::~CPause()
{
	for (int i = 0; i < CPause_Select::CHOICE_MAX; i++)
	{
		if (m_pPauseSelect[i] != nullptr)
		{
			m_pPauseSelect[i]->Uninit();
			m_pPauseSelect[i] = nullptr;
		}
	}

	if (m_pPauseBg != nullptr)
	{
		m_pPauseBg->Uninit();
		m_pPauseBg = nullptr;
	}
}

//============================
//初期化
//============================
HRESULT CPause::Init()
{
	//背景
	m_pPauseBg = CPause_Bg::Create();

	//選択肢
	for (int i = 0; i < CPause_Select::CHOICE_MAX; i++)
	{
		m_pPauseSelect[i] = CPause_Select::Create((CPause_Select::CHOICE)i, D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 250.0f + (SCREEN_HEIGHT * 0.2f) * i, 0.0f));
		m_pPauseSelect[i]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));

		if (i == m_nSelect)
		{
			m_pPauseSelect[i]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

	return S_OK;
}

//============================
//更新
//============================
void CPause::Update()
{
	//フェードをしていたら抜ける
	if (!CManager::GetInstance()->GetFade()->GetEnd()) return;

	//下を押したら選択番号を進める
	if (TriggerDown())
	{
		//最大値を超えないかをチェック
		if (m_nSelect < CPause_Select::CHOICE_MAX - 1)
		{
			m_nSelect++;
		}
	}
	//上を押したら選択番号を戻す
	else if (TriggerUp())
	{
		//最小値を下回るかをチェック
		if (m_nSelect > 0)
		{
			m_nSelect--;
		}
	}

	//選択肢
	for (int i = 0; i < CPause_Select::CHOICE_MAX; i++)
	{
		m_pPauseSelect[i]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));

		if (i == m_nSelect)
		{
			m_pPauseSelect[i]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

	//決定ボタンを押したら
	if (TriggerDecision())
	{
		//選択番号の決定処理を行う
		m_pPauseSelect[m_nSelect]->Decision();
		delete this;
		return;
	}
}

//============================
//生成
//============================
CPause* CPause::Create()
{
	//初期化
	CPause* pPause = new CPause();
	pPause->Init();

	return pPause;
}