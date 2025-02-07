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
#include "effect_justguard.h"
#include "manager.h"

//====================================
//�R���X�g���N�^
//====================================
CState_Player_Guard::CState_Player_Guard(CPlayer* player) :
	KnockBackMove(), 
	m_bStiffening(true), 
	m_nStiffnessCount(0),
	m_pEffect(nullptr),
	m_bJustGuard(false),
	m_nFirstStiffnessCount(0)
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
	//�p�[�c����������
	for (auto itr : player->GetModelPartsVector())
	{
		itr->SetAlpha(1.0f);
	}

	//�����d���̍X�V
	UpdateFirstStiffness();

	//�d�����̍X�V
	UpdateStiffness(player);
}

//====================================
//�����d�����̍X�V
//====================================
void CState_Player_Guard::UpdateFirstStiffness()
{
	//�d�����Ԃ��߂��Ă����甲����
	if (m_nFirstStiffnessCount > TIME_FIRST_STIFFNESS)
	{
		return;
	}

	m_nFirstStiffnessCount++;

	//�����d�����Ԃ��߂�����d������߂�
	if (m_nFirstStiffnessCount > TIME_FIRST_STIFFNESS)
	{
		m_bStiffening = false;
	}
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
bool CState_Player_Guard::SetDamage(CPlayer* player, int damage, float angle)
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

	//�W���X�g�K�[�h�̃t���[�����ŃK�[�h�����甭���d�����Ȃ���
	if (m_nFirstStiffnessCount <= TIME_JUSTGUARD)
	{
		//�t���O�𗧂Ăčd�����Ȃ���
		m_bJustGuard = true;
		m_bStiffening = false;
		CEffect_JustGuard::Create(player->GetCollision()->GetPos());
		return true;
	}

	//�m�b�N�o�b�N�̈ړ��ʂ�ݒ�
	KnockBackMove = { sinf(angle) * VALUE_KNOCKBACK, 0.0f, cosf(angle) * VALUE_KNOCKBACK };
	m_bStiffening = true;
	m_nStiffnessCount = 0;
	m_nFirstStiffnessCount = TIME_FIRST_STIFFNESS + 1;

	//SE�̐ݒ�
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_REPEL);

	return true;
}