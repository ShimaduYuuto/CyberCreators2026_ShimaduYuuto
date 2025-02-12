//======================================
//
//	�v���C���[�̏���[player.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "player.h"
#include "manager.h"
#include "game.h"
#include "modelparts.h"
#include "camera.h"
#include "state_player_normal.h"
#include "state_player_damage.h"
#include "state_player_knockback.h"
#include "battleareamanager.h"
#include "barriermanager.h"
#include "state_player_death.h"

//�ÓI�����o�̏�����
const float CPlayer::DAMAGE_IMPULSE = 10.0f;
const std::string CPlayer::FILEPATH = "data\\MODEL\\player001.x";

//============================
//�v���C���[�̃R���X�g���N�^
//============================
CPlayer::CPlayer(int nPriority) : CGame_Character(nPriority),
	m_pLifeGauge(nullptr),
	m_pState(nullptr),
	m_bGuard(false)
{
	m_pState = new CState_Player_Normal(this);
	SetType(TYPE_PLAYER);	//��ނ̐ݒ�
}

//============================
//�v���C���[�̃f�X�g���N�^
//============================
CPlayer::~CPlayer()
{
	
}

//============================
//�v���C���[�̏�����
//============================
HRESULT CPlayer::Init()
{
	//������
	CGame_Character::Init();

	//�p�����[�^�̏�����
	CCharacter::SetRot({ 0.0f, 0.0f, 0.0f });
	CCharacter::SetPos({ 0.0f, 0.0f, 0.0f });
	CCharacter::SetGoalRot({ 0.0f, D3DX_PI, 0.0f });
	
	//���[�V�����̓ǂݍ���
	SetMotionInfo("data\\playermotion000.txt");

	//�Q�[�W�̐���
	if (m_pLifeGauge == nullptr)
	{
		m_pLifeGauge = CGauge_PlayerLife::Create(20);
	}

	//���̃��C�t�ݒ�
	SetLife(20);

	return S_OK;
}

//============================
//�v���C���[�̏I������
//============================
void CPlayer::Uninit()
{
	//������
	CGame_Character::Uninit();

	//�Q�[�W�̏���
	if (m_pLifeGauge != nullptr)
	{
		m_pLifeGauge->Uninit();
		m_pLifeGauge = nullptr;
	}

	//��Ԃ̏���
	if (m_pState != nullptr)
	{
		if (m_pState->GetBehavior() != nullptr)
		{
			//���̍s�����폜
			if (m_pState->GetBehavior()->GetNextBehavior() != nullptr)
			{
				delete m_pState->GetBehavior()->GetNextBehavior();
			}
		}

		//���̏�Ԃ�j��
		if (m_pState->GetNextState() != nullptr)
		{
			delete m_pState->GetNextState();
		}
		
		delete m_pState;
		m_pState = nullptr;
	}
}

//============================
//�v���C���[�̍X�V
//============================
void CPlayer::Update()
{
	//�Q�[���V�[���̎擾
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//���o���Ȃ�X�V���Ȃ�
	if (pGame->GetDirectioning())
	{
		return;
	}

	//��Ԃ̍X�V
	CPlayer::UpdateState();

	//�R���W�����̔���
	CPlayer::CollisionJudge();

	//���ʏ����̍X�V
	CGame_Character::Update();
}

//============================
//��Ԃ̍X�V
//============================
void CPlayer::UpdateState()
{
	//���̏�Ԃ�����Ȃ�ύX
	if (m_pState->GetNextState() != nullptr)
	{
		//���̏�ԂɕύX
		CState_Player* pNext = m_pState->GetNextState();
		delete m_pState;
		m_pState = nullptr;

		//���
		m_pState = pNext;
	}

	//��Ԃɉ������X�V����
	if (m_pState != nullptr)
	{
		m_pState->Update(this);

		//���̏�Ԃ�����Ȃ�ύX
		if (m_pState->GetNextState() != nullptr)
		{
			//���̏�ԂɕύX
			CState_Player* pNext = m_pState->GetNextState();
			delete m_pState;
			m_pState = nullptr;

			//���
			m_pState = pNext;
		}
	}
}

//============================
//�R���W�����̔���
//============================
void CPlayer::CollisionJudge()
{
	//�Q�[���V�[���̎擾
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//���E�Ƃ̓����蔻��
	for (auto itr : pGame->GetBarrierManager()->GetList())
	{
		//���̓����蔻��
		if (GetPos().z + 30.0f >= itr->GetPos().z)
		{
			GetPos().z = itr->GetPos().z - 30.0f;
		}
	}

	//�e�M�~�b�N�Ƃ̓����蔻��
	for (auto& iter : pGame->GetGimmickManager()->GetList())
	{
		//�ʒu�̎擾
		D3DXVECTOR3 GimmickPos = iter->GetCollision()->GetPos();
		D3DXVECTOR3 CharacterPos = GetCollision()->GetPos();

		//�������v�Z
		float fLength = sqrtf((CharacterPos.x - GimmickPos.x) * (CharacterPos.x - GimmickPos.x) + (CharacterPos.z - GimmickPos.z) * (CharacterPos.z - GimmickPos.z));
		float fTotalRadius = iter->GetCollision()->GetRadius() + GetCollision()->GetRadius();
		float fHeightLength = CharacterPos.y - GimmickPos.y;

		//�����̋������Βl�ɕύX
		if (fHeightLength < 0.0f) { fHeightLength *= -1.0f; }

		//�͈͓��̊m�F
		if (fLength < fTotalRadius && fHeightLength < fTotalRadius)
		{
			//�M�̓�����Ȃ��ʒu�ɕ␳
			float fAngle = atan2f(GimmickPos.x - CharacterPos.x, GimmickPos.z - CharacterPos.z);//�Ίp���̊p�x���Z�o

			//�ʒu�̐ݒ�
			SetPos(D3DXVECTOR3(sinf(fAngle + D3DX_PI) * fTotalRadius + GimmickPos.x,
				GetPos().y,
				cosf(fAngle + D3DX_PI) * fTotalRadius + GimmickPos.z));
		}
	}

	//�ʒu��␳
	if (GetPos().z < 0.0f)
	{
		GetPos().z = 0.0f;
	}

	if (GetPos().z > 4000.0f)
	{
		GetPos().z = 4000.0f;
	}
}

