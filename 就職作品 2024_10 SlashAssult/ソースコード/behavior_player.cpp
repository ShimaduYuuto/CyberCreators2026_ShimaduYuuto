//================================
//
//�v���C���[�̍s���܂Ƃ�[behavior_player.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "behavior_player.h"
#include "manager.h"
#include "game.h"
#include "gauge_slow.h"
#include "effect_hitattack.h"
#include "effect_runsmoke.h"
#include "state_player_normal.h"
#include "state_player_counter.h"
#include "state_player_guard.h"
#include "particle_rush.h"

//�萔
const D3DXVECTOR3 CPlayerBehavior_Attack::POS_OFFSET{ 0.0f, 20.0f, 30.0f };

//�e�s�����s�����Ƃ�������Ԃ�
bool TriggerJump(CPlayer* player);		//�W�����v��������
bool TriggerAttack();					//�U����������
bool TriggerDash();						//�_�b�V����������

//=========================
//�W�����v��������
//=========================
bool TriggerJump(CPlayer* player)
{
	if (!player->GetOnStand()) return false;													//�n��ɂ��Ȃ��Ȃ甲����
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_SPACE)) return true;				//�L�[�{�[�h�̔���
	if (CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_A)) return true;	//�W���C�p�b�h�̊m�F

	return false;
}

//=========================
//�U����������
//=========================
bool TriggerAttack()
{
	if (CManager::GetInstance()->GetMouse()->GetTrigger(CInputMouse::MOUSEBUTTON_LEFT)) return true;	//�L�[�{�[�h�̔���
	if (CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_X)) return true;			//�W���C�p�b�h�̊m�F

	return false;
}

//=========================
//�_�b�V����������
//=========================
bool TriggerDash()
{
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_LSHIFT)) return true;				//�L�[�{�[�h�̔���
	if (CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_LB)) return true;		//�W���C�p�b�h�̊m�F

	return false;
}

//================================================================
//�ړ�
//================================================================

//=========================
//�R���X�g���N�^
//=========================
CPlayerBehavior_Move::CPlayerBehavior_Move(CPlayer* player)
{
	player->SetEnableGravity(true);	//�d�͂��󂯂�
}

//=========================
//�s��(�ړ�)
//=========================
void CPlayerBehavior_Move::Behavior(CPlayer* player)
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 pos = player->GetPos();				//�ʒu�̎擾
	D3DXVECTOR3 goalrot = player->GetGoalRot();		//�ړI�̌����̎擾
	D3DXVECTOR3 move = player->GetMove();			//�ړ��ʂ̎擾

	//X�t�@�C���̓ǂݍ���
	CXfile* pCXfile = CManager::GetInstance()->GetXfile();

	//�W�����v
	if (TriggerJump(player))
	{//SPACE�������ꂽ�ꍇ
		move.y += JUMP_SPEED;
		player->SetOnStand(false);
		player->SetMotion(CPlayer::PLAYERMOTION_JUMP);
	}

	//�󒆂ɂ���Ȃ烂�[�V������ς���
	if(!player->GetOnStand() && player->GetMotionState() != CPlayer::PLAYERMOTION_JUMP)
	{
		//�W�����v�̃��[�V����
		player->SetMotion(CPlayer::PLAYERMOTION_JUMP);
	}

	//�ړ��ʂ̍X�V
	move += UpdateMove(player, goalrot);

	//�p�����[�^�̐ݒ�
	player->SetPos(pos);			//�ʒu
	player->SetGoalRot(goalrot);	//�ړI�̌���
	player->SetMove(move);			//�ړ���

	//�A�N�V��������
	Action(player);
}

//========================
//�ړ��̍X�V
//========================
D3DXVECTOR3 CPlayerBehavior_Move::UpdateMove(CPlayer* player, D3DXVECTOR3& Rotgoal)
{
	//�Ԃ��p�̕ϐ�
	D3DXVECTOR3 move = { 0.0f, 0.0f, 0.0f };
	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	//���������̔���p
	bool bMove = false;
	bool bPressKey = false;

	//�L�[�{�[�h�̍X�V����������
	if (CheckUpdateKeyboard(player, Rotgoal, &move))
	{
		bMove = true;
		bPressKey = true;
	}

	//�X�e�B�b�N���|��Ă����炻�̕����ɐi��
	if (CheckUpdateStick(bPressKey))
	{
		//�X�e�B�b�N�ł̍X�V
		UpdateStickMove(Rotgoal, &move);

		bMove = true;	//����������
	}

	//���������̔���
	if (bMove && player->GetOnStand())
	{
		//�������[�V������ݒ�
		if (player->GetMotionState() != CPlayer::PLAYERMOTION_WALK)
		{
			//���[�V�����̐ݒ�
			player->SetMotion(CPlayer::PLAYERMOTION_WALK);
		}
	}
	else if (player->GetOnStand())	//�n�ʂɒ����Ă���Ȃ�
	{
		//�j���[�g�������[�V������ݒ�
		if (player->GetMotionState() != CPlayer::PLAYERMOTION_NORMAL)
		{
			//���[�V�����̐ݒ�
			player->SetMotion(CPlayer::PLAYERMOTION_NORMAL);
		}
	}

	//�ړ��ʂ�Ԃ�
	return move;
}

