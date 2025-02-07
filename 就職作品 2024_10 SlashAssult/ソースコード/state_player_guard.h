//================================
//
//state_player_guard.cpp�ɕK�v�Ȑ錾[state_player_guard.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_PLAYER_GUARD_H_ //���̃}�N����`������Ă��Ȃ�������
#define _STATE_PLAYER_GUARD_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "state_player.h"
#include "effect_guard.h"

//�K�[�h�X�e�[�g�N���X
class CState_Player_Guard : public CState_Player
{
public:

	//�萔
	static constexpr int TIME_STIFFNESS{ 40 };			//�K�[�h���d���̎���
	static constexpr float VALUE_ATTENUATION{ 0.1f };	//�m�b�N�o�b�N�̌�����
	static constexpr float VALUE_KNOCKBACK{ 12.0f };	//�m�b�N�o�b�N�̒l
	static constexpr int TIME_JUSTGUARD{ 1 };			//�W���X�g�K�[�h����������t���[��
	static constexpr int TIME_FIRST_STIFFNESS{ 20 };	//�K�[�h�̔������̍d���t���[��

	//�����o�֐�
	CState_Player_Guard(CPlayer* player);	//�R���X�g���N�^
	~CState_Player_Guard() override;		//�f�X�g���N�^

	void UpdateState(CPlayer* player) override;				//��Ԃ̍X�V
	bool SetDamage(CPlayer* player, int damage, float angle) override;	//�_���[�W�̐ݒ�

private:

	//�s���̍X�V
	void UpdateBehavior(CPlayer* player) override;

	//�d�����̍X�V����
	void UpdateStiffness(CPlayer* player);	//�K�[�h���̍d��
	void UpdateFirstStiffness();			//�������̍d��

	D3DXVECTOR3 KnockBackMove;	//�m�b�N�o�b�N�̈ړ���
	bool m_bStiffening;			//�d������
	int m_nStiffnessCount;		//�d�����̃J�E���g
	int m_nFirstStiffnessCount;	//�����d�����̃J�E���g
	CEffect_Guard* m_pEffect;	//�K�[�h���̃G�t�F�N�g
	bool m_bJustGuard;			//�W���X�g�K�[�h��������
};

#endif