//======================================
//
//	�G�l�~�[�̏���[enemy.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "enemy.h"
#include "manager.h"
#include "game.h"
#include "enemy000.h"
#include "enemy001.h"
#include "enemy002.h"
#include "enemy003.h"
#include "state_enemy_damage.h"
#include "battleareamanager.h"
#include "effect_brow.h"
#include "effect_death.h"

//============================
//�G�l�~�[�̃R���X�g���N�^
//============================
CEnemy::CEnemy(int nPriority) : 
	CGame_Character(nPriority),	//�e�̃R���X�g���N�^
	m_EnemyType(),				//�G�̎��
	m_pState(nullptr),			//���
	m_bCollisionProcess(true)	//�����蔻����s����
{
	//�G�̎�ނ�ݒ�
	m_EnemyType = ENEMYTYPE_ENEMY000;

	//�Q�[���V�[���Ȃ画��
	if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
	{
		//�Q�[���V�[���̎擾
		CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

		//�}�l�[�W���[�ɓo�^
		pGame->GetEnemyManager()->Regist(this);
	}
}

//============================
//�G�l�~�[�̃f�X�g���N�^
//============================
CEnemy::~CEnemy()
{
	//�Q�[���V�[���Ȃ画��
	if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
	{
		//�Q�[���V�[���̎擾
		CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

		//�}�l�[�W���[����폜
		if (pGame->GetEnemyManager() != nullptr)
		{
			pGame->GetEnemyManager()->Erase(this);
		}

		if (pGame->GetLockon() != nullptr)
		{
			pGame->GetLockon()->Erase(this);
		}
	}

	//�G�̐������炷
	if (CBattleAreaManager::GetInstance()->GetCurrentBattleArea() != nullptr)
	{
		CBattleAreaManager::GetInstance()->GetCurrentBattleArea()->DecrementEnemyNum();
	}

	//��Ԃ̔j��
	if (m_pState != nullptr)
	{
		delete m_pState;
		m_pState = nullptr;
	}
}

//============================
//�G�l�~�[�̏�����
//============================
HRESULT CEnemy::Init()
{
	//������
	CGame_Character::Init();

	//�X�^�[�g�n�_��ۑ�
	m_StartPos = GetPos();

	return S_OK;
}

//============================
//�G�l�~�[�̏I������
//============================
void CEnemy::Uninit()
{
	//���S�t���O�������Ă����甲����
	if (GetDeath())
	{
		return;
	}

	//������
	CCharacter::Uninit();
}

//============================
//�G�l�~�[�̍X�V
//============================
void CEnemy::Update()
{
	//��Ԃɉ������X�V����
	if (m_pState != nullptr)
	{
		m_pState->Update(this);

		//���̃A�N�V����������Ȃ�ύX
		if (m_pState->GetNextState() != nullptr)
		{
			//���̃A�N�V�����ɕύX
			CState_Enemy* pNext = m_pState->GetNextState();
			delete m_pState;
			m_pState = nullptr;

			//���
			m_pState = pNext;
		}
	}

	//���ʏ����̍X�V
	CGame_Character::Update();
}

//============================
//�G�l�~�[�̕`��
//============================
void CEnemy::Draw()
{
	
}

//============================
//�G�l�~�[�̃N���G�C�g
//============================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, ENEMYTYPE type)
{
	//��ނɉ����ē��I�m��
	CEnemy* pEnemy = nullptr;

	switch (type)
	{
	case ENEMYTYPE_ENEMY000:	//�ʏ�̓G

		//�G�̃������m��
		pEnemy = new CEnemy000();
		break;

	case ENEMYTYPE_ENEMY001:	//�������̓G

	//�G�̃������m��
		pEnemy = new CEnemy001();
		break;

	case ENEMYTYPE_ENEMY002:	//�{�X�̓G

	//�G�̃������m��
		pEnemy = new CEnemy002();
		break;

	case ENEMYTYPE_ENEMY003:	//�ːi�̓G

	//�G�̃������m��
		pEnemy = new CEnemy003();
		break;
	}

	//�ʒu�̐ݒ�
	pEnemy->SetPos(pos);

	//������
	pEnemy->Init();

	//�ݒ肵������Ԃ�
	return pEnemy;
}

//============================
//�_���[�W�̐ݒ�
//============================
bool CEnemy::SetDamage(int damage, float angle)
{
	//�_���[�W�̐ݒ�
	CGame_Character::SetDamage(damage, angle);

	return true;
}

//============================
//������΂��ă_���[�W�̐ݒ�
//============================
bool CEnemy::SetBlowDamage(int damage, float rotY)
{
	//�������Ȃ��琁����΂�
	AddMove(D3DXVECTOR3(0.0f, VALUE_BLOWOFF, 0.0f));
	D3DXVECTOR3 Blow = { sinf(rotY + D3DX_PI) * VALUE_BLOWOFF, 0.0f, cosf(rotY + D3DX_PI) * VALUE_BLOWOFF };
	SetBlowValue(Blow);
	SetOnStand(false);
	CEnemy::SetDamage(damage, rotY);

	//�̗͂��Ȃ�������֐��𔲂���
	if (GetLife() <= 0)
	{
		return true;
	}

	//������я�ԂɕύX
	ChangeState(new CState_Enemy_Blow(this));

	//������ԃG�t�F�N�g
	CEffect_Brow::Create(GetCollision()->GetPos(), {0.0f, rotY, 0.0f});

	return true;
}

//============================
//������΂��ă_���[�W�̐ݒ�
//============================
bool CEnemy::SetBlowDamage(int damage, float rotY, float value)
{
	//�������Ȃ��琁����΂�
	AddMove(D3DXVECTOR3(0.0f, VALUE_BLOWOFF, 0.0f));
	D3DXVECTOR3 Blow = { sinf(rotY + D3DX_PI) * value, 0.0f, cosf(rotY + D3DX_PI) * value };
	SetBlowValue(Blow);
	SetOnStand(false);
	SetDamage(damage, rotY);

	//�̗͂��Ȃ�������֐��𔲂���
	if (GetLife() <= 0)
	{
		return true;
	}

	//������я�ԂɕύX
	ChangeState(new CState_Enemy_Blow(this));

	//������ԃG�t�F�N�g
	CEffect_Brow::Create(GetCollision()->GetPos(), { 0.0f, rotY, 0.0f });

	return true;
}

//============================
//������я���
//============================
bool CEnemy::SetBlowOff()
{
	//������ԏ���
	CCharacter::SetMove(D3DXVECTOR3(0.0f, VALUE_BLOWOFF, 0.0f));	//�ړ��ʂ̐ݒ�
	SetOnStand(false);												//�����Ă��Ȃ���Ԃɐݒ�
	SetEnableGravity(true);											//�d�͂��󂯂�

	return true;
}

//============================
//���S���̏���
//============================
void CEnemy::SetCharacterDeath()
{
	//�G�t�F�N�g�𐶐����Ĕj��
	CEffect_Death::Create(GetCollision()->GetPos());

	Uninit();
}

//============================
//��Ԃ̕ύX
//============================
void CEnemy::ChangeState(CState_Enemy* state)
{
	//�`�F�b�N��ɊJ��
	if (m_pState != nullptr)
	{
		delete m_pState;
	}
	
	m_pState = state;
}