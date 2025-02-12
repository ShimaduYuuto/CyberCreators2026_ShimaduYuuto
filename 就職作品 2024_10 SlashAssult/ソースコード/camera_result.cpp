//======================================
//
//	���U���g�J�����̏���[camera_result.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "camera_result.h"

//�萔
const D3DXVECTOR3 CCamera_Result::POSV = { 0.0f, 100.0f, -300.0f };
const D3DXVECTOR3 CCamera_Result::POSR = { 0.0f, 20.0f, 0.0f };

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
void CCamera_Result::Uninit()
{

}

//============================
//�J�����̍X�V����
//============================
void CCamera_Result::Update()
{

}