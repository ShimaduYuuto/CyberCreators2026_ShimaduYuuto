//================================
//
//state_player_counter.cpp�ɕK�v�Ȑ錾[state_player_counter.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_PLAYER_COUNTER_H_ //���̃}�N����`������Ă��Ȃ�������
#define _STATE_PLAYER_COUNTER_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "state_player.h"

//�J�E���^�[�X�e�[�g�N���X
class CState_Player_Counter : public CState_Player
{
public:

	//�萔
	static constexpr int TIME_COUNTER{ 30 };	//�J�E���^�[���󂯕t���鎞��
	static constexpr int TIME_END{ 60 };		//��Ԃ̎���

	//�����o�֐�
	CState_Player_Counter(CPlayer* player) : m_bCounter(true), m_bActivationCounter(false)
	{
		SetBehavior(new CPlayerBehavior(player));
		SetEndTime(TIME_END);
		player->SetMotion(15);
	};	//�R���X�g���N�^
	~CState_Player_Counter() {};				//�f�X�g���N�^

	void UpdateState(CPlayer* player) override;				//��Ԃ̍X�V
	bool SetDamage(CPlayer* player, int damage, float angle) override;	//�_���[�W�̐ݒ�

private:

	bool m_bCounter;			//�J�E���^�[�\��
	bool m_bActivationCounter;	//�J�E���^�[������������
};

#endif