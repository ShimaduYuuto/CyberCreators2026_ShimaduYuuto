//================================
//
//state_player_death.cpp�ɕK�v�Ȑ錾[state_player_death.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_PLAYER_DEATH_H_ //���̃}�N����`������Ă��Ȃ�������
#define _STATE_PLAYER_DEATH_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "state_player.h"

//�X�e�[�g�N���X
class CState_Player_Death : public CState_Player
{
public:

	//�����o�֐�
	CState_Player_Death(CPlayer* player);
	/*{
		SetEndTime(30);
	};	*///�R���X�g���N�^
	~CState_Player_Death() {};					//�f�X�g���N�^

	//��Ԃ��Ƃ̍X�V
	void UpdateState(CPlayer* player) override;				//��Ԃ̍X�V
	bool SetDamage(CPlayer* player, int death, float angle) override;	//�_���[�W�̐ݒ�
};

#endif