//========================
//�L�[�{�[�h�̍X�V�m�F
//========================
bool CPlayerBehavior_Move::CheckUpdateKeyboard(CPlayer* player, D3DXVECTOR3& Rotgoal, D3DXVECTOR3* move)
{
	//����p
	bool bPressKey = false;
	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_A))
	{//A�L�[�������ꂽ�ꍇ
		if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_W))
		{
			move->x += sinf(D3DX_PI * -0.75f - pCamera->GetRot().y) * MOVE_SPEED;
			move->z -= cosf(D3DX_PI * -0.75f - pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = D3DX_PI * 0.75f + pCamera->GetRot().y;
		}
		else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_S))
		{
			move->x += sinf(D3DX_PI * -0.25f - pCamera->GetRot().y) * MOVE_SPEED;
			move->z -= cosf(D3DX_PI * -0.25f - pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = D3DX_PI * 0.25f + pCamera->GetRot().y;
		}
		else
		{
			move->x += sinf(D3DX_PI * -0.5f + pCamera->GetRot().y) * MOVE_SPEED;
			move->z += cosf(D3DX_PI * -0.5f + pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = -(D3DX_PI * -0.5f - pCamera->GetRot().y);
		}

		bPressKey = true;	//�L�[�{�[�h��G���Ă���
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_D))
	{//D�L�[�������ꂽ�ꍇ

		if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_W))
		{
			move->x += sinf(D3DX_PI * 0.75f - pCamera->GetRot().y) * MOVE_SPEED;
			move->z -= cosf(D3DX_PI * 0.75f - pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = D3DX_PI * -0.75f + pCamera->GetRot().y;
		}
		else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_S))
		{
			move->x += sinf(D3DX_PI * 0.25f - pCamera->GetRot().y) * MOVE_SPEED;
			move->z -= cosf(D3DX_PI * 0.25f - pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = D3DX_PI * -0.25f + pCamera->GetRot().y;
		}
		else
		{
			move->x += sinf(D3DX_PI * 0.5f + pCamera->GetRot().y) * MOVE_SPEED;
			move->z += cosf(D3DX_PI * 0.5f + pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = -(D3DX_PI * 0.5f - pCamera->GetRot().y);
		}

		bPressKey = true;	//�L�[�{�[�h��G���Ă���
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_W))
	{//W�L�[�������ꂽ�ꍇ
		{
			move->z -= cosf(D3DX_PI + pCamera->GetRot().y) * MOVE_SPEED;
			move->x -= sinf(D3DX_PI + pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = D3DX_PI + pCamera->GetRot().y;
		}

		bPressKey = true;	//�L�[�{�[�h��G���Ă���
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_S))
	{//S�L�[�������ꂽ�ꍇ
		{
			move->z -= cosf(pCamera->GetRot().y) * MOVE_SPEED;
			move->x -= sinf(pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = pCamera->GetRot().y;
		}

		bPressKey = true;	//�L�[�{�[�h��G���Ă���
	}

	return bPressKey;
}

//============================
//�X�e�B�b�N�ōX�V���ꂽ��
//============================
bool CPlayerBehavior_Move::CheckUpdateStick(bool pressed)
{
	float fDiameter = CManager::GetInstance()->GetJoypad()->GetStick().afTplDiameter[CInputJoypad::STICKTYPE_LEFT];	//�X�e�B�b�N�̓|���

	if (pressed) return false;				//�L�[�����łɉ�����Ă���Ȃ甲����
	if (fDiameter > 0.001f) return true;	//�X�e�B�b�N���|��Ă���Ȃ�^��Ԃ�

	return false;
}

//============================
//�X�e�B�b�N�ōX�V���ꂽ��
//============================
void CPlayerBehavior_Move::UpdateStickMove(D3DXVECTOR3& Rotgoal, D3DXVECTOR3* move)
{
	CCamera* pCamera = CManager::GetInstance()->GetCamera();												//�J�����̎擾
	float fAngle = CManager::GetInstance()->GetJoypad()->GetStick().afAngle[CInputJoypad::STICKTYPE_LEFT];	//�X�e�B�b�N�̊p�x���擾

	move->z += cosf(pCamera->GetRot().y + -fAngle + D3DX_PI) * MOVE_SPEED;	//X�����̈ړ�
	move->x += sinf(pCamera->GetRot().y + -fAngle + D3DX_PI) * MOVE_SPEED;	//Z�����̈ړ�
	Rotgoal.y = pCamera->GetRot().y + -fAngle;								//�i�s�����Ɍ���
}

//============================
//�v���C���[�̃A�N�V��������
//============================
void CPlayerBehavior_Move::Action(CPlayer* player)
{
	//���łɎ��̍s�������܂��Ă���Ȃ甲����
	if (GetNextBehavior() != nullptr) return;

	//���V�t�g�Ń_�b�V����ݒ�
	if (TriggerDash())
	{
		//�Q�[���V�[���Ȃ画��
		if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
		{
			//�Q�[���V�[���̎擾
			CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

			//���b�N�I������̊m�F
			if (pGame->GetLockon() != nullptr)
			{
				if (pGame->GetLockon()->GetTarget() != nullptr)
				{
					//�_�b�V���𐶐�
					SetNextBehavior(new CPlayerBehavior_Dash(player));
				}
			}
		}
	}

	//�����Ă�����
	if (player->GetOnStand())
	{
		//�E�N���b�N��������
		if (CManager::GetInstance()->GetMouse()->GetPress(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_RIGHT) || CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_RB))
		{
			//�K�[�h�𐶐�
			player->GetState()->SetNextState(new CState_Player_Guard(player));
			return;
		}
		else if (TriggerAttack())
		{
			//���[�V�����̐ݒ�
			player->SetMotion(CPlayer::PLAYERMOTION_ACTION);

			//�ʏ�U���𐶐�
			SetNextBehavior(new CPlayerBehavior_NormalAttack000(player));
		}
	}
	else //��
	{
		//���N���b�N��������
		if (TriggerAttack())
		{
			//���[�V�����̐ݒ�
			player->SetMotion(CPlayer::PLAYERMOTION_ACTION);

			//�󒆍U���ɐ؂�ւ�
			SetNextBehavior(new CPlayerBehavior_Arial000(player));
		}
		else if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_RIGHT))
		{
			//�Q�[���V�[���Ȃ画��
			if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
			{
				//�Q�[���V�[���̎擾
				CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

				//���b�N�I���̐ݒ�
				pGame->SetLockon(true);
			}
		}
	}
}

