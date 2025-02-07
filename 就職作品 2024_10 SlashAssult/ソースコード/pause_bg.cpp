//======================================
//
//	�|�[�Y�̔w�i�̏���[pause_bg.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "pause_bg.h"
#include "manager.h"
#include "game.h"

//�萔
const std::string CPause_Bg::TEXTURE_PATH = "data\\TEXTURE\\pause_bg000.png";

//============================
//�R���X�g���N�^
//============================
CPause_Bg::CPause_Bg(int nPriority) : CObject2D(nPriority)
{

}

//============================
//�f�X�g���N�^
//============================
CPause_Bg::~CPause_Bg()
{

}

//============================
//������
//============================
HRESULT CPause_Bg::Init()
{
	//������
	CObject2D::Init();

	SetPos({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f });
	SetSize({ SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f });
	SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f));

	return S_OK;
}

//============================
//�I������
//============================
void CPause_Bg::Uninit()
{
	CObject2D::Uninit();
}

//============================
//�X�V
//============================
void CPause_Bg::Update()
{
	//�X�V����
	CObject2D::Update();
}

//============================
//�`��
//============================
void CPause_Bg::Draw()
{
	//�`�揈��
	CObject2D::Draw();
}

//============================
//�N���G�C�g
//============================
CPause_Bg* CPause_Bg::Create()
{
	//�|�C���^�p�̕ϐ�
	CPause_Bg* pPause_Bg;

	//�������̊m��
	pPause_Bg = new CPause_Bg;

	//������
	pPause_Bg->Init();

	return pPause_Bg;
}