//============================
//�_���[�W���̏���
//============================
bool CPlayer::SetDamage(int damage, float angle)
{
	//�_���[�W�̐ݒ�
	return m_pState->SetDamage(this, damage, angle);
}

//============================
//�v���C���[�̕`��
//============================
void CPlayer::Draw()
{
	//�Q�[���V�[���̎擾
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//���o���Ȃ�X�V���Ȃ�
	if (pGame->GetDirectioning())
	{
		return;
	}
	//�L�����N�^�[�N���X�̕`��
	CCharacter::Draw();
}

//============================
//�v���C���[�̃N���G�C�g
//============================
CPlayer* CPlayer::Create()
{
	//�|�C���^�p�̕ϐ�
	CPlayer* pPlayer;

	//�������̊m��
	pPlayer = new CPlayer;

	//������
	pPlayer->Init();

	return pPlayer;
}

//============================
//�d�͂̏���
//============================
D3DXVECTOR3 CPlayer::GravityMove(D3DXVECTOR3 move)
{
	//�󒆂ɂ���Ȃ�d�͂����Z
	if (!GetOnStand())
	{
		//�d�͂̉��Z
		move.y -= GRAVITY;
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
//�ʒu�̍X�V
//============================
void CPlayer::UpdatePos()
{
	//�̗͂��Ȃ��Ȃ�X�V���Ȃ�
	if (GetLife() <= 0)
	{
		return;
	}

	//�p�����[�^�̎擾
	D3DXVECTOR3 pos = CObject::GetPos();	//�ʒu

	//�O��̈ʒu��ۑ�
	GetOldPos() = pos;

	//�d�͂̏���
	if (GetEnableGravity())
	{
		GetMove() = GravityMove(GetMove());
	}

	//�Q�[���V�[���Ȃ画��
	if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
	{
		//�Q�[���V�[���̎擾
		CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

		//�ړ��ʂ��ʒu�ɉ��Z
		pos += GetMove();

		//�G���A�̊m�F
		if (CBattleAreaManager::GetInstance()->GetCurrentBattleArea() != nullptr)
		{
			//�ǂƂ̓����蔻��
			CBattleAreaManager::GetInstance()->GetCurrentBattleArea()->GetWall()->GetHit(pos, GetSizeRadius());
		}

		//�����Ă��Ȃ��Ȃ�
		if (!GetOnStand())
		{
			//�n�ʂɐڂ��Ă�����
			if (pGame->GetGameField()->MeshCollision(pos))
			{
				//�����Ă��锻��
				SetOnStand(true);
			}
		}
		else
		{
			//�ʒu��␳
			pos = pGame->GetGameField()->ConvertMeshPos(pos);
		}

		//���̓����蔻��
		pos = pGame->GetGameField()->WidthCollision(pos);
	}

	//�ړ��ʂ�����
	GetMove().x += (0.0f - GetMove().x) * 0.5f;
	GetMove().z += (0.0f - GetMove().z) * 0.5f;

	//�p�����[�^�̐ݒ�
	CObject::SetPos(pos);	//�ʒu
}

//============================
//�m�b�N�o�b�N�̐ݒ�
//============================
void CPlayer::SetKnockBack(int time)
{
	SetMotion(PLAYERMOTION_KNOCKBACK);	//���[�V�����̐ݒ�

	//�m�b�N�o�b�N�̈ړ��ʂ�ݒ�
	D3DXVECTOR3 Rot = GetRot();
	D3DXVECTOR3 Move = GetMove();
	D3DXVECTOR3 AddMove = { sinf(Rot.y) * 10.0f, 0.0f, cosf(Rot.y) * 10.0f };

	//�ړ��ʂ̉��Z
	Move += AddMove;
	SetMove(Move);
	ChangeState(new CState_Player_Knockback(this));
}

//============================
//��Ԃ̐ݒ�
//============================
void CPlayer::SetState(CState_Player* state)
{
	//��Ԃ̕ύX
	delete m_pState;
	m_pState = state;
}

//============================
//���S���̏���
//============================
void CPlayer::SetCharacterDeath()
{
	ChangeState(new CState_Player_Death(this));
}

//============================
//��Ԃ̕ύX
//============================
void CPlayer::ChangeState(CState_Player* state)
{
	//�`�F�b�N��ɊJ��
	if (m_pState == nullptr)
	{
		delete m_pState;
		m_pState = nullptr;
	}

	m_pState = state;
}