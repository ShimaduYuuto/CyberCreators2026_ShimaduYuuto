//================================
//
//�G�l�~�[002�̕��g�̏�ԏ���[state_enemy002_alterego.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "state_enemy002_alterego.h"

//===============================================
//�ʏ���
//===============================================

//====================================
//�R���X�g���N�^
//====================================
CState_Enemy002_AlterEgo_Normal::CState_Enemy002_AlterEgo_Normal(CEnemy* enemy)
{
	SetAction(new CEnemyActionAlterEgo_ChargeShot(enemy));
};