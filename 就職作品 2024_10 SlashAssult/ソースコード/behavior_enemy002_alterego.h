//================================
//
//behavior_enemy002_alterego.cpp�ɕK�v�Ȑ錾[behavior_enemy002_alterego.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BEHAVIOR_ENEMY002_ALTEREGO_H_ //���̃}�N����`������Ă��Ȃ�������
#define _BEHAVIOR_ENEMY002_ALTEREGO_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "behavior_enemy002.h"

//==========================
//�`���[�W�V���b�g
//==========================
class CEnemyBehaviorAlterEgo_ChargeShot : public CEnemyBehavior_ChargeShot
{
public:

	//�֐�
	CEnemyBehaviorAlterEgo_ChargeShot(CEnemy* enemy) : CEnemyBehavior_ChargeShot(enemy){}	//�R���X�g���N�^
	~CEnemyBehaviorAlterEgo_ChargeShot() {}												//�f�X�g���N�^
	void Action(CEnemy* enemy) override;												//�s��
	void NextAction(CEnemy* enemy) override;											//�ҋ@�A�N�V������ݒ�

};

#endif