//================================================================
//�_�b�V��
//================================================================

//============================
//�R���X�g���N�^
//============================
CPlayerBehavior_Dash::CPlayerBehavior_Dash(CPlayer* player) :
	m_bFirst(true),
	m_DashSpeed()
{
	//�ݒ�
	player->SetMotion(CPlayer::PLAYERMOTION_JUMP);	//���[�V����
	player->SetOnStand(false);						//�����Ă��Ȃ����
	player->SetEnableGravity(false);				//�d�͂��󂯂Ȃ�
	player->GetPos().y += 0.01f;					//�ʒu�������グ��
}

//============================
//�s��(�_�b�V��)
//============================
void CPlayerBehavior_Dash::Behavior(CPlayer* player)
{
	//�����Ă���ԃ_�b�V������
	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_LSHIFT) ||
		CManager::GetInstance()->GetJoypad()->GetPress(CInputJoypad::JOYKEY_LB))
	{
		//�Ԃ��p�̕ϐ�
		D3DXVECTOR3 move = { 0.0f, 0.0f, 0.0f };

		//�Q�[���V�[���Ȃ画��
		if (CManager::GetInstance()->GetScene()->GetMode() != CManager::GetInstance()->GetScene()->MODE_GAME)
		{
			return;
		}

		//�Q�[���V�[���̎擾
		CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

		//���b�N�I������̊m�F
		if (pGame->GetLockon() == nullptr)
		{
			return;
		}

		if (pGame->GetLockon()->GetTarget() != nullptr)
		{
			//�^�[�Q�b�g�Ƃ̋������Z�o
			D3DXVECTOR3 TagPos = pGame->GetLockon()->GetTarget()->GetPos();
			D3DXVECTOR3 Length = TagPos - player->GetPos();
			float fLength = sqrtf((Length.x * Length.x) + (Length.z * Length.z));
			fLength = D3DXVec3Length(&Length);	//�������Z�o
			float fAngle = atan2f(TagPos.x - player->GetPos().x, TagPos.z - player->GetPos().z);

			//���b�N�I���̕��Ɍ�����
			player->SetGoalRot({ 0.0f, fAngle + D3DX_PI, 0.0f });

			//�G���痣��Ă���Ȃ�_�b�V��
			if (fLength > STOP_LENGYH)
			{
				//���߂Ēʂ�Ȃ瑬�x���Z�o
				if (m_bFirst)
				{
					//���`��Ԃ̒l���Z�o
					m_DashSpeed = Length * RATIO_LINEAR_INTERPOLATION;
					m_bFirst = false;
				}
				//�^�[�Q�b�g�Ƀ_�b�V��
				move.x = m_DashSpeed.x;
				move.y = m_DashSpeed.y;
				move.z = m_DashSpeed.z;

				//effect
				CEffect_RunSmoke::Create(player->GetPos());
			}

			//�~�܂鋗���ɂȂ�����U��
			if (fLength < STOP_LENGYH)
			{
				//�ړ���Ԃɂ���
				SetNextBehavior(new CPlayerBehavior_DashAttack000(player));
			}
		}
		else
		{
			//�ړ���Ԃɂ���
			SetNextBehavior(new CPlayerBehavior_Move(player));
		}

		//�ړ��ʂ̐ݒ�
		player->SetMove({ move.x , move.y, move.z });
	}
	else if(CManager::GetInstance()->GetKeyboard()->GetRerease(DIK_LSHIFT) ||
			CManager::GetInstance()->GetJoypad()->GetRerease(CInputJoypad::JOYKEY_LB)) //��������_�b�V�����I��
	{
		//�ړ���Ԃɂ���
		SetNextBehavior(new CPlayerBehavior_Move(player));
	}
}

//================================================================
//�U��
//================================================================

//============================
//�R���X�g���N�^
//============================
CPlayerBehavior_Attack::CPlayerBehavior_Attack() :
	m_fAttackLength(0.0f),				//�U���̋���
	m_HitEnemy(),						//�q�b�g�����G�̃��X�g
	m_nCancelStartTime(0),				//�L�����Z������
	m_nCollisionlTime(0),				//�����蔻��̔�������
	m_nEndCount(0),						//�I���J�E���g
	m_nEndTime(0),						//�I������
	m_OffsetPos({0.0f, 0.0f, 0.0f}),	//�I�t�Z�b�g�ʒu
	m_bCancel(false)					//�L�����Z������
{
	//�p�����[�^�̐ݒ�
	SetEndTime(END_TIME);				//�I������
	SetCollisionTime(START_COLLISION);	//�����蔻��̎���
	SetCancelTime(START_CANCEL);		//�L�����Z���J�n����
	SetAttackLength(ATTACK_LENGTH);		//�U���̋���
	SetOffsetPos(POS_OFFSET);			//�I�t�Z�b�g�ʒu
}

