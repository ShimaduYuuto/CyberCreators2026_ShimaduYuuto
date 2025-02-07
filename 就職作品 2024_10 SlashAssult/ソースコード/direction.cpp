//======================================
//
//	���o�̏���[direction.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "direction.h"
#include "direction_boss.h"
#include "direction_boss_destroy.h"

//============================
//���o�̃R���X�g���N�^
//============================
CDirection::CDirection() :
	m_nCount(0),
	m_nEndTime(0),
	m_pLetterBox(nullptr)
{
	
}

//============================
//���o�̃f�X�g���N�^
//============================
CDirection::~CDirection()
{

}

//============================
//���o�̏�����
//============================
HRESULT CDirection::Init()
{
	return S_OK;
}

//============================
//���o�̍X�V
//============================
bool CDirection::TimeUpdate()
{
	m_nCount++;

	//�I�����Ԃ𒴂�����
	if (m_nCount > m_nEndTime)
	{
		return true;
	}

	return false;
}

//============================
//���o�̐���
//============================
CDirection* CDirection::Create(DIRECTIONTYPE type)
{
	//��ނɉ����ē��I�m��
	CDirection* pDirction = nullptr;

	switch (type)
	{
	case DIRECTIONTYPE_BOSS:	//�{�X�̓o�ꎞ�̉��o

		//�G�̃������m��
		pDirction = new CDirection_Boss();
		break;

	case DIRECTIONTYPE_BOSS_DESTROY:	//�{�X�̌��j���̉��o

		//�G�̃������m��
		pDirction = new CDirection_Boss_Destroy();
		break;

	default:
		assert(true);
		break;

	}

	//������
	pDirction->Init();

	//�ݒ肵������Ԃ�
	return pDirction;
}

//============================
//�I�����Ԃ̐ݒ�
//============================
void CDirection::SetEndTime(int time)
{
	//���Ԃ̐ݒ�
	m_nEndTime = time;

	//���^�[�{�b�N�X�̐���
	if (m_pLetterBox == nullptr)
	{
		m_pLetterBox = CLetterBox::Create(time);
	}
}