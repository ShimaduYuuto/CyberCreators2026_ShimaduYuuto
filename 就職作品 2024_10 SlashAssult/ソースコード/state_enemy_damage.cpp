//================================
//
//�_���[�W��ԏ��������s[state_enemy_damage.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "state_enemy_damage.h"
#include "state_enemy_normal.h"
#include "game.h"
#include "manager.h"

//====================================
//�R���X�g���N�^
//====================================
CState_Enemy_Damage::CState_Enemy_Damage(CEnemy* enemy) : CState_Enemy(enemy)
{
	//�ݒ�
	SetAction(new CEnemyBehavior);		//��̃A�N�V����
	enemy->SetCollisionProcess(true);	//�����蔻����s��
}

//====================================
//��ԍX�V����
//====================================
void CState_Enemy_Damage::UpdateState(CEnemy* enemy)
{
	//�����o�ϐ��̎擾
	float fEndTime{ GetEndTime() };	//�I������
	float fCount{ GetStateCount() };//�J�E���g�̎擾

	//�J�E���g�A�b�v
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());	//�Q�[���V�[���̎擾
	fCount++;																	//���Ԃɉ����ăJ�E���g�A�b�v

	//���̓G�Ƃ̓����蔻��
	EnemyCollision(enemy);

	//�M�~�b�N�Ƃ̓����蔻��
	UpdateGimmickCollison(enemy);

	//�J�E���g������؂������Ԃ�؂�ւ���
	if (fCount >= fEndTime)
	{
		//���̏�Ԃ�ݒ�
		if (GetNextState() == nullptr)
		{
			//��Ԃ̐ݒ�
			enemy->StateReset();
		}
	}

	//�J�E���g�̐ݒ�
	SetStateCount(fCount);
}