//============================
//�R���X�g���N�^
//============================
CPlayerBehavior_Attack::CPlayerBehavior_Attack(CPlayer* player) :
	m_fAttackLength(0.0f),		//�U���̋���
	m_HitEnemy(),				//�q�b�g�����G�̃��X�g
	m_nCancelStartTime(0),		//�L�����Z������
	m_nCollisionlTime(0),		//�����蔻��̔�������
	m_nEndCount(0),				//�I���J�E���g
	m_nEndTime(0),				//�I������
	m_bCancel(false)			//�L�����Z������
{
	//�p�����[�^�̐ݒ�
	SetEndTime(END_TIME);				//�I������
	SetCollisionTime(START_COLLISION);	//�����蔻��̎���
	SetCancelTime(START_CANCEL);		//�L�����Z���J�n����
	SetAttackLength(ATTACK_LENGTH);		//�U���̋���
	SetOffsetPos(POS_OFFSET);			//�I�t�Z�b�g�ʒu

	//SE��炷
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SWING);
}

//============================
//�f�X�g���N�^
//============================
CPlayerBehavior_Attack::~CPlayerBehavior_Attack()
{
	m_HitEnemy.clear();
}

//============================
//�G�̕�������
//============================
void CPlayerBehavior_Attack::LookAtEnemy(CPlayer* player)
{
	//�Q�[���V�[���̎擾
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//�G������������
	bool bHit = false;

	//�ۑ�������
	D3DXVECTOR3 GoalEnemyPos = { VEC3_RESET_ZERO };
	float ShortLength = 100.0f;
	float fSaveAngleDifference = D3DX_PI;

	//�G�̎���
	for (auto& iter : pGame->GetEnemyManager()->GetList())
	{
		//�ʒu�̏����X�V
		D3DXVECTOR3 PlayerPos = player->GetPos();
		D3DXVECTOR3 EnemyLength = iter->GetCollision()->GetPos() - PlayerPos;

		float fXZ = sqrtf(EnemyLength.x * EnemyLength.x + EnemyLength.z * EnemyLength.z); //XZ�������Z�o����
		float fXY = sqrtf(EnemyLength.x * EnemyLength.x + EnemyLength.y * EnemyLength.y); //XY�������Z�o����
		float fLength = sqrtf(fXZ * fXZ + fXY * fXY);	//�������Z�o

		//���߂��G����������X�V
		if (fLength < ShortLength)
		{
			//�v���C���[�̌����Ă�������ɂ��邩�𔻒f
			float fPlayerAngle = player->GetRot().y;
			D3DXVECTOR3 Length = iter->GetPos() - player->GetPos();
			float fAngle = atan2f(-Length.x, -Length.z)/* + D3DX_PI*/;
			
			if (CheckEnemyInFront(player, fAngle, D3DX_PI))
			{
				float fAngleDifference = CheckAngleDiff(fPlayerAngle, fAngle);

				if (fAngleDifference < fSaveAngleDifference)
				{
					//����ۑ�
					fSaveAngleDifference = fAngleDifference;
					ShortLength = fLength;
					GoalEnemyPos = iter->GetPos();
					bHit = true;
				}
			}
		}
	}

	//�ǔ�����G���������炻����������
	if (bHit)
	{
		D3DXVECTOR3 Length = GoalEnemyPos - player->GetPos();
		float fAngle = atan2f(Length.x, Length.z);
		player->SetGoalRot({ 0.0f, fAngle + D3DX_PI, 0.0f });
	}
}

//============================
//�O���ɓG�����邩�̊m�F
//============================
bool CPlayerBehavior_Attack::CheckEnemyInFront(CPlayer* player, float targetangle, float radian)
{
	float fPlayerRot = player->GetRot().y;
	float fRot = targetangle;
	float fMin = fPlayerRot - radian * 0.5f;
	float fMax = fPlayerRot + radian * 0.5f;

	//��납��̍U���Ȃ�ʂ�
	if (fRot > fMin && fRot < fMax)
	{
		return true;
	}

	return false;
}

//============================
//�U���s��
//============================
void CPlayerBehavior_Attack::Behavior(CPlayer* player)
{
	//�����蔻��
	if (IsHitProcess())
	{
		//�Q�[���V�[���̎擾
		CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

		//�U������̐���
		D3DXVECTOR3 AttackPos = player->GetPos();
		AttackPos += {sinf(player->GetRot().y + D3DX_PI)* m_OffsetPos.z, m_OffsetPos.y, cosf(player->GetRot().y + D3DX_PI)* m_OffsetPos.z};

		//�G�Ƃ̓����蔻��
		HitEnemyProcess(player, AttackPos);

		//�e�Ƃ̓����蔻��
		HitBulletProcess(player, AttackPos);

		//�L�����Z���̃J�E���g�ȏ�ɂȂ�����
		if (m_nEndCount > m_nCancelStartTime && m_bCancel)
		{
			//�L�����Z���̏���
			Cancel(player);
		}
	}

	//��s���͂̎�t
	if (m_nEndCount > m_nCancelStartTime - TYPE_AHEAD)
	{
		CancelInput();
	}

	//�I�����ԂɂȂ�����s�����ړ��ɕύX
	if (m_nEndCount >= m_nEndTime)
	{
		if (GetNextBehavior() == nullptr)
		{
			//���̍s����ݒ�
			NextBehavior(player);
		}
	}

	//�J�E���g�̍X�V
	m_nEndCount++;

	//�G�t�F�N�g����
	Effect(player);
}

