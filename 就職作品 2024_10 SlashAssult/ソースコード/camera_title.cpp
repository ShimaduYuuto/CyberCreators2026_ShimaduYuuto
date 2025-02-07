//======================================
//
//	�^�C�g���J�����̏���[camera_title.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "camera_title.h"

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

	PosV = D3DXVECTOR3(-30.0f, 30.0f, -100.0f);		//���_
	PosR = D3DXVECTOR3(-30.0f, 20.0f, 0.0f);		//�����_

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