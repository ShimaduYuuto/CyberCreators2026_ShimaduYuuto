//================================
//
//behavior_enemy.cpp�ɕK�v�Ȑ錾[behavior_enemy.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BEHAVIOR_ENEMY_H_ //���̃}�N����`������Ă��Ȃ�������
#define _BEHAVIOR_ENEMY_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "behavior_character.h"
#include "enemy.h"

//�O���錾
class CEnemy;

//==========================
//�G�l�~�[�A�N�V�������N���X
//==========================
class CEnemyBehavior
{
public:

	//������
	CEnemyBehavior() : m_pNextAction(nullptr) {}
	virtual ~CEnemyBehavior() {}

	//�A�N�V�����̊��
	virtual void Action(CEnemy* enemy) {}

	//���̃A�N�V����
	void SetNextAction(CEnemyBehavior* action) { m_pNextAction = action; }
	CEnemyBehavior* GetNextAction() { return m_pNextAction; }

	//���̃A�N�V�������m�肷��
	virtual void NextAction(CEnemy* enemy) {}	//���̊֐�

private:
	CEnemyBehavior* m_pNextAction;
};

//==========================
//�ǂ�������
//==========================
class CEnemyBehavior_Chase : public CEnemyBehavior
{
public:
	//�萔
	static constexpr float VALUE_MOVE = 1.0f;			//�ړ���
	static constexpr float LENGTH_CHANGEATTACK = 35.0f;	//�U�����鋗��

	CEnemyBehavior_Chase(CEnemy* enemy);	//�R���X�g���N�^

	void Action(CEnemy* enemy) override;	//�A�N�V����

	//���̍s�����m��
	void NextAction(CEnemy* enemy) override {}
};

//==========================
//�U��
//==========================
class CEnemyBehavior_Attack : public CEnemyBehavior
{
public:

	//�萔
	static constexpr float POS_LENGTH{ 20.0f };	//�U���̔������鋗��

	//�R���X�g���N�^�ƃf�X�g���N�^
	CEnemyBehavior_Attack(CEnemy* enemy);
	~CEnemyBehavior_Attack();

	//�U������
	void Action(CEnemy* enemy) override;

	//�U���̃C���X�^���X
	void SetAttackInstance(CAttack* attack) { m_pAttack = attack; }	//�ݒ�
	CAttack*& GetAttackInstanse() { return m_pAttack; }				//�擾

	//�U���̋���
	void SetAttackLength(float length) { m_fAttackLength = length; }	//�ݒ�
	float GetAttackLength() { return m_fAttackLength; }					//�擾

private:

	void CheckCollision(CEnemy* enemy);	//�����蔻��̊m�F
	bool IsCheckCollision();			//�����蔻��̏������s����
	void HitPlayer(float angle);		//�v���C���[�Ƀq�b�g�����ۂ̏���


	//��{�̍U���N���X�ƓG��p�ϐ�
	CAttack* m_pAttack;		//�U���̃C���X�^���X
	float m_fAttackLength;	//�U���̋���
};
#endif