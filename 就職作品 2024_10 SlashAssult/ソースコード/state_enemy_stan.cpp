//================================
//
//��Ԃɉ��������������s[state_enemy_stan.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "state_enemy_stan.h"
#include "state_enemy_normal.h"
#include "game.h"
#include "manager.h"

//====================================
//�R���X�g���N�^
//====================================
CState_Enemy_Stan::CState_Enemy_Stan(CEnemy* enemy) : CState_Enemy(enemy)
{
	//�����A�N�V����
	SetAction(new CEnemyBehavior);
}

//====================================
//��ԍX�V����
//====================================
void CState_Enemy_Stan::UpdateState(CEnemy* enemy)
{
	//�����o�ϐ��̎擾
	float fEndTime{ GetEndTime() };	//�I������
	float fCount{ GetStateCount() };//�J�E���g�̎擾

	//�J�E���g�A�b�v
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());	//�Q�[���V�[���̎擾
	fCount += pGame->GetTime()->GetValue<float>(1.0f);							//���Ԃɉ����ăJ�E���g�A�b�v

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