//======================================
//
//	�L�����N�^�[�̏���[game_character.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "game_character.h"
#include "manager.h"
#include "game.h"
#include "battleareamanager.h"

//�萔�̐ݒ�
const float CGame_Character::GRAVITY = 0.6f;			//�d�͂̋���

//============================
//�L�����N�^�[�̃R���X�g���N�^
//============================
CGame_Character::CGame_Character(int nPriority) : CCharacter(nPriority)
{
	//�e�p�����[�^�̏�����
	m_nLife = 10;							//�̗�
	m_bOnStand = false;						//�������
	m_fRadiusSize = SIZE_RADIUS;			//�T�C�Y�̔��a
	m_bEnableGravity = true;				//�d�͂��󂯂�
	m_BlowValue = { 0.0f, 0.0f, 0.0f };		//������ԗ�

	//�����蔻��̐���
	if (m_pCollision == nullptr)
	{
		m_pCollision = CCollision::Create(GetSizeRadius(), D3DXVECTOR3(0.0f, 30.0f, 0.0f));
	}

	//�Q�[���^�O��ݒ�
	SetTag(CObject::TAG_GAME);
}

//============================
//�L�����N�^�[�̃f�X�g���N�^
//============================
CGame_Character::~CGame_Character()
{
	//�����蔻��̏���
	if (m_pCollision != nullptr)
	{
		m_pCollision->Uninit();
		m_pCollision = nullptr;
	}
}

//============================
//�L�����N�^�[�̏�����
//============================
HRESULT CGame_Character::Init()
{
	//������
	CCharacter::Init();

	//�����蔻��̈ʒu�̍X�V
	m_pCollision->Update(GetPos());

	return S_OK;
}

//============================
//�L�����N�^�[�̏I������
//============================
void CGame_Character::Uninit()
{
	//�I������
	CCharacter::Uninit();
}

//============================
//�L�����N�^�[�̍X�V
//============================
void CGame_Character::Update()
{
	//�ʒu�̍X�V
	UpdatePos();

	//�����̍X�V
	UpdateRot();

	//���[�V�����̍X�V
	UpdateMotion();

	//�����蔻��̈ʒu�̍X�V
	m_pCollision->Update(GetPos());
}

//============================
//�ʒu�̍X�V
//============================
void CGame_Character::UpdatePos()
{
	//�p�����[�^�̎擾
	D3DXVECTOR3 pos = CCharacter::GetPos();			//�ʒu
	D3DXVECTOR3 OldPos = CCharacter::GetOldPos();	//�O��̈ʒu
	D3DXVECTOR3 Move = CCharacter::GetMove();		//�ړ���

	//�O��̈ʒu��ۑ�
	OldPos = pos;

	//�d�͂̏���
	if (m_bEnableGravity)
	{
		Move = GravityMove(Move);
	}

	//�Q�[���V�[���Ȃ画��
	if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
	{
		//�Q�[���V�[���̎擾
		CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

		//�ʒu�Ɉړ��ʂ����Z
		pos += pGame->GetTime()->GetValue<D3DXVECTOR3>(Move);

		//�G���A�̊m�F
		if (CBattleAreaManager::GetInstance()->GetCurrentBattleArea() != nullptr)
		{
			//�ǂƂ̓����蔻��
			CBattleAreaManager::GetInstance()->GetCurrentBattleArea()->GetWall()->GetHit(pos, m_fRadiusSize);
		}

		//�����Ă��Ȃ��Ȃ�
		if (!m_bOnStand)
		{
			//�n�ʂɐڂ��Ă�����
			if (pGame->GetGameField()->MeshCollision(pos))
			{
				//�����Ă��锻��
				m_bOnStand = true;
			}
		}
		else
		{
			//�ʒu��␳
			pos = pGame->GetGameField()->ConvertMeshPos(pos);
		}
	}

	//������їʂ����Z
	pos += m_BlowValue;

	//������їʂ�����
	m_BlowValue.x += (0.0f - m_BlowValue.x) * 0.1f;
	m_BlowValue.z += (0.0f - m_BlowValue.z) * 0.1f;

	//�ړ��ʂ�����
	Move.x += (0.0f - Move.x) * 0.5f;
	Move.z += (0.0f - Move.z) * 0.5f;

	//�p�����[�^�̐ݒ�
	CCharacter::SetPos(pos);		//�ʒu
	CCharacter::SetOldPos(OldPos);	//�O��̈ʒu
	CCharacter::SetMove(Move);		//�ړ���
}

//============================
//�d�͂̏���
//============================
D3DXVECTOR3 CGame_Character::GravityMove(D3DXVECTOR3 move)
{
	//�󒆂ɂ���Ȃ�d�͂����Z
	if (!m_bOnStand)
	{
		//�Q�[���V�[���Ȃ画��
		if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
		{
			//�Q�[���V�[���̎擾
			CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

			move.y -= pGame->GetTime()->GetValue<float>(GRAVITY);
		}
	}
	else
	{
		//���n���Ă��ė����Ă�����␳
		if (move.y < 0.0f)
		{
			move.y = 0.0f;
		}
	}

	return move;
}

//============================
//�L�����N�^�[�̃_���[�W��ݒ�
//============================
bool CGame_Character::SetDamage(int damage, float angle)
{
	//�_���[�W���󂯂�
	m_nLife -= damage;

	//0�����Ȃ�0�ɂ���
	if (m_nLife <= 0)
	{
		m_nLife = 0;

		//���S���̏���
		SetCharacterDeath();
	}

	return true;
}

//============================
//���S���̏���
//============================
void CGame_Character::SetCharacterDeath()
{
	Uninit();
}

//============================
//�L�����N�^�[�̕`�揈��
//============================
void CGame_Character::Draw()
{
	CCharacter::Draw();
}