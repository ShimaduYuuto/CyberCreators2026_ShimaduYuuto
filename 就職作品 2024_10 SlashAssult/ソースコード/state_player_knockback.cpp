//================================
//
//��Ԃɉ��������������s[state_player_knockback.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "state_player_knockback.h"
#include "state_player_normal.h"
#include "state_player_damage.h"
#include "manager.h"

//====================================
//��Ԃ̍X�V
//====================================
void CState_Player_Knockback::UpdateState(CPlayer* player)
{
	//�����o�ϐ��̎擾
	float fEndTime{ GetEndTime() };	//�I������
	float fCount{ GetStateCount() };//�J�E���g�̎擾

	//�J�E���g�A�b�v
	fCount++;

	//�J�E���g������؂������Ԃ�؂�ւ���
	if (fCount >= fEndTime)
	{
		//���̏�Ԃ�ݒ�
		if (GetNextState() == nullptr)
		{
			//�ʏ��ԂɈڍs
			SetNextState(new CState_Player_Normal(player));
		}
	}

	//��Ԃ̐ݒ�
	SetStateCount(fCount);
}