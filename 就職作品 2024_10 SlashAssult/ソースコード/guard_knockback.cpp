//================================
//
//�K�[�h���̃m�b�N�o�b�N����[guard_knockback.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "guard_knockback.h"
#include "effect_guard.h"
#include "effect_justguard.h"
#include "manager.h"

//====================================
//�R���X�g���N�^
//====================================
CGuard_Knockback::CGuard_Knockback(float angle) :
	KnockBackMove(),
	m_bStiffening(true),
	m_nStiffnessCount(0)
{
	//�m�b�N�o�b�N�̈ړ��ʂ�ݒ�
	KnockBackMove = { sinf(angle) * VALUE_KNOCKBACK, 0.0f, cosf(angle) * VALUE_KNOCKBACK };
	m_bStiffening = true;
	m_nStiffnessCount = 0;
}

//====================================
//�f�X�g���N�^
//====================================
CGuard_Knockback::~CGuard_Knockback()
{
	
}

//====================================
//�s���̍X�V
//====================================
void CGuard_Knockback::Update(CPlayer* player)
{
	//�d����
	if (m_bStiffening) return;

	//�d�����̍X�V
	UpdateStiffness(player);
}

//====================================
//�d�����̍X�V
//====================================
void CGuard_Knockback::UpdateStiffness(CPlayer* player)
{
	//�d�����̃t���O�������Ă���Ȃ甲����
	if (!m_bStiffening)
	{
		return;
	}

	//�J�E���g�A�b�v
	m_nStiffnessCount++;

	//�m�b�N�o�b�N�l������
	KnockBackMove.x += (0.0f - KnockBackMove.x) * VALUE_ATTENUATION;
	KnockBackMove.z += (0.0f - KnockBackMove.z) * VALUE_ATTENUATION;

	//�v���C���[�̈ړ��ʂɉ��Z
	player->AddMove(KnockBackMove);

	//���J�E���g��ɍd��������
	if (m_nStiffnessCount > TIME_STIFFNESS)
	{
		m_bStiffening = false;
		KnockBackMove = { 0.0f, 0.0f, 0.0f };
		m_nStiffnessCount = 0;
	}
}