//======================================
//
//	�R�����̏���[colon.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "colon.h"

//�萔
const std::string CColon::TEXTURE_PATH = "data\\TEXTURE\\colon000.png";

//============================
//�R�����̃R���X�g���N�^
//============================
CColon::CColon(int nPriority) : CObject2D(nPriority)
{

}

//============================
//�R�����̃f�X�g���N�^
//============================
CColon::~CColon()
{

}

//============================
//�R�����̏�����
//============================
HRESULT CColon::Init()
{
	//������
	CObject2D::Init();

	return S_OK;
}

//============================
//�R�����̏I������
//============================
void CColon::Uninit()
{
	CObject2D::Uninit();
}

//============================
//�R�����̍X�V
//============================
void CColon::Update()
{
	//�X�V����
	CObject2D::Update();
}

//============================
//�R�����̕`��
//============================
void CColon::Draw()
{
	//�`�揈��
	CObject2D::Draw(TEXTURE_PATH.c_str());
}

//============================
//�R�����̃N���G�C�g
//============================
CColon* CColon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�|�C���^�p�̕ϐ�
	CColon* pColon;

	//�������̊m��
	pColon = new CColon;

	//������
	pColon->Init();
	pColon->SetPos(pos);	//�ʒu
	pColon->SetSize(size);	//�T�C�Y

	return pColon;
}