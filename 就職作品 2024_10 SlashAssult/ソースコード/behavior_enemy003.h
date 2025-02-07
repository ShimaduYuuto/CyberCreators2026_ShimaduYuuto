//================================
//
//behavior_enemy003.cpp�ɕK�v�Ȑ錾[behavior_enemy003.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BEHAVIOR_ENEMY003_H_ //���̃}�N����`������Ă��Ȃ�������
#define _BEHAVIOR_ENEMY003_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "behavior_enemy.h"

//==========================
//�ҋ@
//==========================
class CEnemyBehavior_Standby003 : public CEnemyBehavior
{
public:

	//�R���X�g���N�^
	CEnemyBehavior_Standby003(CEnemy* enemy) : m_nCoolTime(0)
	{
		enemy->SetMotion(0);
		m_nCoolTime = COOL_TIME;
		enemy->SetCollisionProcess(true);
	};

	//�萔
	static constexpr int COOL_TIME{ 90 };	//�N�[���^�C���̎���
	void Action(CEnemy* enemy) override;	//�A�N�V����

	//�U���A�N�V������ݒ�
	void NextAction(CEnemy* enemy) override;

private:
	int m_nCoolTime;
};

//==========================
//�G�l�~�[003�̍U������
//==========================
class CEnemyBehavior_Attack003 : public CEnemyBehavior_Attack
{
public:

	//�R���X�g���N�^
	CEnemyBehavior_Attack003(CEnemy* enemy) : CEnemyBehavior_Attack(enemy)
	{
		//�ݒ�
		GetAttackInstanse()->SetCollisionTime(65);
		GetAttackInstanse()->SetEndTime(100.0f);
		GetAttackInstanse()->SetDamageValue(1);
		SetAttackLength(30.0f);
		enemy->SetMotion(2);
		enemy->SetCollisionProcess(false);
	};

	void Action(CEnemy* enemy) override
	{
		CEnemyBehavior_Attack::Action(enemy);
	};	//�U��

	//�ҋ@�A�N�V������ݒ�
	void NextAction(CEnemy* enemy) override
	{
		SetNextAction(new CEnemyBehavior_Standby003(enemy));
	}
};

//==========================
//�`���[�W�A�^�b�N
//==========================
class CEnemyBehavior_ChargeAttack : public CEnemyBehavior
{
public:

	static constexpr int CHARGE_TIME{ 80 };			//�`���[�W����
	static constexpr int END_TIME{ 200 };			//�I���̎���
	static constexpr float SPEED_MOVE{ 3.0f };		//�U���̈ړ����x

	//�R���X�g���N�^
	CEnemyBehavior_ChargeAttack(CEnemy* enemy) : m_nChargeCount(0), m_fAttackAngle(0.0f)
	{
		//�ݒ�
		enemy->SetMotion(2);
		enemy->SetCollisionProcess(false);
	};

	//�f�X�g���N�^
	~CEnemyBehavior_ChargeAttack() {}

	void Action(CEnemy* enemy) override;	//�U��

	//�ҋ@�A�N�V������ݒ�
	void NextAction(CEnemy* enemy) override
	{
		SetNextAction(new CEnemyBehavior_Standby003(enemy));
	}

private:

	void LookAtPlayer(CEnemy* enemy);					//�v���C���[�̕�������
	void PreparationAttack(CEnemy* enemy, float angle);	//�U���̏���
	void EndAttack(CEnemy* enemy);						//�U���I�����̏���

	bool CheckAttackHit(CEnemy* enemy);	//�U���������������̔���

	int m_nChargeCount;		//�`���[�W�̃J�E���g
	float m_fAttackAngle;	//�ːi����
};

#endif