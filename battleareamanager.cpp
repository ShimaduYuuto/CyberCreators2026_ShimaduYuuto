//======================================
//
//	�o�g���G���A�̏���[battleareamanager.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "battleareamanager.h"

//============================
//�R���X�g���N�^
//============================
CBattleAreaManager::CBattleAreaManager() :
	m_BattleAreaList(),
	m_pCurrentBattleArea(nullptr)
{
	m_BattleAreaList.clear();
}

//============================
//�f�X�g���N�^
//============================
CBattleAreaManager::~CBattleAreaManager()
{
	m_BattleAreaList.clear();
}

//============================
//������
//============================
HRESULT CBattleAreaManager::Init()
{
	//�ǂݍ���
	Load();
	m_pCurrentBattleArea = nullptr;
	return S_OK;
}

//============================
//�I������
//============================
void CBattleAreaManager::Uninit()
{
	m_BattleAreaList.clear();
	m_pCurrentBattleArea = nullptr;
}

//============================
//�X�V
//============================
void CBattleAreaManager::Update()
{
	//���X�g�̃G���A���X�V
	for (auto itr : m_BattleAreaList)
	{
		itr->Update();	//�X�V
		
		//���S���肪�����Ă��������
		if (itr->GetEnd())
		{
			itr->Uninit();
		}
	}

	//�G���A�̏I���m�F
	if (m_pCurrentBattleArea != nullptr)
	{
		if (m_pCurrentBattleArea->GetEnd())
		{
			//���X�g����폜
			Erase(m_pCurrentBattleArea);
		}
	}
}

//============================
//�ǂݍ���
//============================
void CBattleAreaManager::Load()
{
	m_BattleAreaList.clear();

	//�G���A�̐���
	Regist(CBattleArea::Create({ 0.0f, 0.0f, 350.0f }));
}

//============================
//�o�^����
//============================
void CBattleAreaManager::Regist(CBattleArea* area)
{
	//�o�^�ς݂�
	bool bRegisted = false;

	//�������̂����������m�F
	for (auto itr : m_BattleAreaList)
	{
		if (itr == area)
		{
			bRegisted = true;
			break;
		}
	}

	//�o�^�ς݂Ȃ甲����
	if (bRegisted)
	{
		return;
	}

	//�G�̏���o�^
	m_BattleAreaList.push_back(area);
}

//============================
//�폜����
//============================
void CBattleAreaManager::Erase(CBattleArea* area)
{
	//�T�C�Y��0�Ȃ甲����
	if (m_BattleAreaList.size() == 0)
	{
		return;
	}

	//�o�^�ς݂�
	bool bRegisted = false;

	//�������̂����������m�F
	for (auto itr : m_BattleAreaList)
	{
		if (itr == area)
		{
			bRegisted = true;
			break;
		}
	}

	//�o�^����Ă��Ȃ��Ȃ甲����
	if (!bRegisted)
	{
		return;
	}

	//���݂̃G���A�Ȃ�nullptr�ɂ���
	if (m_pCurrentBattleArea == area)
	{
		delete m_pCurrentBattleArea;
		m_pCurrentBattleArea = nullptr;
	}

	//�G�̏����폜
	m_BattleAreaList.remove(area);
}