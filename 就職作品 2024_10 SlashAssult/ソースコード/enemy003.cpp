//======================================
//
//	�G�l�~�[�̏���[enemy003.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "enemy003.h"
#include "manager.h"
#include "state_enemy003.h"

//�萔
const std::string CEnemy003::FILEPATH = "data\\enemy013motion.txt";

//============================
//�G�l�~�[�̃R���X�g���N�^
//============================
CEnemy003::CEnemy003() :
	m_bAttacking(false)
{
	
}

//============================
//�G�l�~�[�̃f�X�g���N�^
//============================
CEnemy003::~CEnemy003()
{

}

//============================
//�G�l�~�[�̏�����
//============================
HRESULT CEnemy003::Init()
{
	//������
	CEnemy::Init();

	//�p�����[�^�̏�����
	SetLife(LIFE);	//�̗�

	//���[�V�����̓ǂݍ���
	SetMotionInfo(FILEPATH.c_str());

	//�|�C���^�ɍs����ݒ�
	ChangeState(new CState_Enemy003_Normal(this));

	return S_OK;
}

//============================
//�G�l�~�[�̏I������
//============================
void CEnemy003::Uninit()
{
	//������
	CEnemy::Uninit();
}

//============================
//�G�l�~�[�̍X�V
//============================
void CEnemy003::Update()
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
void CEnemy003::Draw()
{
	//�`��
	CCharacter::Draw();
}

//============================
//�_���[�W�̐ݒ�
//============================
bool CEnemy003::SetDamage(int damage, float angle)
{
	//����t���Ă��Ȃ��Ȃ�_���[�W��Ԃ�
	if (!GetEnteredStick())
	{
		//�U�����Ȃ琁�����
		if (m_bAttacking)
		{
			//��Ԃ̕ύX
			CEnemy::SetBlowDamage(damage, angle);
			CEnemy::SetBlowValue({ sinf(angle + D3DX_PI) * 60.0f, 0.0f, cosf(angle + D3DX_PI) * 60.0f });

			//��Ԃ̕ύX
			ChangeState(new CState_Enemy003_Blow(this));
		}
		else
		{
			//��Ԃ̕ύX
			ChangeState(new CState_Enemy003_Damage(this));

			//���̃_���[�W����
			CEnemy::SetDamage(damage, angle);
		}
	}
	else
	{
		//���̃_���[�W����
		CEnemy::SetDamage(damage, angle);
	}

	return true;
}

//============================
//��Ԃ̃��Z�b�g
//============================
void CEnemy003::StateReset()
{
	//�ʏ�̏�Ԃɖ߂�
	ChangeState(new CState_Enemy003_Normal(this));
	SetEnableGravity(true);
	m_bAttacking = false;
}

//============================
//�\��t����ԂɕύX
//============================
void CEnemy003::ChangeStickState()
{
	ChangeState(new CState_Enemy003_Stick(this));
}

//============================
//�X�^����ԂɕύX
//============================
void CEnemy003::ChangeStanState()
{
	ChangeState(new CState_Enemy003_Stan(this));
}