//================================
//
//��Ԃɉ��������������s[state_enemy.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "state_enemy.h"
#include "game.h"
#include "manager.h"
#include "state_enemy_normal.h"

//====================================
//�f�X�g���N�^
//====================================
CState_Enemy::~CState_Enemy()
{
	//�A�N�V�����̔j��
	if (m_pAction != nullptr)
	{
		//���̃A�N�V�������j��
		if (m_pAction->GetNextAction() != nullptr)
		{
			CEnemyBehavior* pNext = m_pAction->GetNextAction();
			delete pNext;
			pNext = nullptr;
		}
		
		delete m_pAction;
		m_pAction = nullptr;
	}

	//���̏�Ԃ�j��
	if (m_pNextState != nullptr)
	{
		m_pNextState = nullptr;
	}
}

//====================================
//�X�V����
//====================================
void CState_Enemy::Update(CEnemy* enemy)
{
	//�A�N�V�����̍X�V
	UpdateAction(enemy);

	//��ԃJ�E���g�̍X�V
	UpdateState(enemy);
}

//====================================
//�A�N�V��������
//====================================
void CState_Enemy::UpdateAction(CEnemy*& enemy)
{
	//�A�N�V�����̍X�V
	if (m_pAction != nullptr)
	{
		//�h����̃A�N�V���������s
		m_pAction->Action(enemy);

		//���̃A�N�V����������Ȃ�ύX
		if (m_pAction->GetNextAction() != nullptr)
		{
			//���̃A�N�V�����ɕύX
			CEnemyBehavior* pNext = m_pAction->GetNextAction();
			delete m_pAction;
			m_pAction = nullptr;

			//���
			m_pAction = pNext;
		}
	}
}

//====================================
//��ԍX�V����
//====================================
void CState_Enemy::UpdateState(CEnemy* enemy)
{
	//�����o�ϐ��̎擾
	float fEndTime{ GetEndTime() };	//�I������
	float fCount{ GetStateCount() };//�J�E���g�̎擾

	//�J�E���g�A�b�v
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());	//�Q�[���V�[���̎擾
	fCount += pGame->GetTime()->GetValue<float>(1.0f);							//���Ԃɉ����ăJ�E���g�A�b�v

	//�J�E���g������؂������Ԃ�؂�ւ���
	if (fCount >= fEndTime)
	{
		//���̏�Ԃ�ݒ�
		if (m_pNextState == nullptr)
		{
			m_pNextState = new CState_Enemy_Normal(enemy);
		}
	}
}

//====================================
//�G�l�~�[���m�̓����蔻��
//====================================
void CState_Enemy::EnemyCollision(CEnemy* enemy)
{
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());	//�Q�[���V�[���̎擾
	CEnemyManager* pManager = pGame->GetEnemyManager();							//�G�l�~�[�}�l�[�W���[�̎擾

	//���̓G�Ƃ̓����蔻��
	for (auto& itr : pManager->GetList())
	{
		//�������g�Ȃ��΂�
		if (itr == enemy)
		{
			continue;
		}

		//�ʒu�̎擾
		D3DXVECTOR3 Pos = itr->GetCollision()->GetPos();
		D3DXVECTOR3 EnemyPos = enemy->GetCollision()->GetPos();

		//�������v�Z
		float fLength = sqrtf((EnemyPos.x - Pos.x) * (EnemyPos.x - Pos.x) + (EnemyPos.z - Pos.z) * (EnemyPos.z - Pos.z));
		float fTotalRadius = itr->GetCollision()->GetRadius() + enemy->GetCollision()->GetRadius();

		//�͈͓��̊m�F
		if (fLength < fTotalRadius)
		{
			//�G�̓�����Ȃ��ʒu�ɕ␳
			float fAngle = atan2f(Pos.x - EnemyPos.x, Pos.z - EnemyPos.z);//�Ίp���̊p�x���Z�o

			//�ʒu��ݒ�
			enemy->SetPos(D3DXVECTOR3(sinf(fAngle + D3DX_PI) * fTotalRadius + Pos.x,
				enemy->GetPos().y,
				cosf(fAngle + D3DX_PI) * fTotalRadius + Pos.z));
		}
	}
}