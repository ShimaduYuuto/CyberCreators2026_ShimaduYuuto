//================================
//
//state_bullet_reflection.cpp�ɕK�v�Ȑ錾[state_bullet_reflection.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_BULLET_REFLECTION_H_ //���̃}�N����`������Ă��Ȃ�������
#define _STATE_BULLET_REFLECTION_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "state_bullet.h"

//�e�̒ʏ��ԃN���X
class CState_Bullet_Reflection : public CState_Bullet
{
public:

	//�����o�֐�
	CState_Bullet_Reflection(CEnemyBullet* bullet) : CState_Bullet(bullet) {}	//�R���X�g���N�^
	~CState_Bullet_Reflection() {}						//�f�X�g���N�^

	//�����蔻��̊m�F
	void CheckCollision(CEnemyBullet* bullet) override;

};

#endif