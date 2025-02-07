//================================
//
//�G�l�~�[002�̏�ԏ���[state_enemy002.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "state_enemy002.h"

//===============================================
//�ʏ���
//===============================================

//====================================
//�R���X�g���N�^
//====================================
CState_Enemy002_Normal::CState_Enemy002_Normal(CEnemy* enemy) : CState_Enemy_Normal(enemy)
{
	SetAction(new CEnemyBehavior_Standby(enemy));
};	

//===============================================
//�X�^�����
//===============================================

//====================================
//�R���X�g���N�^
//====================================
CState_Enemy002_Stan::CState_Enemy002_Stan(CEnemy* enemy) : m_pStanEffect(nullptr)
{
	SetAction(new CEnemyBehavior());
	//enemy->SetMotion(5);
	SetEndTime(3000);
	m_pStanEffect = CEffect_Stan::Create({ 0.0f, 40.0f, 0.0f }, &enemy->GetModelParts(1)->GetMtx());
}

//====================================
//�f�X�g���N�^
//====================================
CState_Enemy002_Stan::~CState_Enemy002_Stan()
{
	if (m_pStanEffect != nullptr)
	{
		m_pStanEffect->Uninit();
		m_pStanEffect = nullptr;
	}
}

//===============================================
//�\��t����ԏ��
//===============================================

//====================================
//�R���X�g���N�^
//====================================
CState_Enemy002_Stick::CState_Enemy002_Stick(CEnemy* enemy) : CState_Enemy_Stick(enemy)
{
	SetEndTime(TIME_END);
	enemy->SetMotion(CEnemy002::ENEMY002MOTION_STICK);
}

//===============================================
//���o���
//===============================================

//====================================
//�R���X�g���N�^
//====================================
CState_Enemy002_Direction::CState_Enemy002_Direction(CEnemy* enemy) : m_nCount(0)
{
	SetAction(new CEnemyBehavior_Direction(enemy));
	SetEndTime(TIME_END);
};

//====================================
//��Ԃ̍X�V����
//====================================
void CState_Enemy002_Direction::UpdateState(CEnemy* enemy)
{
	//�J�E���g�A�b�v
	m_nCount++;

	//��莞�ԂŏI��
	if (m_nCount > GetEndTime())
	{
		//��Ԃ̃��Z�b�g
		enemy->StateReset();
	}
}

//===============================================
//���j���o���
//===============================================

//====================================
//�R���X�g���N�^
//====================================
CState_Enemy002_Direction_Destroy::CState_Enemy002_Direction_Destroy(CEnemy* enemy)
{
	SetAction(new CEnemyBehavior_Direction_Destroy(enemy));
};