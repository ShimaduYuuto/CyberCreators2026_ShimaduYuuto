//================================
//
//state_enemy.cpp�ɕK�v�Ȑ錾[state_enemy.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_ENEMY001_H_ //���̃}�N����`������Ă��Ȃ�������
#define _STATE_ENEMY001_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "behavior_enemy001.h"
#include "state_enemy_normal.h"
#include "state_enemy_damage.h"
#include "state_enemy_blow.h"
#include "state_enemy_stick.h"
#include "state_enemy_stan.h"

//========================
//�ʏ���
//========================
class CState_Enemy001_Normal : public CState_Enemy_Normal
{
public:

	//�����o�֐�
	CState_Enemy001_Normal(CEnemy* enemy) : CState_Enemy_Normal(enemy)
	{
		SetAction(new CEnemyBehavior_Chase001(enemy));
	};	//�R���X�g���N�^

	//��Ԃ̍X�V
	void UpdateState(CEnemy* enemy) override
	{
		CState_Enemy_Normal::UpdateState(enemy);
	}
};

//========================
//�_���[�W���
//========================
class CState_Enemy001_Damage : public CState_Enemy_Damage
{
public:

	CState_Enemy001_Damage(CEnemy* enemy) : CState_Enemy_Damage(enemy)
	{
		SetAction(new CEnemyBehavior());
		SetEndTime(60);
		enemy->SetMotion(4);
	};	//�R���X�g���N�^

	//��Ԃ̍X�V
	void UpdateState(CEnemy* enemy) override
	{
		CState_Enemy_Damage::UpdateState(enemy);
	}
};

//========================
//������я��
//========================
class CState_Enemy001_Blow : public CState_Enemy_Blow
{
public:

	//�����o�֐�
	CState_Enemy001_Blow(CEnemy* enemy) : CState_Enemy_Blow(enemy)
	{
		SetAction(new CEnemyBehavior());
	};	//�R���X�g���N�^

	//��Ԃ̍X�V
	void UpdateState(CEnemy* enemy) override
	{
		CState_Enemy_Blow::UpdateState(enemy);
	}
};

//========================
//�\��t�����
//========================
class CState_Enemy001_Stick : public CState_Enemy_Stick
{
public:

	CState_Enemy001_Stick(CEnemy* enemy) : CState_Enemy_Stick(enemy)
	{
		SetEndTime(160);
	};	//�R���X�g���N�^

	//��Ԃ̍X�V
	void UpdateState(CEnemy* enemy) override
	{
		CState_Enemy_Stick::UpdateState(enemy);
	}
};

//========================
//�X�^�����
//========================
class CState_Enemy001_Stan : public CState_Enemy_Stan
{
public:

	CState_Enemy001_Stan(CEnemy* enemy) : CState_Enemy_Stan(enemy)
	{
		SetAction(new CEnemyBehavior());
		SetEndTime(180);
	};	//�R���X�g���N�^

	//��Ԃ̍X�V
	void UpdateState(CEnemy* enemy) override
	{
		CState_Enemy_Stan::UpdateState(enemy);
	}
};

#endif