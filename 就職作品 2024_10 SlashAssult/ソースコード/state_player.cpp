//================================
//
//��Ԃɉ��������������s[state_player.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "state_player.h"
#include "state_player_normal.h"
#include "state_player_damage.h"
#include "manager.h"

//====================================
//�f�X�g���N�^
//====================================
CState_Player::~CState_Player()
{
	//�s���C���X�^���X�̔j��
	if (m_pBehavior != nullptr)
	{
		delete m_pBehavior;
		m_pBehavior = nullptr;
	}
}

//====================================
//��Ԃɉ������X�V����
//====================================
void CState_Player::Update(CPlayer* player)
{
	//�A�N�V�����̍X�V
	UpdateBehavior(player);

	//��ԃJ�E���g�̍X�V
	UpdateState(player);
}

//====================================
//�s���̍X�V
//====================================
void CState_Player::UpdateBehavior(CPlayer* player)
{
	//�A�N�V�����̍X�V
	if (m_pBehavior != nullptr)
	{
		//�h����̃A�N�V���������s
		m_pBehavior->Behavior(player);

		//���̃A�N�V����������Ȃ�ύX
		if (m_pBehavior->GetNextBehavior() != nullptr)
		{
			//���̃A�N�V�����ɕύX
			CPlayerBehavior* pNext = m_pBehavior->GetNextBehavior();
			delete m_pBehavior;
			m_pBehavior = nullptr;

			//���
			m_pBehavior = pNext;
		}
	}
}

//====================================
//��ԍX�V����
//====================================
void CState_Player::UpdateState(CPlayer* player)
{
	//�����o�ϐ��̎擾
	float fEndTime{ GetEndTime() };	//�I������
	float fCount{ GetStateCount() };//�J�E���g�̎擾

	//�J�E���g�A�b�v
	fCount++;

	//�J�E���g������؂������Ԃ�؂�ւ���
	if (fCount >= fEndTime)
	{
		//���̏�Ԃ�ݒ�
		if (m_pNextState == nullptr)
		{
			//�ʏ��ԂɈڍs
			m_pNextState = new CState_Player_Normal(player);
		}
	}
}

//====================================
//�s���̐ݒ�
//====================================
void CState_Player::SetBehavior(CPlayerBehavior* behavior)
{
	//���g������Ȃ����	//�����������ǂ���null�ŏ㏑���ł��Ȃ�
	m_pBehavior = behavior;
}

//========================
//�_���[�W�̐ݒ�
//========================
bool CState_Player::SetDamage(CPlayer* player, int damage, float angle)
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

	//�_���[�W���󂯂�
	player->CGame_Character::SetDamage(damage, angle);		//�_���[�W������ݒ�
	player->SetMotion(CPlayer::PLAYERMOTION_DAMAGE);		//���[�V�����̐ݒ�
	SetNextState(new CState_Player_Damage(player));			//���̏�Ԃ̐ݒ�

	//�m�b�N�o�b�N�̈ړ��ʂ��Z�o
	D3DXVECTOR3 Move = player->GetMove();
	D3DXVECTOR3 AddMove = { sinf(angle + D3DX_PI) * 10.0f, 0.0f, cosf(angle + D3DX_PI) * 10.0f };

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

	//�̗̓Q�[�W��ݒ�
	player->SetLifeGauge(pGauge);

	//SE�̐ݒ�
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_DAMAGE);

	return true;
}