//======================================
//
//	�G�l�~�[�̏���[enemy002.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "enemy002.h"
#include "manager.h"
#include "game.h"
#include "state_enemy002.h"

//�萔
const std::string CEnemy002::FILEPATH = "data\\enemy012motion.txt";

//============================
//�G�l�~�[�̃R���X�g���N�^
//============================
CEnemy002::CEnemy002() : 
	m_bMaterialized(true),
	m_fCurrentAlpha(1.0f),
	m_fGoalfAlpha(1.0f),
	m_fAddAlpha(0.0f),
	m_bUpdateAlpha(false)
{
	
}

//============================
//�G�l�~�[�̃f�X�g���N�^
//============================
CEnemy002::~CEnemy002()
{

}

//============================
//�G�l�~�[�̏�����
//============================
HRESULT CEnemy002::Init()
{
	//������
	CEnemy::Init();

	//�p�����[�^�̏�����
	SetLife(LIFE);	//�̗�

	//���[�V�����̓ǂݍ���
	SetMotionInfo(FILEPATH.c_str());

	//�|�C���^�ɍs����ݒ�
	ChangeState(new CState_Enemy002_Direction(this));

	SetMaterialized(true);
	
	return S_OK;
}

//============================
//�G�l�~�[�̏I������
//============================
void CEnemy002::Uninit()
{
	//������
	CEnemy::Uninit();
}

//============================
//�G�l�~�[�̍X�V
//============================
void CEnemy002::Update()
{
	//���S�t���O�������Ă���Ȃ甲����
	if (GetDeath())
	{
		return;
	}

	//���l�̍X�V
	UpdateAlpha();

	//���ʏ����̍X�V
	CEnemy::Update();
}

//============================
//�G�l�~�[�̕`��
//============================
void CEnemy002::Draw()
{
	//�`��
	CCharacter::Draw();
}

//============================
//�ʒu�̍X�V
//============================
void CEnemy002::UpdatePos()
{
	//�̗͂��c���Ă���Ȃ�ʒu���X�V
	if (GetLife() <= 0)
	{
		return;
	}

	CGame_Character::UpdatePos();
}

//============================
//���l�̍X�V
//============================
void CEnemy002::UpdateAlpha()
{
	//�ړI�̃��l�Ɠ����Ȃ甲����
	if (m_fCurrentAlpha == m_fGoalfAlpha)
	{
		m_bUpdateAlpha = false;
		m_fAddAlpha = 0.0f;
		return;
	}

	//�X�V���̔���ɂ��ď����ݒ�
	if (!m_bUpdateAlpha)
	{
		m_bUpdateAlpha = true;
		m_fAddAlpha = (m_fGoalfAlpha - m_fCurrentAlpha) / TIME_GOAL_ALPHA;	//���Z����F���Z�o
	}

	m_fCurrentAlpha += m_fAddAlpha;	//���Z

	//�덷���C��
	if (m_fCurrentAlpha > m_fGoalfAlpha - 0.001f && m_fCurrentAlpha < m_fGoalfAlpha + 0.001f)
	{
		m_fCurrentAlpha = m_fGoalfAlpha;
	}

	//�p�[�c����������
	for (auto itr : GetModelPartsVector())
	{
		itr->SetAlpha(m_fCurrentAlpha);
	}
}

//============================
//�_���[�W�̐ݒ�
//============================
bool CEnemy002::SetDamage(int damage, float angle)
{
	//���̉����Ă��Ȃ��Ȃ瓖����Ȃ�
	if (!m_bMaterialized)
	{
		return false;
	}

	//����t���Ă��Ȃ��Ȃ�_���[�W��Ԃ�
	if (!GetEnteredStick())
	{
		//��Ԃ̕ύX
		ChangeState(new CState_Enemy002_Damage(this));

		//���̏���
		CEnemy::SetDamage(damage, angle);
	}
	else
	{
		//���̏���
		CEnemy::SetDamage(damage, angle);
	}

	return true;
}

//============================
//�_���[�W�̐ݒ�
//============================
bool CEnemy002::SetBlowDamage(int damage, float rotY)
{
	//���̉����Ă��Ȃ��Ȃ瓖����Ȃ�
	if (!m_bMaterialized)
	{
		return false;
	}

	CEnemy::SetBlowDamage(damage, rotY);

	return true;
}

//============================
//�_���[�W�̐ݒ�
//============================
bool CEnemy002::SetBlowDamage(int damage, float rotY, float value)
{
	//���̉����Ă��Ȃ��Ȃ瓖����Ȃ�
	if (!m_bMaterialized)
	{
		return false;
	}

	CEnemy::SetBlowDamage(damage, rotY, value);

	return true;
}

//============================
//���̉��̐ݒ�
//============================
void CEnemy002::SetMaterialized(bool materialized)
{
	//�����Ȃ甲����
	if (m_bMaterialized == materialized)
	{
		return;
	}

	//���̉�����Ȃ�p�[�c�𓧖��ɂ���
	if (materialized)
	{
		m_fGoalfAlpha = 1.0f;
		GetShadow()->SetDrawJudge(true);
	}
	else
	{
		m_fGoalfAlpha = VALUE_INVISIBLE_ALPHA;
		GetShadow()->SetDrawJudge(false);
	}

	//�ݒ�
	m_bMaterialized = materialized;
}

//============================
//��Ԃ̃��Z�b�g
//============================
void CEnemy002::StateReset()
{
	//�ʏ�̏�Ԃɖ߂�
	ChangeState(new CState_Enemy002_Normal(this));
	SetEnableGravity(true);
	SetMaterialized(false);
}

//============================
//�\��t����ԂɕύX
//============================
void CEnemy002::ChangeStickState()
{
	ChangeState(new CState_Enemy002_Stick(this));
}

//============================
//�X�^����ԂɕύX
//============================
void CEnemy002::ChangeStanState()
{
	ChangeState(new CState_Enemy002_Stan(this));
	SetMaterialized(true);
}

//============================
//���S���̏���
//============================
void CEnemy002::SetCharacterDeath()
{
	//BGM�X�g�b�v
	CManager::GetInstance()->GetSound()->Stop(CSound::SOUND_LABEL_BATTLE);

	ChangeState(new CState_Enemy002_Direction_Destroy(this));
}