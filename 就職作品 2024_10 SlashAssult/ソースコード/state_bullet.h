//================================
//
//state_bullet.cpp�ɕK�v�Ȑ錾[state_bullet.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_BULLET_H_ //���̃}�N����`������Ă��Ȃ�������
#define _STATE_BULLET_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "enemybullet.h"

//�O���錾
class CEnemyBullet;

//�e�̏�ԃN���X
class CState_Bullet
{
public:

	//�����o�֐�
	CState_Bullet(CEnemyBullet* bullet) {};	//�R���X�g���N�^
	~CState_Bullet() {}						//�f�X�g���N�^

	//�����蔻��̊m�F
	virtual void CheckCollision(CEnemyBullet* bullet) {}

};

#endif