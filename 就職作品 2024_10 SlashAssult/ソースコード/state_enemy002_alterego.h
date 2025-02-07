//================================
//
//state_enemy002_alterego.cpp�ɕK�v�Ȑ錾[state_enemy002_alterego.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_ENEMY002_ALTEREGO_H_ //���̃}�N����`������Ă��Ȃ�������
#define _STATE_ENEMY002_ALTEREGO_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "behavior_enemy002_alterego.h"

//========================
//�ʏ���
//========================
class CState_Enemy002_AlterEgo_Normal : public CState_Enemy_Normal
{
public:

	//�����o�֐�
	CState_Enemy002_AlterEgo_Normal(CEnemy* enemy);	//�R���X�g���N�^

	//��Ԃ̍X�V
	void UpdateState(CEnemy* enemy) override
	{
		CState_Enemy_Normal::UpdateState(enemy);
	}
};

//========================
//�_���[�W���
//========================
class CState_Enemy002_AlterEgo_Damage : public CState_Enemy002_Damage
{
public:

	//�����o�֐�
	CState_Enemy002_AlterEgo_Damage(CEnemy* enemy) : CState_Enemy002_Damage(enemy){}	//�R���X�g���N�^

	//��Ԃ̍X�V
	void UpdateState(CEnemy* enemy) override
	{
		CState_Enemy002_Damage::UpdateState(enemy);
	}
};

//========================
//������я��
//========================
class CState_Enemy002_AlterEgo_Blow : public CState_Enemy002_Blow
{
public:

	//�����o�֐�
	CState_Enemy002_AlterEgo_Blow()
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
class CState_Enemy002_AlterEgo_Stick : public CState_Enemy002_Stick
{
public:

	//�����o�֐�
	CState_Enemy002_AlterEgo_Stick(){}												//�R���X�g���N�^
	CState_Enemy002_AlterEgo_Stick(CEnemy* enemy) : CState_Enemy002_Stick(enemy){}	//�R���X�g���N�^

	//��Ԃ̍X�V
	void UpdateState(CEnemy* enemy) override
	{
		CState_Enemy_Stick::UpdateState(enemy);
	}
};

//========================
//�X�^�����
//========================
class CState_Enemy002_AlterEgo_Stan : public CState_Enemy002_Stan
{
public:

	//�����o�֐�
	CState_Enemy002_AlterEgo_Stan(){}												//�R���X�g���N�^
	CState_Enemy002_AlterEgo_Stan(CEnemy* enemy) : CState_Enemy002_Stan(enemy) {}	//�R���X�g���N�^
	~CState_Enemy002_AlterEgo_Stan() override {};									//�f�X�g���N�^

	//��Ԃ̍X�V
	void UpdateState(CEnemy* enemy) override
	{
		CState_Enemy002_Stan::UpdateState(enemy);
	}
};

//========================
//���o���
//========================
class CState_Enemy002_AlterEgo_Direction : public CState_Enemy002_Direction
{
public:

	CState_Enemy002_AlterEgo_Direction() {}													//�R���X�g���N�^
	CState_Enemy002_AlterEgo_Direction(CEnemy* enemy) : CState_Enemy002_Direction(enemy) {}	//�R���X�g���N�^

	//��Ԃ̍X�V
	void UpdateState(CEnemy* enemy) override 
	{
		CState_Enemy002_Direction::UpdateState(enemy);
	}
};

#endif