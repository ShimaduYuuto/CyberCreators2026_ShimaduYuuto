//================================
//
//state_enemy.cpp�ɕK�v�Ȑ錾[state_enemy.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_ENEMY002_H_ //���̃}�N����`������Ă��Ȃ�������
#define _STATE_ENEMY002_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "enemy.h"
#include "behavior_enemy002.h"
#include "state_enemy_normal.h"
#include "state_enemy_damage.h"
#include "state_enemy_blow.h"
#include "state_enemy_stick.h"
#include "state_enemy_stan.h"
#include "effect_stan.h"

//========================
//�ʏ���
//========================
class CState_Enemy002_Normal : public CState_Enemy_Normal
{
public:

	//�����o�֐�
	CState_Enemy002_Normal(CEnemy* enemy);	//�R���X�g���N�^

	//��Ԃ̍X�V
	void UpdateState(CEnemy* enemy) override
	{
		CState_Enemy_Normal::UpdateState(enemy);
	}
};

//========================
//�_���[�W���
//========================
class CState_Enemy002_Damage : public CState_Enemy_Damage
{
public:

	//�萔
	static constexpr int TIME_END{ 120 };	//�I������

	CState_Enemy002_Damage(CEnemy* enemy) : CState_Enemy_Damage(enemy)
	{
		SetAction(new CEnemyBehavior());
		SetEndTime(TIME_END);
		enemy->SetMotion(8);
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
class CState_Enemy002_Blow : public CState_Enemy_Blow
{
public:

	//�����o�֐�
	CState_Enemy002_Blow(CEnemy* enemy) : CState_Enemy_Blow(enemy)
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
class CState_Enemy002_Stick : public CState_Enemy_Stick
{
public:

	//�萔
	static constexpr int TIME_END{ 300 };	//�I������

	//�����o�֐�
	CState_Enemy002_Stick(CEnemy* enemy);	//�R���X�g���N�^

	//��Ԃ̍X�V
	void UpdateState(CEnemy* enemy) override
	{
		//�e�̍X�V
		CState_Enemy_Stick::UpdateState(enemy);
	}
};

//========================
//�X�^�����
//========================
class CState_Enemy002_Stan : public CState_Enemy_Stan
{
public:

	//�萔
	static constexpr int END_TIME{ 3000 };	//�I������

	//�����o�֐�
	CState_Enemy002_Stan(CEnemy* enemy);	//�R���X�g���N�^
	~CState_Enemy002_Stan() override;		//�f�X�g���N�^

	//��Ԃ̍X�V
	void UpdateState(CEnemy* enemy) override
	{
		CState_Enemy_Stan::UpdateState(enemy);
	}

private:
	CEffect_Stan* m_pStanEffect;
};

//========================
//���o���
//========================
class CState_Enemy002_Direction : public CState_Enemy
{
public:

	//�萔
	static constexpr int TIME_END{ 300 };	//�I������

	//�����o�֐�
	CState_Enemy002_Direction() : m_nCount(0)
	{
		SetAction(new CEnemyBehavior());
		SetEndTime(TIME_END);
	};	//�R���X�g���N�^

	CState_Enemy002_Direction(CEnemy* enemy);	///�R���X�g���N�^

	//��Ԃ̍X�V
	void UpdateState(CEnemy* enemy) override;

private:
	int m_nCount;	//�J�E���g�p
};

//========================
//���o���
//========================
class CState_Enemy002_Direction_Destroy : public CState_Enemy
{
public:

	CState_Enemy002_Direction_Destroy(CEnemy* enemy);	///�R���X�g���N�^

private:
	
	//��Ԃ̍X�V
	void UpdateState(CEnemy* enemy) override {}
};

#endif