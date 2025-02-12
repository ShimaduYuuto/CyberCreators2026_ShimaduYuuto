//================================
//
//state_player_invincible.cpp�ɕK�v�Ȑ錾[state_player_invincible.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_PLAYER_INVINCIBLE_H_ //���̃}�N����`������Ă��Ȃ�������
#define _STATE_PLAYER_INVINCIBLE_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "state_player.h"

//�X�e�[�g�N���X
class CState_Player_Invincible : public CState_Player
{
public:

	//�m�b�N�o�b�N�̎���
	static constexpr int TIME_INVINCIBLE{ 90 };	//���G����
	static constexpr float ALPHA_ODD{ 0.5f };	//����̃A���t�@�l
	static constexpr float ALPHA_EVEN{ 0.2f };	//�������̃A���t�@�l

	//�����o�֐�
	CState_Player_Invincible() {};					//�R���X�g���N�^
	CState_Player_Invincible(CPlayer* player)
	{
		SetBehavior(new CPlayerBehavior_Move(player));
		SetEndTime(TIME_INVINCIBLE);
	};	//�R���X�g���N�^
	~CState_Player_Invincible() {};					//�f�X�g���N�^

	//��Ԃ̍X�V
	void UpdateState(CPlayer* player) override;
	bool SetDamage(CPlayer* player, int damage, float angle) override;	//�_���[�W�̐ݒ�

private:

	//�֐�
	void ChangeAlpha(CPlayer* player, int count);	//���l�̕ύX
};

#endif