//================================
//
//�ʏ��ԏ���[state_player_guard.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "state_player_guard.h"
#include "state_player_damage.h"
#include "state_player_normal.h"
#include "behavior_player.h"
#include "effect_guard.h"

//====================================
//�R���X�g���N�^
//====================================
CState_Player_Guard::CState_Player_Guard(CPlayer* player) :
	KnockBackMove(), 
	m_bStiffening(false), 
	m_nStiffnessCount(0),
	m_pEffect(nullptr)
{
	SetBehavior(new CPlayerBehavior_Guard(player));							//�s���̐ݒ�
	m_pEffect = CEffect_Guard::Create(&player->GetCollision()->GetPos());	//�G�t�F�N�g�̎擾
}

//====================================
//�f�X�g���N�^
//====================================
CState_Player_Guard::~CState_Player_Guard()
{
	//�G�t�F�N�g�ɏI���̍��}�𑗂�
	if (m_pEffect != nullptr)
	{
		m_pEffect->SetEnd();
		m_pEffect = nullptr;
	}
}

//====================================
//�s���̍X�V
//====================================
void CState_Player_Guard::UpdateBehavior(CPlayer* player)
{
	//�d����
	if (m_bStiffening)
	{
		return;
	}

	//�s���̍X�V
	CState_Player::UpdateBehavior(player);
}

//====================================
//��Ԃ̍X�V
//====================================
void CState_Player_Guard::UpdateState(CPlayer* player)
{
	//�d�����̍X�V
	UpdateStiffness(player);
}

//====================================
//�d�����̍X�V
//====================================
void CState_Player_Guard::UpdateStiffness(CPlayer* player)
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

//========================
//�_���[�W�̐ݒ�
//========================
bool CState_Player_Guard::SetDamage(CPlayer* player, int damage)
{
	//���S�t���O�������Ă����甲����
	if (player->GetDeath())
	{
		return true;
	}

	//�m�b�N�o�b�N�̈ړ��ʂ�ݒ�
	KnockBackMove = { sinf(player->GetRot().y) * VALUE_KNOCKBACK, 0.0f, cosf(player->GetRot().y) * VALUE_KNOCKBACK };
	m_bStiffening = true;
	m_nStiffnessCount = 0;

	return true;
}