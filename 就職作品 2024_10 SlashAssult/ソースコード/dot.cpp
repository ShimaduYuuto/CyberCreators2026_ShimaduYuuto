//======================================
//
//	�Q�[�W�̏���[dot.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "dot.h"
#include "manager.h"
#include "game.h"

//�萔
const std::string CDot::TEXTURE_PATH = "data\\TEXTURE\\dot000.png";

//============================
//�Q�[�W�̃R���X�g���N�^
//============================
CDot::CDot(int nPriority) : CObject2D(nPriority)
{

}

//============================
//�Q�[�W�̃f�X�g���N�^
//============================
CDot::~CDot()
{

}

//============================
//�Q�[�W�̏�����
//============================
HRESULT CDot::Init()
{
	//������
	CObject2D::Init();

	return S_OK;
}

//============================
//�Q�[�W�̏I������
//============================
void CDot::Uninit()
{
	CObject2D::Uninit();
}

//============================
//�Q�[�W�̍X�V
//============================
void CDot::Update()
{
	//�X�V����
	CObject2D::Update();
}

//============================
//�Q�[�W�̕`��
//============================
void CDot::Draw()
{
	//�`�揈��
	CObject2D::Draw(TEXTURE_PATH.c_str());
}

//============================
//�Q�[�W�̃N���G�C�g
//============================
CDot* CDot::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�|�C���^�p�̕ϐ�
	CDot* pDot;

	//�������̊m��
	pDot = new CDot;

	//������
	pDot->Init();
	pDot->SetPos(pos);	//�ʒu
	pDot->SetSize(size);	//�T�C�Y

	return pDot;
}