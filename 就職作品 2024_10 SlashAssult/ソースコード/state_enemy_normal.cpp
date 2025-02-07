//================================
//
//��Ԃɉ��������������s[state_enemy_damage.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "state_enemy_normal.h"
#include "game.h"
#include "manager.h"

//====================================
//�R���X�g���N�^
//====================================
CState_Enemy_Normal::CState_Enemy_Normal(CEnemy* enemy)
{
	//�����A�N�V����
	enemy->SetEnableGravity(true);
	enemy->SetCollisionProcess(true);
}

//====================================
//��ԍX�V����
//====================================
void CState_Enemy_Normal::UpdateState(CEnemy* enemy)
{
	//�Q�[���V�[���̎擾
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

	//���̓G�Ƃ̓����蔻��
	if (enemy->GetCollisionProcess())
	{
		EnemyCollision(enemy);
	}

	//�M�~�b�N�Ƃ̓����蔻��
	UpdateGimmickCollison(enemy);
}