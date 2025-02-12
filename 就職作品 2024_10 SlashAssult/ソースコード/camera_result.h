//================================
//
//camera_game.cpp�ɕK�v�Ȑ錾[camera_game.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _CAMERA_RESULT_H_ //���̃}�N����`������Ă��Ȃ�������
#define _CAMERA_RESULT_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"
#include "camera.h"

//���U���g�J�����N���X
class CCamera_Result : public CCamera
{
public:

	//�萔
	static const D3DXVECTOR3 POSV;	//���_
	static const D3DXVECTOR3 POSR;	//�����_

	//�����o�֐�
	CCamera_Result();			//�R���X�g���N�^
	~CCamera_Result() override;	//�f�X�g���N�^
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
};

#endif