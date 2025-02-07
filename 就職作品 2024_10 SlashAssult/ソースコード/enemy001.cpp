//======================================
//
//	�G�l�~�[�̏���[enemy001.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "enemy001.h"
#include "manager.h"
#include "game.h"
#include "effect_repel.h"

//�萔�̐錾
const std::string CEnemy001::FILEPATH = "data\\enemy011motion.txt";
const float CEnemy001::MOVE_VALUE = 2.0f;
const float CEnemy001::STARTATTACK_RANGE = 50.0f;

//============================
//�G�l�~�[�̃R���X�g���N�^
//============================
CEnemy001::CEnemy001() :
	m_pShield(nullptr),
	m_bDamageJudge(false)
{
	
}

//============================
//�G�l�~�[�̃f�X�g���N�^
//============================
CEnemy001::~CEnemy001()
{

}

//============================
//�G�l�~�[�̏�����
//============================
HRESULT CEnemy001::Init()
{
	//������
	CEnemy::Init();

	//�p�����[�^�̏�����
	SetLife(LIFE);	//�̗�

	//���[�V�����̓ǂݍ���
	SetMotionInfo(FILEPATH.c_str());

	//�|�C���^�ɍs����ݒ�
	ChangeState(new CState_Enemy001_Normal(this));

	//���̐���
	if (m_pShield == nullptr)
	{
		m_pShield = CShield::Create(D3DXVECTOR3(-5.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
		m_pShield->SetParent(GetModelParts(3));
	}

	return S_OK;
}

//============================
//�G�l�~�[�̏I������
//============================
void CEnemy001::Uninit()
{
	//���̔j��
	if (m_pShield != nullptr)
	{
		m_pShield->Uninit();
		m_pShield = nullptr;
	}

	//�I������
	CEnemy::Uninit();
}

//============================
//�G�l�~�[�̍X�V
//============================
void CEnemy001::Update()
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
void CEnemy001::Draw()
{
	//�`��
	CCharacter::Draw();
}

//============================
//�_���[�W�̐ݒ�
//============================
//bool CEnemy001::SetDamage(int damage)
//{
//	//�_���[�W�̐ݒ�
//	CEnemy::SetDamage(damage);
//
//	return true;
//}

//============================
//�_���[�W�̐ݒ�
//============================
bool CEnemy001::SetDamage(int damage, float angle)
{
	//�_���[�W���󂯂邩�̔���
	if (!m_bDamageJudge)
	{
		//��Βl�ɕϊ���Ɋp�x�̌덷���v�Z����
		float fAttackRot = angle;
		float fRot = GetRot().y;
		float fMin = angle - D3DX_PI * 0.5f;
		float fMax = angle + D3DX_PI * 0.5f;

		//��납��̍U���Ȃ�ʂ�
		if (fRot > fMin && fRot < fMax)
		{
			m_bDamageJudge = true;
		}
		else
		{
			return false;
		}
	}

	//���𗎂Ƃ�
	DropShield();

	//����t���Ă��Ȃ��Ȃ�_���[�W��Ԃ�
	if (!GetEnteredStick())
	{
		//��Ԃ̕ύX
		ChangeState(new CState_Enemy001_Damage(this));

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
//������я���
//============================
bool CEnemy001::SetBlowOff()
{
	//�q�b�g������
	bool bHit = false;
	
	//�A�N�V���������Ă��Ȃ��Ȃ琁����΂Ȃ�
	if (m_pShield != nullptr)
	{
		return bHit;
	}

	//���������Ă���Ȃ�
	if (m_pShield != nullptr)
	{
		m_pShield->Uninit();
		m_pShield = nullptr;
	}

	bHit = true;

	//�������Ă����琁�����
	if (bHit)
	{
		//���̐�����я���
		CEnemy::SetBlowOff();
		SetMotion(3);
	}

	return bHit;
}

//============================
//�_���[�W�e������
//============================
void CEnemy001::DamageEffect(CPlayer* player)
{
	if (!m_bDamageJudge)
	{
		if (m_pShield != nullptr)
		{
			//�G�t�F�N�g�̐���
			CEffect_Repel::Create(m_pShield->GetWorldPos());

			//SE�̐ݒ�
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_REPEL);
		}
		
		player->SetKnockBack(30);
	}
}