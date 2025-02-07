//======================================
//
//	�|�[�Y�̏���[pause.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "pause.h"
#include "pause_bg.h"
#include "pause_select.h"
#include "manager.h"
#include "useful.h"

//============================
//�R���X�g���N�^
//============================
CPause::CPause() :
	m_nSelect(0),
	m_pPauseSelect(),
	m_pPauseBg(nullptr)
{

}

//============================
//�f�X�g���N�^
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
//������
//============================
HRESULT CPause::Init()
{
	//�w�i
	m_pPauseBg = CPause_Bg::Create();

	//�I����
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
//�X�V
//============================
void CPause::Update()
{
	//�t�F�[�h�����Ă����甲����
	if (!CManager::GetInstance()->GetFade()->GetEnd()) return;

	//������������I��ԍ���i�߂�
	if (TriggerDown())
	{
		//�ő�l�𒴂��Ȃ������`�F�b�N
		if (m_nSelect < CPause_Select::CHOICE_MAX - 1)
		{
			m_nSelect++;
		}
	}
	//�����������I��ԍ���߂�
	else if (TriggerUp())
	{
		//�ŏ��l������邩���`�F�b�N
		if (m_nSelect > 0)
		{
			m_nSelect--;
		}
	}

	//�I����
	for (int i = 0; i < CPause_Select::CHOICE_MAX; i++)
	{
		m_pPauseSelect[i]->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));

		if (i == m_nSelect)
		{
			m_pPauseSelect[i]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

	//����{�^������������
	if (TriggerDecision())
	{
		//�I��ԍ��̌��菈�����s��
		m_pPauseSelect[m_nSelect]->Decision();
		delete this;
		return;
	}
}

//============================
//����
//============================
CPause* CPause::Create()
{
	//������
	CPause* pPause = new CPause();
	pPause->Init();

	return pPause;
}