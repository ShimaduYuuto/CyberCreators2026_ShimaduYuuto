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
class CEnemyActionAlterEgo_ChargeShot : public CEnemyAction_ChargeShot
{
public:

	//�R���X�g���N�^
	CEnemyActionAlterEgo_ChargeShot(CEnemy* enemy) : CEnemyAction_ChargeShot(enemy){}	//�R���X�g���N�^
	~CEnemyActionAlterEgo_ChargeShot() {}												//�f�X�g���N�^

	void Action(CEnemy* enemy) override
	{
		CEnemyAction_ChargeShot::Action(enemy);
	}

	//�ҋ@�A�N�V������ݒ�
	void NextAction(CEnemy* enemy) override
	{
		SetNextAction(new CEnemyActionAlterEgo_ChargeShot(enemy));
	}

};

#endif