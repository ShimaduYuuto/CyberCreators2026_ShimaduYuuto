//================================
//
//�G�̍s���܂Ƃ�[behavior_enemy000.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "behavior_enemy000.h"
#include "enemy000.h"

//======================================================================
//�ǂ�������
//======================================================================

//====================================
//�R���X�g���N�^
//====================================
CEnemyBehavior_Chase000::CEnemyBehavior_Chase000(CEnemy* enemy) : CEnemyBehavior_Chase(enemy)
{
	enemy->SetMotion(CEnemy000::ENEMY000MOTION_WALK);
};

//====================================
//�s����ݒ�
//====================================
void CEnemyBehavior_Chase000::Action(CEnemy* enemy)
{
	CEnemyBehavior_Chase::Action(enemy);
};	//�A�N�V����

//====================================
//���̍s����ݒ�
//====================================
void CEnemyBehavior_Chase000::NextAction(CEnemy* enemy)
{
	//�U����ݒ�
	SetNextAction(new CEnemyBehavior_Attack000(enemy));
}

//======================================================================
//�U��
//======================================================================

//====================================
//�R���X�g���N�^
//====================================
CEnemyBehavior_Attack000::CEnemyBehavior_Attack000(CEnemy* enemy) : CEnemyBehavior_Attack(enemy)
{
	//�ݒ�
	GetAttackInstanse()->SetCollisionTime(START_COLLISON_TIME);	//������n�߂鎞��
	GetAttackInstanse()->SetEndTime(END_TIME);					//�I������
	GetAttackInstanse()->SetDamageValue(DAMAGE_VALUE);			//�_���[�W��
	SetAttackLength(ATTACK_LENGTH);								//�U���̋���
	enemy->SetMotion(CEnemy000::ENEMY000MOTION_ACTION);			//���[�V����
};

//====================================
//�s����ݒ�
//====================================
void CEnemyBehavior_Attack000::Action(CEnemy* enemy)
{
	CEnemyBehavior_Attack::Action(enemy);
}

//====================================
//���̍s����ݒ�
//====================================
void CEnemyBehavior_Attack000::NextAction(CEnemy* enemy)
{
	SetNextAction(new CEnemyBehavior_Chase000(enemy));
}