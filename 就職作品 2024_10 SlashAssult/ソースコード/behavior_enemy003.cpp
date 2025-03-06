//================================
//
//�G�̍s���܂Ƃ�[behavior_enemy003.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "behavior_enemy003.h"
#include "enemy003.h"
#include "game.h"
#include "manager.h"

//======================================================================
//�ҋ@
//======================================================================

//====================================
//�R���X�g���N�^
//====================================
CEnemyBehavior_Standby003::CEnemyBehavior_Standby003(CEnemy* enemy) : 
	m_nCoolTime(0)	//�N�[���^�C��
{
	//�֐�
	enemy->SetMotion(CEnemy003::ENEMY003MOTION_NORMAL);	//���[�V����
	enemy->SetCollisionProcess(true);					//�����蔻����s��
	m_nCoolTime = COOL_TIME;							//�N�[���^�C��
};

//====================================
//�A�N�V����(�ҋ@)
//====================================
void CEnemyBehavior_Standby003::Action(CEnemy* enemy)
{
	//�N�[���^�C�������炷
	m_nCoolTime--;

	//�N�[���^�C�����I������玟�̍s�����s��
	if (m_nCoolTime < 0)
	{
		//�U������
		SetNextAction(new CEnemyBehavior_ChargeAttack(enemy));
	}
}

//====================================
//���̍s����ݒ�
//====================================
void CEnemyBehavior_Standby003::NextAction(CEnemy* enemy)
{
	//�U����ݒ�
	SetNextAction(new CEnemyBehavior_Attack003(enemy));
}

//======================================================================
//�`���[�W�A�^�b�N
//======================================================================

//====================================
//�R���X�g���N�^
//====================================
CEnemyBehavior_Attack003::CEnemyBehavior_Attack003(CEnemy* enemy) : CEnemyBehavior_Attack(enemy)
{
	//�ݒ�
	GetAttackInstanse()->SetCollisionTime(START_COLLISON_TIME);	//�����蔻�肪�n�܂鎞��
	GetAttackInstanse()->SetEndTime(END_TIME);					//�I�����鎞��
	GetAttackInstanse()->SetDamageValue(DAMAGE_VALUE);			//�_���[�W��
	SetAttackLength(ATTACK_LENGTH);								//�U���̋���
	enemy->SetMotion(CEnemy003::ENEMY003MOTION_ACTION);			//���[�V����
	enemy->SetCollisionProcess(false);							//�����蔻����s��
};

//====================================
//�A�N�V����(�U��)
//====================================
void CEnemyBehavior_Attack003::Action(CEnemy* enemy)
{
	CEnemyBehavior_Attack::Action(enemy);
};

//====================================
//���̃A�N�V������ݒ�
//====================================
void CEnemyBehavior_Attack003::NextAction(CEnemy* enemy)
{
	SetNextAction(new CEnemyBehavior_Standby003(enemy));
}

//====================================
//�A�N�V����(�`���[�W�A�^�b�N)
//====================================
void CEnemyBehavior_ChargeAttack::Action(CEnemy* enemy)
{
	//�J�E���g�̍X�V
	m_nChargeCount++;

	//�J�E���g�����؂��Ă��Ȃ��Ȃ�X�V
	if (m_nChargeCount <= CHARGE_TIME)
	{
		//�v���C���[�̕�������
		LookAtPlayer(enemy);
	}
	else
	{
		//�ړ��l�̐ݒ�
		enemy->SetMove({ sinf(m_fAttackAngle) * SPEED_MOVE, 0.0f, cosf(m_fAttackAngle) * SPEED_MOVE });

		//�U���͈͓̔��Ȃ�
		if (CheckAttackHit(enemy))
		{
			EndAttack(enemy);	//�U���I�����̏���
		}

		//�I���̎��ԂɂȂ�����ҋ@
		if (m_nChargeCount > END_TIME)
		{
			EndAttack(enemy);	//�U���I�����̏���
		}
	}
	
}

//====================================
//�v���C���[�̕�������
//====================================
void CEnemyBehavior_ChargeAttack::LookAtPlayer(CEnemy* enemy)
{
	//�ϐ��錾
	CGame* pGame = nullptr;
	pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());		//�Q�[���V�[���̎擾
	D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();				//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 Pos = enemy->GetPos();										//�����̈ʒu���擾

	//�v���C���[�Ƃ̊p�x���Z�o
	float fAngle = atan2f(PlayerPos.x - Pos.x, PlayerPos.z - Pos.z);//�Ίp���̊p�x���Z�o

	//�p�x��ݒ�
	enemy->SetGoalRot({ enemy->GetRot().x, fAngle + D3DX_PI, enemy->GetRot().z });

	//�`���[�W���I�������U��
	if (m_nChargeCount >= CHARGE_TIME)
	{
		PreparationAttack(enemy, fAngle);
	}
}

//====================================
//�U���̏���
//====================================
void CEnemyBehavior_ChargeAttack::PreparationAttack(CEnemy* enemy, float angle)
{
	//�U������ɂ���
	CEnemy003* pEnemy003 = dynamic_cast<CEnemy003*>(enemy);
	pEnemy003->SetAttacking(true);

	//�ړ��l�̐ݒ�
	enemy->SetMove({ sinf(angle) * SPEED_MOVE, 0.0f, cosf(angle) * SPEED_MOVE });
	m_fAttackAngle = angle;
}

//====================================
//�U�����������������m�F
//====================================
bool CEnemyBehavior_ChargeAttack::CheckAttackHit(CEnemy* enemy)
{
	//�ϐ��錾
	CGame* pGame = nullptr;
	pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());			//�Q�[���V�[���̎擾
	D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetCollision()->GetPos();	//�v���C���[�̓����蔻��̈ʒu
	D3DXVECTOR3 EnemyPos = enemy->GetCollision()->GetPos();						//�G�l�~�[�̈ʒu���擾
	D3DXVECTOR3 Distance = enemy->GetPos() - PlayerPos;
	float fAngle = atan2f(Distance.x, Distance.z);

	//�������v�Z
	float fXZ = sqrtf((EnemyPos.x - PlayerPos.x) * (EnemyPos.x - PlayerPos.x) + (EnemyPos.z - PlayerPos.z) * (EnemyPos.z - PlayerPos.z)); //�������Z�o����
	float fXY = sqrtf((EnemyPos.x - PlayerPos.x) * (EnemyPos.x - PlayerPos.x) + (EnemyPos.y - PlayerPos.y) * (EnemyPos.y - PlayerPos.y)); //�������Z�o����
	float fLength = sqrtf(fXZ * fXZ + fXY * fXY);	//�������Z�o

	//����
	if (fLength > pGame->GetGamePlayer()->GetCollision()->GetRadius() + enemy->GetCollision()->GetRadius()) return false;	//�U�����������Ă��Ȃ��Ȃ甲����
	if (!pGame->GetGamePlayer()->SetDamage(1, fAngle)) return false;														//�_���[�W��^�����Ȃ������甲����

	return true;
}

//====================================
//�U���I�����̏���
//====================================
void CEnemyBehavior_ChargeAttack::EndAttack(CEnemy* enemy)
{
	//�U������̏I��
	CEnemy003* pEnemy003 = dynamic_cast<CEnemy003*>(enemy);
	if (pEnemy003 == nullptr) assert("enemy003�ւ̃L���X�g�Ɏ��s");
	pEnemy003->SetAttacking(false);

	//�ҋ@��ԂɂȂ�
	SetNextAction(new CEnemyBehavior_Standby003(enemy));
}