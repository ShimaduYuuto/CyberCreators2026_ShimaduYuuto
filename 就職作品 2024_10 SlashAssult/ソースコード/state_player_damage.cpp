//================================
//
//��Ԃɉ��������������s[state_player_damage.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "state_player_damage.h"
#include "state_player_invincible.h"

//====================================
//�R���X�g���N�^
//====================================
CState_Player_Damage::CState_Player_Damage(CPlayer* player)
{
	//�ݒ�
	SetEndTime(END_TIME);			//�I������
	player->SetEnableGravity(true);	//�d�͂��󂯂�
};

//====================================
//��Ԃ̍X�V
//====================================
void CState_Player_Damage::UpdateState(CPlayer* player)
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
			SetNextState(new CState_Player_Invincible(player));
		}
	}

	//�J�E���g�̍X�V
	SetStateCount(fCount);
}