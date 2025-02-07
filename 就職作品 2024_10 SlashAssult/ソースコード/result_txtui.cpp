//======================================
//
//	�e�L�X�gUI�̏���[result_txtui.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "result_txtui.h"

//�萔
const std::string CResult_Txtui::TEXTUREPATH = "data\\TEXTURE\\cleartime000.png";
const D3DXVECTOR3 CResult_Txtui::POS = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.3f, 0.0f };
const D3DXVECTOR3 CResult_Txtui::SIZE = { 600.0f, 100.0f, 0.0f };

//============================
//�w�i�̃R���X�g���N�^
//============================
CResult_Txtui::CResult_Txtui(int nPriority) : CObject2D(nPriority)
{

}

//============================
//�w�i�̃f�X�g���N�^
//============================
CResult_Txtui::~CResult_Txtui()
{

}

//============================
//�w�i�̏�����
//============================
HRESULT CResult_Txtui::Init()
{
	//������
	CObject2D::Init();

	return S_OK;
}

//============================
//�w�i�̏I������
//============================
void CResult_Txtui::Uninit()
{
	CObject2D::Uninit();
}

//============================
//�w�i�̍X�V
//============================
void CResult_Txtui::Update()
{
	CObject2D::Update();
}

//============================
//�w�i�̕`��
//============================
void CResult_Txtui::Draw()
{
	//�`�揈��
	CObject2D::Draw(TEXTUREPATH.c_str());
}

//============================
//�w�i�̃N���G�C�g
//============================
CResult_Txtui* CResult_Txtui::Create()
{
	//�|�C���^�p�̕ϐ�
	CResult_Txtui* pResult_Txtui;

	//�������̊m��
	pResult_Txtui = new CResult_Txtui;

	//������
	pResult_Txtui->Init();
	pResult_Txtui->SetPos(POS);		//�ʒu
	pResult_Txtui->SetSize(SIZE);	//�T�C�Y

	return pResult_Txtui;
}