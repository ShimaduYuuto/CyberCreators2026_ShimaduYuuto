//======================================
//
//	�^�C�g���J�����̏���[camera_title.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "camera_title.h"

//�萔
const D3DXVECTOR3 CCamera_Title::POSV = { -30.0f, 30.0f, -100.0f };
const D3DXVECTOR3 CCamera_Title::POSR = { -30.0f, 20.0f, 0.0f };

//============================
//�J�����̃R���X�g���N�^
//============================
CCamera_Title::CCamera_Title()
{

}

//============================
//�J�����̃f�X�g���N�^
//============================
CCamera_Title::~CCamera_Title()
{

}

//============================
//�J�����̏�����
//============================
HRESULT CCamera_Title::Init()
{
	//���̏�����
	CCamera::Init();

	//�擾
	D3DXVECTOR3 PosR = GetPosR();
	D3DXVECTOR3 PosV = GetPos();

	//���
	PosV = POSV;		//���_
	PosR = POSR;		//�����_

	//�ݒ�
	SetPosR(PosR);
	SetPosV(PosV);

	return S_OK;
}

//============================
//�J�����̏I������
//============================
void CCamera_Title::Uninit()
{

}

//============================
//�J�����̍X�V����
//============================
void CCamera_Title::Update()
{
	
}