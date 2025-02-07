//================================
//
//�ʏ��ԏ���[state_player_counter.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "state_player_counter.h"
#include "state_player_damage.h"
#include "state_player_normal.h"

//====================================
//��Ԃ̍X�V
//====================================
void CState_Player_Counter::UpdateState(CPlayer* player)
{
	//�J�E���^�[���������Ă�����X�V���Ȃ�
	if (m_bActivationCounter)
	{
		return;
	}

	//�����o�ϐ��̎擾
	float fEndTime{ GetEndTime() };	//�I������
	float fCount{ GetStateCount() };//�J�E���g�̎擾

	//�J�E���g�A�b�v
	fCount++;

	//�J�E���^�[�̎�t���I��
	if (fCount > TIME_COUNTER && m_bCounter)
	{
		m_bCounter = false;
	}

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

//========================
//�_���[�W�̐ݒ�
//========================
bool CState_Player_Counter::SetDamage(CPlayer* player, int damage, float angle)
{
	//���S�t���O�������Ă����甲����
	if (player->GetDeath())
	{
		return true;
	}

	//�J�E���^�[�U�����Ȃ甲����
	if (m_bActivationCounter)
	{
		return true;
	}

	//�J�E���^�[��t���Ȃ�
	if (m_bCounter)
	{
		m_bActivationCounter = true;	//�J�E���^�[������
		SetBehavior(new CPlayerBehavior_CounterAttack(player));	//�J�E���^�[�U��
		return true;
	}

	//�_���[�W���󂯂�
	player->CGame_Character::SetDamage(damage, angle);
	player->SetMotion(8);											//���[�V�����̐ݒ�
	SetNextState(new CState_Player_Damage(player));					//�X�e�[�g�̐ݒ�

	//�m�b�N�o�b�N�̈ړ��ʂ�ݒ�
	D3DXVECTOR3 Rot = player->GetRot();
	D3DXVECTOR3 Move = player->GetMove();
	D3DXVECTOR3 AddMove = { sinf(Rot.y) * 10.0f, 0.0f, cosf(Rot.y) * 10.0f };

	//�ړ��ʂ̉��Z
	Move += AddMove;
	player->SetMove(Move);

	//�C���X�^���X�̎擾
	CGauge_PlayerLife* pGauge = player->GetLifeGauge();

	//�̗̓Q�[�W�ɔ��f
	if (pGauge != nullptr)
	{
		//�Q�[�W�ɔ��f
		pGauge->GetGauge()->AddGauge(-(float)damage);
	}

	player->SetLifeGauge(pGauge);

	return true;
}