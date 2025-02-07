//======================================
//
//	���U���g�J�����̏���[camera_result.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "camera_result.h"

//============================
//�J�����̃R���X�g���N�^
//============================
CCamera_Result::CCamera_Result()
{

}

//============================
//�J�����̃f�X�g���N�^
//============================
CCamera_Result::~CCamera_Result()
{

}

//============================
//�J�����̏�����
//============================
HRESULT CCamera_Result::Init()
{
	//���̏�����
	CCamera::Init();

	//�擾
	D3DXVECTOR3 PosR = GetPosR();
	D3DXVECTOR3 PosV = GetPos();

	PosV = D3DXVECTOR3(0.0f, 100.0f, -300.0f);		//���_
	PosR = D3DXVECTOR3(0.0f, 20.0f, 0.0f);			//�����_

	//�ݒ�
	SetPosR(PosR);
	SetPosV(PosV);

	return S_OK;
}

//============================
//�J�����̏I������
//============================
void CCamera_Result::Uninit()
{

}

//============================
//�J�����̍X�V����
//============================
void CCamera_Result::Update()
{

}