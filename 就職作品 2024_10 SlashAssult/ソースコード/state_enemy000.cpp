//================================
//
//�G�l�~�[000�̏�ԏ���[state_enemy000.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "state_enemy000.h"
#include "enemy000.h"

//====================================
//�R���X�g���N�^
//====================================
CState_Enemy000_Stick::CState_Enemy000_Stick(CEnemy* enemy) : CState_Enemy_Stick(enemy)
{
	//�ݒ�
	SetEndTime(END_TIME);								//�I������
	enemy->SetMotion(CEnemy000::ENEMY000MOTION_STICK);	//���[�V����
}