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

//============================
//�G�l�~�[�̃R���X�g���N�^
//============================
CEnemy002::CEnemy002() : 
	m_bMaterialized(false)
{
	SetMaterialized(false);
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
	CCharacter::SetLife(LIFE);	//�̗�

	//���[�V�����̓ǂݍ���
	SetMotionInfo("data\\enemy012motion.txt");

	//�|�C���^�ɍs����ݒ�
	ChangeState(new CState_Enemy002_Direction(this));
	
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
//�_���[�W�̐ݒ�
//============================
bool CEnemy002::SetDamage(int damage)
{
	//���̉����Ă��Ȃ��Ȃ瓖����Ȃ�
	if (!m_bMaterialized)
	{
		return false;
	}

	//���̏���
	CEnemy::SetDamage(damage);

	return true;
}

//============================
//�_���[�W�̐ݒ�
//============================
bool CEnemy002::SetDamage(int damage, float rotY)
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
		CEnemy::SetDamage(damage, rotY);
	}
	else
	{
		//���̏���
		CEnemy::SetDamage(damage);
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
		//�p�[�c����������
		for (auto itr : GetModelPartsVector())
		{
			itr->SetAlpha(1.0f);
		}
	}
	else
	{
		//�p�[�c����������
		for (auto itr : GetModelPartsVector())
		{
			itr->SetAlpha(VALUE_INVISIBLE_ALPHA);
		}
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