//======================================
//
//	���b�N�I������[lockon.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "lockon.h"
#include "camera.h"
#include "manager.h"
#include "game.h"

//============================
//�R���X�g���N�^
//============================
CLockon::CLockon() : 
	m_pTarget(nullptr),	//���݃^�[�Q�b�g�Ώۂ̃|�C���^
	m_pMark(nullptr),	//��̃|�C���^
	m_LockonList(),		//���b�N�I���Ώۂ����̃��X�g
	m_pRushUi(nullptr)	//���b�V���\��UI��\������|�C���^
{
	m_LockonList.clear();
}

//============================
//�f�X�g���N�^
//============================
CLockon::~CLockon()
{

}

//============================
//������
//============================
HRESULT CLockon::Init()
{
	return S_OK;
}

//============================
//�I������
//============================
void CLockon::Uninit()
{
	//�}�[�N�𐶐�
	if (m_pMark != nullptr)
	{
		m_pMark->Uninit();
		m_pMark = nullptr;
	}

	//��������
	delete this;
}

//============================
//�X�V
//============================
void CLockon::Update()
{
	//���b�N�I���Ώۂ���ʓ��ɑ��݂��邩���m�F
	if (m_pMark != nullptr)
	{
		//���Ȃ�������j��
		if (!CManager::GetInstance()->GetCamera()->GetViewObject(m_pMark->GetPos()))
		{
			//��ƑΏۂ̃|�C���^��j��
			m_pMark->Uninit();
			m_pMark = nullptr;
			m_pTarget = nullptr;
			
		}
		else
		{
			return;
		}
	}

	//�󂪂Ȃ��Ȃ�
	if (m_pMark == nullptr)
	{
		//���X�g�ɂ��Ȃ��Ȃ甲����
		if (m_LockonList.size() == 0)
		{
			return;
		}

		//�ŏ��̓G���擾
		auto iter = m_LockonList.begin();
		m_pTarget = *iter;
		m_pMark = CLockonMark::Create(MARK_RADIUS, &m_pTarget->GetCollision()->GetPos());
	}
}

//============================
//�N���G�C�g
//============================
CLockon* CLockon::Create()
{
	//�|�C���^�p�̕ϐ�
	CLockon* pLockon = nullptr;

	//����
	pLockon = new CLockon;

	//������
	pLockon->Init();

	return pLockon;
}

//============================
//�o�^
//============================
void CLockon::Regist(CEnemy* enemy)
{
	//�ϐ��錾
	bool bRegist = false;

	//�G�̎���
	for (auto& iter : m_LockonList)
	{
		//���łɓo�^���Ă���Ȃ�o�^���Ȃ�
		if (iter == enemy)
		{
			bRegist = true;
			break;
		}
	}

	//�o�^���Ă��Ȃ��Ȃ�o�^
	if (!bRegist)
	{
		m_LockonList.push_back(enemy);
	}
}

//============================
//�폜
//============================
void CLockon::Erase(CEnemy* enemy)
{
	//�G�̎���
	for (auto& iter : m_LockonList)
	{
		//���łɓo�^���Ă���Ȃ�o�^���Ȃ�
		if (iter == enemy)
		{
			//�G�̏����폜
			if (m_pTarget == enemy)
			{
				m_pTarget = nullptr;
				m_pMark->Uninit();
				m_pMark = nullptr;
			}
			m_LockonList.remove(iter);
			break;
		}
	}
}