//================================
//
//�G�̍s���܂Ƃ�[behavior_enemy001.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "behavior_enemy001.h"
#include "enemy001.h"

//======================================================================
//�ǂ�������
//======================================================================

//====================================
//�R���X�g���N�^
//====================================
CEnemyBehavior_Chase001::CEnemyBehavior_Chase001(CEnemy* enemy) : CEnemyBehavior_Chase(enemy)
{
	enemy->SetMotion(CEnemy001::ENEMY001MOTION_WALK);	//���[�V�����̐ݒ�

	//�ŗL�̐ݒ�
	CEnemy001* enemy001 = dynamic_cast<CEnemy001*>(enemy);
	enemy001->SetDamageJudge(false);	//�_���[�W���󂯂Ȃ�����
}

//====================================
//�s����ݒ�
//====================================
void CEnemyBehavior_Chase001::Action(CEnemy* enemy)
{
	//�ǂ�������s��(���)��ݒ�
	CEnemyBehavior_Chase::Action(enemy);
}

//====================================
//���̍s����ݒ�
//====================================
void CEnemyBehavior_Chase001::NextAction(CEnemy* enemy)
{
	//�U����ݒ�
	SetNextAction(new CEnemyBehavior_Attack001(enemy));
}

//======================================================================
//�U��
//======================================================================

//====================================
//�R���X�g���N�^
//====================================
CEnemyBehavior_Attack001::CEnemyBehavior_Attack001(CEnemy* enemy) : CEnemyBehavior_Attack(enemy)
{
	//�ݒ�
	GetAttackInstanse()->SetCollisionTime(START_COLLISON_TIME);	//������n�߂鎞��
	GetAttackInstanse()->SetEndTime(END_TIME);					//�I������
	GetAttackInstanse()->SetDamageValue(DAMAGE_VALUE);			//�_���[�W��
	SetAttackLength(ATTACK_LENGTH);								//�U���̋���
	enemy->SetMotion(CEnemy001::ENEMY001MOTION_ATTACK);			//���[�V����

	//�ŗL�̐ݒ�
	CEnemy001* enemy001 = dynamic_cast<CEnemy001*>(enemy);
	enemy001->SetDamageJudge(true);				//�_���[�W���󂯂锻��
}

//====================================
//�s����ݒ�
//====================================
void CEnemyBehavior_Attack001::Action(CEnemy* enemy)
{
	CEnemyBehavior_Attack::Action(enemy);
}

//====================================
//���̍s����ݒ�
//====================================
void CEnemyBehavior_Attack001::NextAction(CEnemy* enemy)
{
	//�ǂ�������
	SetNextAction(new CEnemyBehavior_Chase001(enemy));
}