//================================
//
//�G�̍s���܂Ƃ�[behavior_enemy000.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "behavior_enemy002_alterego.h"
#include "enemy002_alterego.h"

//======================================================================
//�`���[�W�V���b�g
//======================================================================

//====================================
//�s����ݒ�
//====================================
void CEnemyBehaviorAlterEgo_ChargeShot::Action(CEnemy* enemy)
{
	//���̍s����ݒ�
	CEnemyBehavior_ChargeShot::Action(enemy);	//�`���[�W�V���b�g
}

//====================================
//���̍s����ݒ�
//====================================
void CEnemyBehaviorAlterEgo_ChargeShot::NextAction(CEnemy* enemy)
{
	SetNextAction(new CEnemyBehaviorAlterEgo_ChargeShot(enemy));	//���̍s����ݒ�
	enemy->Uninit();												//�G��j��
}