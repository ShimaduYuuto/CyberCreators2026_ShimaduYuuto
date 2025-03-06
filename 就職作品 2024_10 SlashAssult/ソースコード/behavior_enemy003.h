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

	//�萔
	static constexpr int COOL_TIME{ 90 };	//�N�[���^�C���̎���

	//�֐�
	CEnemyBehavior_Standby003(CEnemy* enemy);	//�R���X�g���N�^
	~CEnemyBehavior_Standby003() {}				//�f�X�g���N�^
	void Action(CEnemy* enemy) override;		//�A�N�V����
	void NextAction(CEnemy* enemy) override;	//�U���A�N�V������ݒ�

private:

	//�ϐ�
	int m_nCoolTime;
};

//==========================
//�G�l�~�[003�̍U������
//==========================
class CEnemyBehavior_Attack003 : public CEnemyBehavior_Attack
{
public:

	//�֐�
	CEnemyBehavior_Attack003(CEnemy* enemy);	//�R���X�g���N�^
	void Action(CEnemy* enemy) override;		//�U��
	void NextAction(CEnemy* enemy) override;	//���̃A�N�V������ݒ�

private:

	//�萔
	static constexpr float START_COLLISON_TIME{ 65.0f };	//�����蔻�肪�o�n�߂�t���[��
	static constexpr float END_TIME{ 100.0f };				//�U�����I������t���[��
	static constexpr int DAMAGE_VALUE{ 1 };					//�^����_���[�W��
	static constexpr float ATTACK_LENGTH{ 50.0f };			//�U�����������鋗��
};

//==========================
//�`���[�W�A�^�b�N
//==========================
class CEnemyBehavior_ChargeAttack : public CEnemyBehavior
{
public:

	//�萔
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

	//�֐�
	void LookAtPlayer(CEnemy* enemy);					//�v���C���[�̕�������
	void PreparationAttack(CEnemy* enemy, float angle);	//�U���̏���
	void EndAttack(CEnemy* enemy);						//�U���I�����̏���
	bool CheckAttackHit(CEnemy* enemy);					//�U���������������̔���

	//�ϐ�
	int m_nChargeCount;		//�`���[�W�̃J�E���g
	float m_fAttackAngle;	//�ːi����
};

#endif