//============================
//�����蔻����s����
//============================
bool CPlayerBehavior_Attack::IsHitProcess()
{
	//�e����
	if (m_nEndCount <= m_nCollisionlTime) return false;	//�J�E���g�������蔻����s�����Ԃ���Ȃ��Ȃ甲����
	if (CManager::GetInstance()->GetScene()->GetMode() !=
		CManager::GetInstance()->GetScene()->MODE_GAME)return false;	//�Q�[���V�[������Ȃ��Ȃ甲����

	return true;
}

//============================
//�G�Ƃ̓����蔻��
//============================
void CPlayerBehavior_Attack::HitEnemyProcess(CPlayer* player, D3DXVECTOR3 pos)
{
	//�Q�[���V�[���̎擾
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//�G�̎���
	for (auto& iter : pGame->GetEnemyManager()->GetList())
	{
		//����������
		bool bHit = false;

		//���łɓ������Ă��邩���m�F
		for (auto& HitEnemyiter : m_HitEnemy)
		{
			//���łɓ������Ă����甲����
			if (HitEnemyiter == iter)
			{
				bHit = true;	//���łɓ������Ă���
				break;
			}
		}

		//���łɓ������Ă������΂�
		if (bHit)
		{
			continue;
		}

		//�G�̈ʒu���擾
		D3DXVECTOR3 EnemyLength = iter->GetCollision()->GetPos() - pos;

		float fXZ = sqrtf(EnemyLength.x * EnemyLength.x + EnemyLength.z * EnemyLength.z); //XZ�������Z�o����
		float fXY = sqrtf(EnemyLength.x * EnemyLength.x + EnemyLength.y * EnemyLength.y); //XY�������Z�o����
		float fLength = sqrtf(fXZ * fXZ + fXY * fXY);	//�������Z�o

		//�G�̔�����Ȃ�
		if (fLength < m_fAttackLength)
		{
			//�_���[�W����
			Damage(player, iter, 1);

			//�G�̈ړ��ʂ��擾
			D3DXVECTOR3 Move = iter->CCharacter::GetMove();

			//�����Ă�����ړ��ʂ�߂�
			if (Move.y < 0.0f)
			{
				Move.y = 0.0f;
			}

			//�ݒ�
			iter->CCharacter::SetMove(Move);

			//�G�̏���ۑ�
			m_HitEnemy.push_back(iter);
		}
	}
}

//============================
//�e�Ƃ̓����蔻��
//============================
void CPlayerBehavior_Attack::HitBulletProcess(CPlayer* player, D3DXVECTOR3 pos)
{
	//�Q�[���V�[���̎擾
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//�e�Ƃ̓����蔻��
	for (auto& iter : pGame->GetEnemyBulletManager()->GetList())
	{
		//���ˍς݂͔�΂�
		if (iter->GetReflection() || !iter->GetShooting())
		{
			continue;
		}

		//�G�̈ʒu���擾
		D3DXVECTOR3 Length = iter->GetCollision()->GetPos() - pos;

		float fXZ = sqrtf(Length.x * Length.x + Length.z * Length.z); //XZ�������Z�o����
		float fXY = sqrtf(Length.x * Length.x + Length.y * Length.y); //XY�������Z�o����
		float fLength = sqrtf(fXZ * fXZ + fXY * fXY);	//�������Z�o
		D3DXVECTOR3 Distance = iter->GetPos() - pos;
		float fAngle = atan2f(Distance.x, Distance.z);

		//�G�̔�����Ȃ�
		if (fLength < m_fAttackLength + iter->GetCollision()->GetRadius())
		{
			//�e�𔽎�
			iter->Reflection(player->GetRot().y);
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_REPEL);	//SE
		}
	}
}

//============================
//�_���[�W��^���鏈��
//============================
void CPlayerBehavior_Attack::Damage(CPlayer* player, CEnemy* enemy, int damage)
{
	//�_���[�W���^����ꂽ��q�b�g����
	if (enemy->SetDamage(damage, player->GetRot().y))
	{
		//�q�b�g���̏���
		CEffect_HitAttack::Create(enemy->GetCollision()->GetPos());
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_ATTACK);
	}

	//�_���[�W���^�����Ȃ�������G�̌��ʂ��󂯂�
	else
	{
		enemy->DamageEffect(player);
	}
}

//============================
//���̍s��(�ړ�)
//============================
void CPlayerBehavior_Attack::NextBehavior(CPlayer* player)
{
	SetNextBehavior(new CPlayerBehavior_Move(player));
}

//============================
//�U���{�^������͂�����
//============================
bool CPlayerBehavior_Attack::TriggerAttack()
{
	if (CManager::GetInstance()->GetMouse()->GetTrigger(CInputMouse::MOUSEBUTTON_LEFT)) return true;	//�}�E�X
	if (CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_X)) return true;			//�W���C�p�b�h

	return false;
}

//============================
//�L�����Z�����͂̏���
//============================
void CPlayerBehavior_Attack::CancelInput()
{
	if (TriggerAttack())
	{
		m_bCancel = true;
	}
}

//============================
//�G�t�F�N�g�̏���
//============================
void CPlayerBehavior_Attack::Effect(CPlayer* player)
{
	//���f���p�[�c�̎擾
	CModelparts* pModelParts = player->GetModelParts(15);

	//�I�t�Z�b�g�ʒu�̐ݒ�
	D3DXVECTOR3 OffsetPos = { 0.0f, ORBIT_OFFSET_LENGTH, 0.0f };
	D3DXVec3TransformCoord(&OffsetPos, &OffsetPos, &pModelParts->GetMtx());

	//�p�[�e�B�N���̐���
	CParticle_Rush::Create(OffsetPos, player->GetRot());
}

