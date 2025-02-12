//================================
//
//�G�̍s���܂Ƃ�[behavior_enemy.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "behavior_enemy.h"
#include "manager.h"
#include "game.h"

//====================================
//�ǂ���������
//====================================

//==============================
//�R���X�g���N�^
//==============================
CEnemyBehavior_Chase::CEnemyBehavior_Chase(CEnemy* enemy)
{
	enemy->SetCollisionProcess(true);	//�����蔻��𑱂���
}

//==============================
//�A�N�V����
//==============================
void CEnemyBehavior_Chase::Action(CEnemy* enemy)
{
	//�v���C���[�̕�������
	LookAtPlayer(enemy);

	//�ړ�
	Move(enemy);
}

//==============================
//�v���C���[�̕���������
//==============================
void CEnemyBehavior_Chase::LookAtPlayer(CEnemy* enemy)
{
	//�Q�[���V�[���̃v���C���[�̈ʒu���擾
	CGame* pGame = nullptr;
	pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());	//�Q�[���V�[���̎擾
	D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();			//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 Pos = enemy->GetPos();									//�����̈ʒu���擾

	//�v���C���[�Ƃ̊p�x���Z�o
	float fAngle = atan2f(PlayerPos.x - Pos.x, PlayerPos.z - Pos.z);//�Ίp���̊p�x���Z�o

	//�p�x��ݒ�
	enemy->SetGoalRot({ enemy->GetRot().x, fAngle + D3DX_PI, enemy->GetRot().z });
}

//==============================
//�ړ�����
//==============================
void CEnemyBehavior_Chase::Move(CEnemy* enemy)
{
	//�����Ă�����
	if (enemy->GetOnStand())
	{
		//���͈͓��ɓ�������U��
		if (IsNextAction(enemy))
		{
			//���̃A�N�V�����Ɉڍs
			NextAction(enemy);
		}
		else
		{
			//�ǂ�������ړ�������
			ChaseMove(enemy);
		}
	}
	else
	{
		//�d�͂̉e���̂ݔ��f
		enemy->CCharacter::SetMove({ 0.0f, enemy->CCharacter::GetMove().y, 0.0f });
	}
}

//==============================
//���̍s���Ɉڍs���邩
//==============================
bool CEnemyBehavior_Chase::IsNextAction(CEnemy* enemy)
{
	if (!enemy->GetOnStand()) return false;	//�����Ă��Ȃ��Ȃ�ڍs���Ȃ�

	//�Q�[���V�[���̃v���C���[�̈ʒu���擾
	CGame* pGame = nullptr;
	pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());	//�Q�[���V�[���̎擾
	D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();			//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 Pos = enemy->GetPos();									//�����̈ʒu���擾

	//�����̌v�Z
	D3DXVECTOR3 fLengthPos = PlayerPos - Pos;
	float fLength = sqrtf(fLengthPos.x * fLengthPos.x + fLengthPos.z * fLengthPos.z);

	//�͈͊O�Ȃ甲����
	if (fLength > LENGTH_CHANGEATTACK) return false;

	//�͈͓��Ȃ�ڍs
	return true;
}

//==============================
//�ǂ�������ړ��̏���
//==============================
void CEnemyBehavior_Chase::ChaseMove(CEnemy* enemy)
{
	//�Q�[���V�[���̃v���C���[�̈ʒu���擾
	CGame* pGame = nullptr;
	pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());	//�Q�[���V�[���̎擾
	D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();			//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 Pos = enemy->GetPos();									//�����̈ʒu���擾

	//�v���C���[�Ƃ̊p�x���Z�o
	float fAngle = atan2f(PlayerPos.x - Pos.x, PlayerPos.z - Pos.z);//�Ίp���̊p�x���Z�o

	enemy->CCharacter::AddMove({ sinf(fAngle) * VALUE_MOVE, 0.0f, cosf(fAngle) * VALUE_MOVE });
}

