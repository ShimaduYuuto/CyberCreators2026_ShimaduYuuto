//================================
//
//state_bullet_normal.cpp�ɕK�v�Ȑ錾[state_bullet_normal.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_BULLET_NORMAL_H_ //���̃}�N����`������Ă��Ȃ�������
#define _STATE_BULLET_NORMAL_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "state_bullet.h"

//�e�̒ʏ��ԃN���X
class CState_Bullet_Normal : public CState_Bullet
{
public:

	//�����o�֐�
	CState_Bullet_Normal(CEnemyBullet* bullet) : CState_Bullet(bullet){}	//�R���X�g���N�^
	~CState_Bullet_Normal() {}						//�f�X�g���N�^

	//�����蔻��̊m�F
	void CheckCollision(CEnemyBullet* bullet) override;

};

#endif