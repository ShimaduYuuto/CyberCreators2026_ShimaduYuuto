//======================================
//
//	�|�[�Y�̑I�����̏���[pause_select.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "pause_select.h"
#include "select_continue.h"
#include "select_restart.h"
#include "select_title.h"

//�T�C�Y
const D3DXVECTOR3 CPause_Select::SIZE = { 400.0f, 100.0f, 0.0f };

//============================
//�R���X�g���N�^
//============================
CPause_Select::CPause_Select(int nPriority) : CObject2D(nPriority)
{

}

//============================
//�f�X�g���N�^
//============================
CPause_Select::~CPause_Select()
{

}

//============================
//������
//============================
HRESULT CPause_Select::Init()
{
	//������
	CObject2D::Init();

	SetPos({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f });
	SetSize(SIZE);

	return S_OK;
}

//============================
//�I������
//============================
void CPause_Select::Uninit()
{
	CObject2D::Uninit();
}

//============================
//�X�V
//============================
void CPause_Select::Update()
{
	//�X�V����
	CObject2D::Update();
}

//============================
//���莞�̏���
//============================
void CPause_Select::Decision()
{

}

//============================
//�`��
//============================
void CPause_Select::Draw()
{
	//�`�揈��
	CObject2D::Draw();
}

//============================
//�N���G�C�g
//============================
CPause_Select* CPause_Select::Create(CHOICE choice, D3DXVECTOR3 pos)
{
	//�|�C���^�p�̕ϐ�
	CPause_Select* pPause_Select = nullptr;

	switch (choice)
	{
	case CHOICE_CONTINUE:
		pPause_Select = new CSelect_Continue();
		break;

	case CHOICE_RESTART:
		pPause_Select = new CSelect_Restart();
		break;

	case CHOICE_TITLE:
		pPause_Select = new CSelect_Title();
		break;
	}

	//������
	pPause_Select->Init();
	pPause_Select->SetPos(pos);

	return pPause_Select;
}