//===========================
//�U���N���X
//===========================

//===============================
//�R���X�g���N�^
//===============================
CEnemyBehavior_Attack::CEnemyBehavior_Attack(CEnemy* enemy) :m_pAttack(nullptr), m_fAttackLength(0.0f)
{
	//�C���X�^���X�𐶐�
	if (m_pAttack == nullptr)
	{
		m_pAttack = new CAttack();
	}

	//�U�����͓����蔻����s��Ȃ�
	enemy->SetCollisionProcess(false);
}

//===============================
//�f�X�g���N�^
//===============================
CEnemyBehavior_Attack::~CEnemyBehavior_Attack()
{
	//�U���|�C���^�̊J��
	if (m_pAttack != nullptr)
	{
		delete m_pAttack;
		m_pAttack = nullptr;
	}
}

//===============================
//�U������
//===============================
void CEnemyBehavior_Attack::Action(CEnemy* enemy)
{
	//�p�����[�^�̎擾
	float fCount = m_pAttack->GetActionCount();		//�J�E���g
	float fEndTime = m_pAttack->GetEndTime();			//�I������

	//�����蔻����m�F���邩
	if (IsCheckCollision())
	{
		//�����蔻��̊m�F
		CheckCollision(enemy);
	}

	//�J�E���g���I���l�ɂȂ������Ԃ̕ύX
	if (fEndTime < fCount)
	{
		NextAction(enemy);	//���̍s����ݒ�
	}

	//�J�E���g�̍X�V
	fCount++;

	//�p�����[�^�̐ݒ�
	m_pAttack->SetActionCount(fCount);
}

//===============================
//�����蔻��̊m�F
//===============================
void CEnemyBehavior_Attack::CheckCollision(CEnemy* enemy)
{
	//�Q�[���V�[���̎擾
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//�ϐ��錾
	D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetCollision()->GetPos();	//�v���C���[�̈ʒu
	D3DXVECTOR3 AttackRot = enemy->GetRot();									//�U���̌���
	D3DXVECTOR3 AttackPos = enemy->GetCollision()->GetPos();					//�U���̈ʒu

	//�U���̈ʒu���Z�o
	AttackPos += D3DXVECTOR3(sinf(AttackRot.y + D3DX_PI) * POS_LENGTH, 0.0f, cosf(AttackRot.y + D3DX_PI) * POS_LENGTH);

	//�������v�Z
	D3DXVECTOR3 Length = AttackPos - PlayerPos;	//3�����ɕ�����������
	float fLength = D3DXVec3Length(&Length);	//����
	float fAngle = atan2f(Length.x, Length.z);	//�p�x

	//�U���͈͓̔��Ȃ�
	if (fLength < m_fAttackLength)
	{
		HitPlayer(fAngle);
	}
}

//===============================
//�����蔻��̊m�F�����邩
//===============================
bool CEnemyBehavior_Attack::IsCheckCollision()
{
	//�p�����[�^�̎擾
	bool bHit = m_pAttack->GetHit();						//����������
	float fCount = m_pAttack->GetActionCount();				//�J�E���g
	float fCollisionTime = m_pAttack->GetCollisionTime();	//�����蔻��̎���

	//�m�F
	if (fCount <= fCollisionTime) return false;	//�R���W�������������鎞�ԂȂ�ʂ�
	if (bHit) return false;						//�܂��������Ă��Ȃ��Ȃ�ʂ�

	return true;
}

//===============================
//�v���C���[�Ƀq�b�g�����ۂ̏���
//===============================
void CEnemyBehavior_Attack::HitPlayer(float angle)
{
	//�ϐ��錾
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());	//�Q�[���V�[���̎擾
	int nDamageValue = m_pAttack->GetDamageValue();								//�_���[�W�l

	//�v���C���[�Ƀ_���[�W��^����
	pGame->GetGamePlayer()->SetDamage(nDamageValue, angle);
	m_pAttack->SetHit(true);
}