//================================================================
//�ʏ�U��(���N���X)
//================================================================

//============================
//�ʏ�U��
//============================
void CPlayerBehavior_NormalAttack::Behavior(CPlayer* player)
{
	//�ړ��ʂ����Z���鎞��
	if (GetCount() < END_MOVE)
	{
		//�Q�[���V�[���̎擾
		CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

		//�ړ��ʂ����Z
		D3DXVECTOR3 Move = player->GetMove();
		D3DXVECTOR3 Rot = player->GetRot();

		//�v�Z���ĉ��Z
		Move += { sinf(Rot.y + D3DX_PI)* VALUE_MOVE, 0.0f, cosf(Rot.y + D3DX_PI)* VALUE_MOVE };
		pGame->GetGamePlayer()->SetMove(Move);
	}

	//�U���̏���
	CPlayerBehavior_Attack::Behavior(player);
}

//================================================================
//�ʏ�U��(1�i��)
//================================================================

//============================
//�R���X�g���N�^
//============================
CPlayerBehavior_NormalAttack000::CPlayerBehavior_NormalAttack000(CPlayer* player) : CPlayerBehavior_NormalAttack(player)
{
	//�G�̕���������
	LookAtEnemy(player);

	//���[�V�����̐ݒ�
	player->SetMotion(CPlayer::PLAYERMOTION_ACTION);
}

//============================
//�L�����Z��
//============================
void CPlayerBehavior_NormalAttack000::Cancel(CPlayer* player)
{
	//���̍U���̐���
	SetNextBehavior(new CPlayerBehavior_NormalAttack001(player));
}

//================================================================
//�ʏ�U��(2�i��)
//================================================================

//============================
//�R���X�g���N�^
//============================
CPlayerBehavior_NormalAttack001::CPlayerBehavior_NormalAttack001(CPlayer* player) : CPlayerBehavior_NormalAttack(player)
{
	//���[�V�����̐ݒ�
	player->SetMotion(CPlayer::PLAYERMOTION_ACTION001);
}

//============================
//�L�����Z��
//============================
void CPlayerBehavior_NormalAttack001::Cancel(CPlayer* player)
{
	//���̍U���̐���
	SetNextBehavior(new CPlayerBehavior_NormalAttack002(player));
}

//================================================================
//�ʏ�U��(3�i��)
//================================================================

//============================
//�R���X�g���N�^
//============================
CPlayerBehavior_NormalAttack002::CPlayerBehavior_NormalAttack002(CPlayer* player) : CPlayerBehavior_NormalAttack(player),
	m_bChargeEnd(false),			//�`���[�W�I���t���O
	m_fChargeRate(0.5f),			//�`���[�W�{��
	m_fChargeAcceleration(0.0f),	//�`���[�W�����x
	m_nCancelCount(0),				//�L�����Z���J�E���g
	m_pEffect(nullptr)				//�G�t�F�N�g�̃|�C���^
{
	//���[�V�����̐ݒ�
	player->SetMotion(player->PLAYERMOTION_ATTACKCHARGE);

	//�p�����[�^�̐ݒ�
	SetEndTime(END_TIME);
	SetCollisionTime(START_COLLISION);
	SetCancelTime(START_CANCEL);
	SetAttackLength(ATTACK_LENGTH);
	SetOffsetPos(POS_OFFSET);

	//SE���~�߂�
	CManager::GetInstance()->GetSound()->Stop(CSound::SOUND_LABEL_SWING);
}

//============================
//�f�X�g���N�^
//============================
CPlayerBehavior_NormalAttack002::~CPlayerBehavior_NormalAttack002()
{
	//�G�t�F�N�g�̔j��
	if (m_pEffect != nullptr)
	{
		m_pEffect->Uninit();
		m_pEffect = nullptr;
	}

	CManager::GetInstance()->GetSound()->Stop(CSound::SOUND_LABEL_CHARGE000);
}

//============================
//�s��(�U��)
//============================
void CPlayerBehavior_NormalAttack002::Behavior(CPlayer* player)
{
	if (!m_bChargeEnd)
	{
		//�L�����Z���J�E���g�̉��Z
		if (m_nCancelCount < ACCEPT_CANCELTIME)
		{
			m_nCancelCount++;

			//�`���[�W�U���ɑJ�ڂ��鎞�Ԃ܂ŗ��߂���G�t�F�N�g�𐶐�
			if (m_nCancelCount >= ACCEPT_CANCELTIME)
			{
				m_pEffect = CEffect_Charge::Create(player->GetCollision()->GetPos());

				//SE�̐���
				CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_CHARGE000);
			}
		}

		//�}�b�N�X�܂Ń`���[�W
		if (m_fChargeRate < MAX_RATE)
		{
			m_fChargeAcceleration += ACCELERATION_VALUE;
			m_fChargeRate += m_fChargeAcceleration;
		}

		//�U���{�^���𗣂��Ă���Ȃ�U��
		if ((!CManager::GetInstance()->GetMouse()->GetPress(CInputMouse::MOUSEBUTTON_LEFT) && !CManager::GetInstance()->GetJoypad()->GetPress(CInputJoypad::JOYKEY_X)) || m_fChargeRate >= MAX_RATE)
		{
			//�L�����Z�����Ԍ�ɗ�������`���[�W
			if (m_nCancelCount >= ACCEPT_CANCELTIME)
			{
				//�U�����[�V����
				player->SetMotion(player->PLAYERMOTION_CHARGEATTACK);

				//�`���[�W���I�������
				m_bChargeEnd = true;

				//�e�p�����[�^�̐ݒ�
				SetAttackLength(ATTACK_LENGTH * (m_fChargeRate * 0.01f));
				SetOffsetPos(D3DXVECTOR3(POS_OFFSET.x, POS_OFFSET.y, POS_OFFSET.z * (m_fChargeRate * 0.01f)));
			}
			else
			{
				//�U�����[�V����
				player->SetMotion(CPlayer::PLAYERMOTION_ACTION002);
			}

			//�G�t�F�N�g�̔j��
			if (m_pEffect != nullptr)
			{
				m_pEffect->Uninit();
				m_pEffect = nullptr;
			}

			//�`���[�W���I�������
			m_bChargeEnd = true;
			CManager::GetInstance()->GetSound()->Stop(CSound::SOUND_LABEL_CHARGE000);
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SWING);
		}
	}
	//�`���[�W���I����Ă�����U��
	else
	{
		//�ʏ�U��
		CPlayerBehavior_NormalAttack::Behavior(player);
	}
}

