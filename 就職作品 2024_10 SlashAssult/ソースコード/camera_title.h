//================================
//
//camera_title.cpp�ɕK�v�Ȑ錾[camera_title.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _CAMERA_TITLE_H_ //���̃}�N����`������Ă��Ȃ�������
#define _CAMERA_TITLE_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"
#include "camera.h"

//�^�C�g���J�����N���X
class CCamera_Title : public CCamera
{
public:

	//�萔
	static const D3DXVECTOR3 POSV;	//���_
	static const D3DXVECTOR3 POSR;	//�����_

	//�����o�֐�
	CCamera_Title();			//�R���X�g���N�^
	~CCamera_Title() override;	//�f�X�g���N�^
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
};

#endif