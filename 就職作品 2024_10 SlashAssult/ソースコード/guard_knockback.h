//================================
//
//guard_knockback.cpp�ɕK�v�Ȑ錾[guard_knockback.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _GUARD_KNOCKBACK_H_ //���̃}�N����`������Ă��Ȃ�������
#define _GUARD_KNOCKBACK_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "player.h"

//�K�[�h�m�b�N�o�b�N�N���X
class CGuard_Knockback
{
public:

	//�萔
	static constexpr int TIME_STIFFNESS{ 40 };			//�K�[�h���d���̎���
	static constexpr float VALUE_ATTENUATION{ 0.1f };	//�m�b�N�o�b�N�̌�����
	static constexpr float VALUE_KNOCKBACK{ 12.0f };	//�m�b�N�o�b�N�̒l
	static constexpr int TIME_FIRST_STIFFNESS{ 20 };	//�K�[�h�̔������̍d���t���[��

	//�����o�֐�
	CGuard_Knockback(float angle);	//�R���X�g���N�^
	~CGuard_Knockback();			//�f�X�g���N�^

	//�d�����I����������擾
	bool GetEndStiffness() { return m_bStiffening; }

private:

	//�s���̍X�V
	void Update(CPlayer* player);

	//�d�����̍X�V����
	void UpdateStiffness(CPlayer* player);	//�K�[�h���̍d��

	D3DXVECTOR3 KnockBackMove;	//�m�b�N�o�b�N�̈ړ���
	bool m_bStiffening;			//�d������
	int m_nStiffnessCount;		//�d�����̃J�E���g
};

#endif