//============================
//�_���[�W��^���鏈��
//============================
void CPlayerBehavior_NormalAttack002::Damage(CPlayer* player, CEnemy* enemy, int damage)
{
	//�q�b�g������
	bool bHit = false;

	//�L�����Z���J�E���g�̉��Z
	if (m_nCancelCount < ACCEPT_CANCELTIME)
	{
		bHit = enemy->SetBlowDamage(damage, player->GetRot().y);
	}
	else
	{
		//�_���[�W
		bHit = enemy->SetBlowDamage(damage * 3, player->GetRot().y, m_fChargeRate * 0.5f);
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_CHARGEATTACK);
	}

	//�q�b�g���̏���
	if (bHit)
	{
		CEffect_HitAttack::Create(enemy->GetCollision()->GetPos());
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_ATTACK);
	}
}

//=================================================
//�󒆍U��(1�i��)
//=================================================

//============================
//�R���X�g���N�^
//============================
CPlayerBehavior_Arial000::CPlayerBehavior_Arial000(CPlayer* player)
{
	//��{�̐ݒ�
	player->SetMotion(CPlayer::PLAYERMOTION_ARIAL000);	//���[�V����
	player->SetEnableGravity(false);					//�d�͂��󂯂Ȃ�
	player->SetMove({ player->GetMove().x, 0.0f, player->GetMove().z });	//Y�����̈ړ��ʂ𖳂���
}

//============================
//�L�����Z������
//============================
void CPlayerBehavior_Arial000::Cancel(CPlayer* player)
{
	//���̍U���̐���
	SetNextBehavior(new CPlayerBehavior_Arial001(player));
}

//============================
//�s������(�U��)
//============================
void CPlayerBehavior_Arial000::Behavior(CPlayer* player)
{
	//�U���̊��s��
	CPlayerBehavior_Attack::Behavior(player);
}

//=================================================
//�󒆍U��(2�i��)
//=================================================

//============================
//�R���X�g���N�^
//============================
CPlayerBehavior_Arial001::CPlayerBehavior_Arial001(CPlayer* player)
{
	//���[�V�����̐ݒ�
	player->SetMotion(CPlayer::PLAYERMOTION_ARIAL001);
}

//============================
//�L�����Z������
//============================
void CPlayerBehavior_Arial001::Cancel(CPlayer* player)
{
	//���̍U���̐���
	SetNextBehavior(new CPlayerBehavior_Arial002(player));
}

//============================
//�s������(�U��)
//============================
void CPlayerBehavior_Arial001::Behavior(CPlayer* player)
{
	//�U���̊��s��
	CPlayerBehavior_Attack::Behavior(player);
}

//=================================================
//�󒆍U��(3�i��)
//=================================================

//============================
//�R���X�g���N�^
//============================
CPlayerBehavior_Arial002::CPlayerBehavior_Arial002(CPlayer* player)
{
	//���[�V�����̐ݒ�
	player->SetMotion(CPlayer::PLAYERMOTION_ARIAL002);
}

//============================
//�s������(�U��)
//============================
void CPlayerBehavior_Arial002::Behavior(CPlayer* player)
{
	//�U���̊��s��
	CPlayerBehavior_Attack::Behavior(player);
}

//=================================================
//�_�b�V���U��(���)
//=================================================

//============================
//�R���X�g���N�^
//============================
CPlayerBehavior_DashAttack::CPlayerBehavior_DashAttack(CPlayer* player) : CPlayerBehavior_Attack(player),
	m_RushContinue(false)
{
	//�p�����[�^�̐ݒ�
	SetCancelTime(START_CANCELTIME);	//�L�����Z��
	SetEndTime(END_TIME);				//�I������
	SetCollisionTime(START_COLLISION);	//�����蔻��
	SetAttackLength(ATTACK_LENGTH);		//�U���̋���

	//���b�V��������Q�[���V�[���ɐݒ�
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());
	pGame->SetRushJudge(true);
}

//============================
//�f�X�g���N�^
//============================
CPlayerBehavior_DashAttack::~CPlayerBehavior_DashAttack()
{
	//���b�V��������Q�[���V�[���ɐݒ�
	if (!m_RushContinue)
	{
		CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());
		pGame->SetRushJudge(false);
	}
}

