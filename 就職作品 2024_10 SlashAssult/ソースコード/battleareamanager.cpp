//======================================
//
//	�o�g���G���A�̊Ǘ�����[battleareamanager.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "battleareamanager.h"
#include "game.h"
#include "manager.h"

//============================
//�R���X�g���N�^
//============================
CBattleAreaManager::CBattleAreaManager() :
	m_BattleAreaList(),
	m_pCurrentBattleArea(nullptr)
{
	//���X�g�̏�����
	m_BattleAreaList.clear();
}

//============================
//�f�X�g���N�^
//============================
CBattleAreaManager::~CBattleAreaManager()
{
	//���X�g�̏�����
	m_BattleAreaList.clear();
}

//============================
//������
//============================
HRESULT CBattleAreaManager::Init()
{
	//�ǂݍ���
	Load();

	return S_OK;
}

//============================
//�I������
//============================
void CBattleAreaManager::Uninit()
{
	//���X�g�̃N���A
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

	std::ifstream File("data\\FILE\\battleareaInfo.txt");	//�ǂݍ��ރt�@�C���̃p�X���w��
	std::string String;										//�ǂݎ��p

	if (!File) return;	//�ǂݍ��݂Ɏ��s�����甲����

	//�����ɌJ��Ԃ�
	while (1)
	{
		//�P�����Ƃɓǂݎ��
		File >> String;

		//�I����ǂݎ������break
		if (String == "END_SCREPT") break;

		//�o�g���G���A�̓ǂݍ���
		if (String == "BATTLEAREA")
		{
			LoadBattleArea(File);
		}
	}

	//�t�@�C�������
	File.close();
}

//============================
//�o�g���G���A�̓ǂݍ���
//============================
void CBattleAreaManager::LoadBattleArea(std::ifstream& File)
{
	//�ǂݎ��p�̕ϐ�
	std::string String;
	D3DXVECTOR3 Pos = { VEC3_RESET_ZERO };
	std::string Path;

	//�����ɌJ��Ԃ�
	while (1)
	{
		//�P�����Ƃɓǂݎ��
		File >> String;

		//�I����ǂݎ������break
		if (String == "END_BATTLEAREA")
		{
			Regist(CBattleArea::Create(Pos, Path.c_str()));	//�o�^
			break;
		}

		//�ʒu�̓ǂݍ���
		if (String == "POS")
		{
			//�ʒu������
			for (float& Coord : { std::ref(Pos.x), std::ref(Pos.y), std::ref(Pos.z) })
			{
				File >> String;
				Coord = std::stof(String);
			}
		}

		//�p�X�̓ǂݍ���
		if (String == "PATH")
		{
			File >> String;
			Path = String;
		}
	}
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

		//�Q�[���̐퓬�����false�ɕύX
		CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());
		pGame->SetBattle(false);
	}

	//�G���A�̏����폜
	m_BattleAreaList.remove(area);
}