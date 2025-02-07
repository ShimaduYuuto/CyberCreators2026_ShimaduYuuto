//================================
//
//��Ԃɉ��������������s[state_player_invincible.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "state_player_invincible.h"
#include "state_player_normal.h"
#include "manager.h"

//====================================
//��Ԃ̍X�V
//====================================
void CState_Player_Invincible::UpdateState(CPlayer* player)
{	//�����o�ϐ��̎擾
	float fEndTime{ GetEndTime() };	//�I������
	float fCount{ GetStateCount() };//�J�E���g�̎擾

	//�J�E���g�A�b�v
	fCount++;

	//�_�ł�����
	if ((static_cast<int>(fCount) & 1) == 0) //����
	{
		//�p�[�c����������
		for (auto itr : player->GetModelPartsVector())
		{
			itr->SetAlpha(0.2f);
		}
	}
	else //�
	{
		//�p�[�c����������
		for (auto itr : player->GetModelPartsVector())
		{
			itr->SetAlpha(0.5f);
		}
	}

	//�J�E���g������؂������Ԃ�؂�ւ���
	if (fCount >= fEndTime)
	{
		//���̏�Ԃ�ݒ�
		if (GetNextState() == nullptr)
		{
			//�p�[�c����������
			for (auto itr : player->GetModelPartsVector())
			{
				itr->SetAlpha(1.0f);
			}

			//�ʏ��ԂɈڍs
			SetNextState(new CState_Player_Normal(player));
			GetNextState()->SetBehavior(GetBehavior());
			SetBehavior(nullptr);
		}
	}

	//��Ԃ̐ݒ�
	SetStateCount(fCount);
}

//========================
//�_���[�W�̐ݒ�
//========================
bool CState_Player_Invincible::SetDamage(CPlayer* player, int damage, float angle)
{
	//�̗͂��Ȃ��Ȃ�X�V���Ȃ�
	if (player->GetLife() <= 0)
	{
		return false;
	}

	//���S�t���O�������Ă����甲����
	if (player->GetDeath())
	{
		return true;
	}

	return true;
}