//============================
//�s������(�U��)
//============================
void CPlayerBehavior_DashAttack::Behavior(CPlayer* player)
{
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//���b�V������̊m�F
	if (!pGame->GetRushJudge())
	{
		pGame->SetRushJudge(true);
	}

	//���f���p�[�c�̎擾
	CModelparts* pModelParts = player->GetModelParts(15);

	//�I�t�Z�b�g�ʒu�̐ݒ�
	D3DXVECTOR3 OffsetPos = { 0.0f, ORBIT_OFFSET_LENGTH, 0.0f };
	D3DXVec3TransformCoord(&OffsetPos, &OffsetPos, &pModelParts->GetMtx());

	//�U������
	CPlayerBehavior_Attack::Behavior(player);
}

//=================================================
//�_�b�V���U��(1�i��)
//=================================================

//============================
//�R���X�g���N�^
//============================
CPlayerBehavior_DashAttack000::CPlayerBehavior_DashAttack000(CPlayer* player) : CPlayerBehavior_DashAttack(player)
{
	//��{�̐ݒ�
	player->SetMotion(CPlayer::PLAYERMOTION_ARIAL000);					//���[�V����
	player->SetEnableGravity(false);									//�d�͂��󂯂Ȃ�
	player->SetMove({ player->GetMove().x, 0.0f, player->GetMove().z });//Y�����̈ړ��ʂ𖳂���
}

//============================
//�L�����Z������
//============================
void CPlayerBehavior_DashAttack000::Cancel(CPlayer* player)
{
	//�Q�[���V�[���̎擾
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//���b�N�I������̊m�F
	if (pGame->GetLockon() != nullptr)
	{
		if (pGame->GetLockon()->GetTarget() != nullptr)
		{
			//�^�[�Q�b�g�Ƀ_�b�V��
			D3DXVECTOR3 TagPos = pGame->GetLockon()->GetTarget()->GetPos();
			D3DXVECTOR3 Length = TagPos - player->GetPos();
			float fLength = sqrtf((Length.x * Length.x) + (Length.z * Length.z));
			fLength = D3DXVec3Length(&Length);	//�������Z�o

			//�U���͈̔͊O�Ȃ�_�b�V������
			if (fLength > CPlayerBehavior_Dash::STOP_LENGYH)
			{
				SetNextBehavior(new CPlayerBehavior_Move(player));
			}
			else
			{
				//���̍U���̐���
				SetNextBehavior(new CPlayerBehavior_DashAttack001(player));
				SetRushContinue(true);
			}
		}
	}
}

//============================
//�s������(�U��)
//============================
void CPlayerBehavior_DashAttack000::Behavior(CPlayer* player)
{
	//�_�b�V���U��
	CPlayerBehavior_DashAttack::Behavior(player);
}

//=================================================
//�_�b�V���U��(2�i��)
//=================================================

//============================
//�R���X�g���N�^
//============================
CPlayerBehavior_DashAttack001::CPlayerBehavior_DashAttack001(CPlayer* player) : CPlayerBehavior_DashAttack(player)
{
	//���[�V�����̐ݒ�
	player->SetMotion(CPlayer::PLAYERMOTION_ARIAL001);
}

//============================
//�L�����Z������
//============================
void CPlayerBehavior_DashAttack001::Cancel(CPlayer* player)
{
	//�Q�[���V�[���̎擾
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//���b�N�I������̊m�F
	if (pGame->GetLockon() != nullptr)
	{
		if (pGame->GetLockon()->GetTarget() != nullptr)
		{
			//�^�[�Q�b�g�Ƀ_�b�V��
			D3DXVECTOR3 TagPos = pGame->GetLockon()->GetTarget()->GetPos();
			D3DXVECTOR3 Length = TagPos - player->GetPos();
			float fLength = sqrtf((Length.x * Length.x) + (Length.z * Length.z));
			fLength = D3DXVec3Length(&Length);	//�������Z�o

			//�U���͈̔͊O�Ȃ�_�b�V������
			if (fLength > CPlayerBehavior_Dash::STOP_LENGYH)
			{
				SetNextBehavior(new CPlayerBehavior_Move(player));
			}
			else
			{
				//���̍U���̐���
				SetNextBehavior(new CPlayerBehavior_DashAttack000(player));
				SetRushContinue(true);
			}
		}
	}
}

//============================
//�s������(�U��)
//============================
void CPlayerBehavior_DashAttack001::Behavior(CPlayer* player)
{
	//�_�b�V���U��
	CPlayerBehavior_DashAttack::Behavior(player);
}

//=================================================
//�K�[�h
//=================================================

//============================
//�R���X�g���N�^
//============================
CPlayerBehavior_Guard::CPlayerBehavior_Guard(CPlayer* player) : m_nStiffnessCount(0)
{
	//��{�̏���
	player->SetMotion(CPlayer::PLAYERMOTION_GUARD);	//���[�V����
	player->SetGuardJudge(true);					//�K�[�h�����Ă��邩
}

//============================
//�s������(�K�[�h)
//============================
void CPlayerBehavior_Guard::Behavior(CPlayer* player)
{
	//�d�����Ԃ��߂��Ă����甲����
	if (m_nStiffnessCount <= TIME_FIRST_STIFFNESS)
	{
		m_nStiffnessCount++;
	}

	//�����d�����Ԃ��߂�����d������߂�
	if (m_nStiffnessCount > TIME_FIRST_STIFFNESS)
	{
		m_bStiffening = false;

		//���N���b�N�𗣂�����
		if (!CManager::GetInstance()->GetMouse()->GetPress(CInputMouse::MOUSEBUTTON_RIGHT) &&
			!CManager::GetInstance()->GetJoypad()->GetPress(CInputJoypad::JOYKEY_RB))
		{
			//�ʏ��ԂɕύX
			player->GetState()->SetNextState(new CState_Player_Normal(player));
			player->SetGuardJudge(false);
		}
	}
}