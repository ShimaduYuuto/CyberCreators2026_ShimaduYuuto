//================================
//
//behavior_enemy000.cpp�ɕK�v�Ȑ錾[behavior_enemy000.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BEHAVIOR_ENEMY000_H_ //���̃}�N����`������Ă��Ȃ�������
#define _BEHAVIOR_ENEMY000_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "behavior_enemy.h"

//==========================
//�ǂ�������
//==========================
class CEnemyBehavior_Chase000 : public CEnemyBehavior_Chase
{
public:

	//�萔
	static constexpr float VALUE_MOVE = 1.0f;	//�ړ���

	//�֐�
	CEnemyBehavior_Chase000(CEnemy* enemy);	//�R���X�g���N�^
	void Action(CEnemy* enemy) override;	//�A�N�V����
	void NextAction(CEnemy* enemy) override;//�U���A�N�V������ݒ�
};

//==========================
//�G�l�~�[000�̍U������
//==========================
class CEnemyBehavior_Attack000 : public CEnemyBehavior_Attack
{
public:

	//�萔
	static constexpr float START_COLLISON_TIME{ 70.0f };	//�����蔻�肪�o�n�߂�t���[��
	static constexpr float END_TIME{ 100.0f };				//�U�����I������t���[��
	static constexpr int DAMAGE_VALUE{ 1 };					//�^����_���[�W��
	static constexpr float ATTACK_LENGTH{ 30.0f };			//�U�����������鋗��

	//�֐�
	CEnemyBehavior_Attack000(CEnemy* enemy);	//�R���X�g���N�^
	void Action(CEnemy* enemy) override;	//�U��
	void NextAction(CEnemy* enemy) override;//�ǂ�������A�N�V������ݒ�
};
#endif