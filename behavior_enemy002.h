//================================
//
//behavior_enemy002.cpp�ɕK�v�Ȑ錾[behavior_enemy002.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BEHAVIOR_ENEMY002_H_ //���̃}�N����`������Ă��Ȃ�������
#define _BEHAVIOR_ENEMY002_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "behavior_enemy.h"
#include "enemybullet.h"
#include "effect_chargeshot.h"
#include "enemy002_alterego.h"

//�O���錾
class CEnemy002_AlterEgo;

//==========================
//�ǂ�������
//==========================
class CEnemyAction_Standby : public CEnemyAction
{
public:

	//�R���X�g���N�^
	CEnemyAction_Standby(CEnemy* enemy) : m_nCoolTime(0)
	{
		enemy->SetMotion(0);
		m_nCoolTime = COOL_TIME;
	};

	//�萔
	static constexpr int COOL_TIME{90};		//�N�[���^�C���̎���
	void Action(CEnemy* enemy) override;	//�A�N�V����

	//�U���A�N�V������ݒ�
	void NextAction(CEnemy* enemy) override;

private:
	int m_nCoolTime;
};

//==========================
//�G�l�~�[002�̍U������
//==========================
class CEnemyAction_Attack002 : public CEnemyAction_Attack
{
public:

	//�R���X�g���N�^
	CEnemyAction_Attack002(CEnemy* enemy)
	{
		//�ݒ�
		GetAttackInstanse()->SetCollisionTime(65);
		GetAttackInstanse()->SetEndTime(100.0f);
		GetAttackInstanse()->SetDamageValue(1);
		SetAttackLength(30.0f);
		enemy->SetMotion(2);
	};

	void Action(CEnemy* enemy) override
	{
		CEnemyAction_Attack::Action(enemy);
	};	//�U��

	//�ҋ@�A�N�V������ݒ�
	void NextAction(CEnemy* enemy) override
	{
		SetNextAction(new CEnemyAction_Standby(enemy));
	}
};

//==========================
//�`���[�W�V���b�g
//==========================
class CEnemyAction_ChargeShot : public CEnemyAction
{
public:

	static constexpr int CHARGE_TIME{ 230 };		//�`���[�W����
	static constexpr int CREATE_BULLET_TIME{ 50 };	//�e�̐�������
	static constexpr int END_TIME{ 300 };			//�A�N�V�����I������
	static constexpr float ADD_SCALE_VALUE{ 0.03f };//�X�P�[���̉��Z��

	//�R���X�g���N�^
	CEnemyAction_ChargeShot(CEnemy* enemy) : m_nChargeCount(0), m_pBullet(nullptr), m_pEffect(nullptr)
	{
		//�ݒ�
		enemy->SetMotion(4);
	};

	//�f�X�g���N�^
	~CEnemyAction_ChargeShot();

	void Action(CEnemy* enemy) override;	//�U��

	//�ҋ@�A�N�V������ݒ�
	void NextAction(CEnemy* enemy) override
	{
		SetNextAction(new CEnemyAction_Standby(enemy));
	}

private:
	int m_nChargeCount;				//�`���[�W�̃J�E���g
	CEnemyBullet* m_pBullet;		//�e�̃|�C���^
	CEffect_ChargeShot* m_pEffect;	//�G�t�F�N�g�̃|�C���^
};

//==========================
//���o
//==========================
class CEnemyAction_Direction : public CEnemyAction
{
public:

	static constexpr int DIRECTION_TIME{ 300 };	//���o�̎���

	//�R���X�g���N�^
	CEnemyAction_Direction(CEnemy* enemy);

	void Action(CEnemy* enemy) override;	//���o

	//�ǂ�������A�N�V������ݒ�
	void NextAction(CEnemy* enemy) override
	{
		SetNextAction(new CEnemyAction_Standby(enemy));
	}

private:
	int m_nCount;	//�J�E���g�p
};

//==========================
//���g�U��
//==========================
class CEnemyAction_AlterEgoAttack : public CEnemyAction
{
public:

	//���g
	static constexpr float TIME_INTERPOLATION_ALPHA{ 10 };	//�A���t�@�l��ω������鎞��
	static constexpr int TIME_START_APPEAR{ 60 };			//�o�����n�߂鎞��
	static constexpr int TIME_END_ACTION{ 90 };				//�A�N�V�����̏I��鎞��
	static constexpr int NUM_ALTEREGO{ 3 };					//���g�̐�
	
	//�R���X�g���N�^
	CEnemyAction_AlterEgoAttack(CEnemy* enemy);
	~CEnemyAction_AlterEgoAttack();

	void Action(CEnemy* enemy) override;	//���g��Ɏˌ�

	//�ǂ�������A�N�V������ݒ�
	void NextAction(CEnemy* enemy) override
	{
		SetNextAction(new CEnemyAction_Standby(enemy));
	}

private:

	int m_nCount;									//�J�E���g
	bool m_bCreateAlterEgo;							//���g�𐶐�������
	CEnemyAction_ChargeShot* m_pShotAction;			//�V���b�g�̃|�C���^
	CEnemy002_AlterEgo* m_pAlterEgo[NUM_ALTEREGO];	//���g�̃|�C���^
};

#endif