//======================================
//
//	�G�l�~�[�X�|�[������[spawn_enemy.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "spawn_enemy.h"
#include "battleareamanager.h"

//============================
//�R���X�g���N�^
//============================
CSpawn_Enemy::CSpawn_Enemy(int nPriority) : CObject(nPriority),
	m_nCount(0),				//�J�E���g
	m_pPaticleManager(nullptr),	//�p�[�e�B�N���̐��������|�C���^
	m_EnemyType()				//�o��������G�̎��
{
	//�o�^����G�̐��𑝂₷
	if (CBattleAreaManager::GetInstance()->GetCurrentBattleArea() != nullptr)
	{
		CBattleAreaManager::GetInstance()->GetCurrentBattleArea()->AddEnemyNum();
	}
}

//============================
//�f�X�g���N�^
//============================
CSpawn_Enemy::~CSpawn_Enemy()
{
	//�p�[�e�B�N���}�l�[�W���[�̔j��
	if (m_pPaticleManager != nullptr)
	{
		delete m_pPaticleManager;
		m_pPaticleManager = nullptr;
	}
}

//============================
//������
//============================
HRESULT CSpawn_Enemy::Init()
{
	//�p�[�e�B�N���̐���
	m_pPaticleManager = CParticle_Spawn::Create(GetPos());

	return S_OK;
}

//============================
//�I��
//============================
void CSpawn_Enemy::Uninit()
{
	CObject::Uninit();
}

//============================
//�X�V
//============================
void CSpawn_Enemy::Update()
{
	//�p�[�e�B�N���}�l�[�W���[�̍X�V
	m_pPaticleManager->Update();

	//�J�E���g�A�b�v
	m_nCount++;

	//��莞�ԂœG�𐶐�
	if (m_nCount > SPAWN_TIME)
	{
		CEnemy::Create(GetPos(), m_EnemyType);
		Uninit();
	}
}

//============================
//����
//============================
CSpawn_Enemy* CSpawn_Enemy::Create(D3DXVECTOR3 pos, CEnemy::ENEMYTYPE type)
{
	//�|�C���^�p�̕ϐ�
	CSpawn_Enemy* pObject;

	//�������̊m��
	pObject = new CSpawn_Enemy();

	//�p�����[�^�̐ݒ�
	pObject->SetPos(pos);		//�ʒu�̐ݒ�
	pObject->m_EnemyType = type;//���

	//������
	pObject->Init();

	return pObject;
}