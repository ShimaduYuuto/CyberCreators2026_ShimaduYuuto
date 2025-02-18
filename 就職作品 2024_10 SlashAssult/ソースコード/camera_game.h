//================================
//
//camera_game.cpp�ɕK�v�Ȑ錾[camera_game.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _CAMERA_GAME_H_ //���̃}�N����`������Ă��Ȃ�������
#define _CAMERA_GAME_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"
#include "camera.h"

//�Q�[���J�����N���X
class CCamera_Game : public CCamera
{
public:

	//�萔
	static constexpr float MOVE_RATE{ 0.1f };		//�ړI�̒����_�܂ňړ����鋗���̊���
	static constexpr float LENGTH_RATE{ 0.05f };		//������ω������銄��
	static constexpr float MOUSE_RATE{ 0.004f };	//�}�E�X�̈ړ��ʂ̔��f�{��
	static constexpr float STICK_RATE{ 0.04f };		//�X�e�B�b�N�ł̈ړ��ʂ̔��f�{��

	//�����o�֐�
	CCamera_Game();					//�R���X�g���N�^
	~CCamera_Game() override;		//�f�X�g���N�^
	HRESULT Init() override;		//������
	void Uninit() override;			//�I��
	void Update() override;			//�X�V
	//void SetCamera() override;	//�J�����̐ݒ�

private:
	D3DXVECTOR3 m_GoalPosR;	//�ړI�̒����_�ʒu
};

#endif