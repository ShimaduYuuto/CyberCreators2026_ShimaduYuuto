//======================================
//
//	�o�g���G���A�̏���[battlearea.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "battlearea.h"
#include "manager.h"
#include "game.h"
#include "battleareamanager.h"
#include "spawn_enemy.h"
#include "gimmick.h"

//============================
//�R���X�g���N�^
//============================
CBattleArea::CBattleArea() :
	m_EnemyList(),
	m_fRadius(RADIUS),
	m_pWall(nullptr),
	m_Pos(),
	m_nEnemyNum(0),
	m_bEnd(false),
	m_bEnteredArea(false),
	m_Path()
{
	
}

//============================
//�f�X�g���N�^
//============================
CBattleArea::~CBattleArea()
{
	//�ǂɏI�������n��
	if (m_pWall != nullptr)
	{
		m_pWall->SetEnd(true);
		m_pWall =  nullptr;
	}

	//���E������
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();
	pGame->GetBarrierManager()->Erase();
}

//============================
//������
//============================
HRESULT CBattleArea::Init()
{
	return S_OK;
}

//============================
//�I������
//============================
void CBattleArea::Uninit()
{
	m_bEnd = true;
}

//============================
//�X�V����
//============================
void CBattleArea::Update()
{
	//���łɃG���A���œG���c���Ă���Ȃ甲����
	if (m_bEnteredArea && m_nEnemyNum > 0)
	{
		return;
	}
	else if (m_bEnteredArea && m_nEnemyNum == 0)	//�G���S�ł���������j��
	{
		//BGM�X�g�b�v
		CManager::GetInstance()->GetSound()->Stop(CSound::SOUND_LABEL_BATTLE);
		m_bEnd = true;
		return;
	}

	//�Q�[���V�[���Ȃ画��
	if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
	{
		//�v���C���[���G���A�ɓ����Ă��邩���m�F
		CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());
		D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();	//�v���C���[�ʒu
		float fLength = sqrtf((PlayerPos.x - m_Pos.x) * (PlayerPos.x - m_Pos.x) + (PlayerPos.z - m_Pos.z) * (PlayerPos.z - m_Pos.z));	//xz���ʂ̋������Z�o

		//���m�͈͓��Ȃ�G���A�𐶐�
		if (fLength < RADIUS_ENTEREDAREA)
		{
			//�ǂ̐���
			if (m_pWall == nullptr)
			{
				m_pWall = CCollision_Wall::Create(m_Pos, m_fRadius);
			}

			//�o�g���G���A�ɓ�����
			m_bEnteredArea = true;
			CBattleAreaManager::GetInstance()->SetCurrentBattleArea(this);	//���݂̃G���A�Ƃ��ēo�^

			//�Q�[���̐퓬�����false�ɕύX
			pGame->SetBattle(true);

			//�������̓ǂݍ���
			SpawnLoad(m_Path.c_str());

			//BGM�X�^�[�g
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_BATTLE);
		}
	}
}

//============================
//�������̓ǂݍ���
//============================
void CBattleArea::SpawnLoad(const char* path)
{
	if (path == nullptr) assert("�o�g���G���A�̃p�X��������܂���ł���");

	std::ifstream File(path);  // �ǂݍ��ރt�@�C���̃p�X���w��
	std::string line;

	if (!File)
	{// ��ޖ��̏��̃f�[�^�t�@�C�����J���Ȃ������ꍇ�A
	 //�������I������
		return;
	}

	//�����ɌJ��Ԃ�
	while (1) 
	{
		//�P�����Ƃɓǂݎ��
		File >> line;

		//�I����ǂݎ������break
		if (line == "END_SCREPT") break;

		//�G���̓ǂݍ���
		if (line == "ENEMYINFO")
		{
			CBattleArea::SpawnEnemy(File);
		}

		//�M�~�b�N���̓ǂݍ���
		if (line == "GIMMICKINFO")
		{
			CBattleArea::SpawnGimmick(File);
		}
	}

	//�t�@�C�������
	File.close();
}

//============================
//�G�̐���
//============================
void CBattleArea::SpawnEnemy(std::ifstream& File)
{
	//�ǂݎ��p�̕ϐ�
	std::string line;

	//�����ɌJ��Ԃ�
	while (1)
	{
		//�P�����Ƃɓǂݎ��
		File >> line;

		//�I����ǂݎ������break
		if (line == "END_ENEMYINFO") break;

		//�G���̓ǂݍ���
		if (line == "ENEMY")
		{
			//�ǂݎ��p�̕ϐ�
			D3DXVECTOR3 Pos = { VEC3_RESET_ZERO };
			int nType = NULL;

			//���ǂݍ���
			InfoLoad(File, "END_ENEMY", Pos, nType);

			//�G�̐���
			CSpawn_Enemy::Create(GetPos() + Pos, static_cast<CEnemy::ENEMYTYPE>(nType));
		}
	}
}

//============================
//�M�~�b�N�̐���
//============================
void CBattleArea::SpawnGimmick(std::ifstream& File)
{
	//�ǂݎ��p�̕ϐ�
	std::string line;

	//�����ɌJ��Ԃ�
	while (1)
	{
		//�P�����Ƃɓǂݎ��
		File >> line;

		//�I����ǂݎ������break
		if (line == "END_GIMMICKINFO") break;

		//�G���̓ǂݍ���
		if (line == "GIMMICK")
		{
			//�ǂݎ��p�̕ϐ�
			D3DXVECTOR3 Pos = { VEC3_RESET_ZERO };
			int nType = NULL;

			//���ǂݍ���
			InfoLoad(File, "END_GIMMICK", Pos, nType);

			//�M�~�b�N�̐���
			CGimmick::Create(GetPos() + Pos, static_cast<CGimmick::TYPE>(nType));
		}
	}
}

//============================
//���̓ǂݎ��
//============================
void CBattleArea::InfoLoad(std::ifstream& File, const char* end, D3DXVECTOR3& pos, int& type)
{
	//�ǂݎ��p�̕ϐ�
	std::string line;

	while (1)
	{
		//�P�����Ƃɓǂݎ��
		File >> line;

		//�I����ǂݎ������break
		if (line == end)
		{
			break;
		}

		//�ʒu��ǂݎ��
		if (line == "POS")
		{
			//�ʒu������
			for (float& Coord : { std::ref(pos.x), std::ref(pos.y), std::ref(pos.z) })
			{
				File >> line;
				Coord = std::stof(line);
			}
		}

		//��ނ�ǂݎ��
		if (line == "TYPE")
		{
			File >> line;
			type = std::stoi(line);
		}
	}
}

//============================
//��������
//============================
CBattleArea* CBattleArea::Create(D3DXVECTOR3 pos, const char* path)
{
	//�|�C���^�p�̕ϐ�
	CBattleArea* pArea = new CBattleArea();

	//�p�����[�^�̑��
	pArea->m_Pos = pos;
	pArea->SetPath(path);

	//������
	pArea->Init();

	return pArea;
}