//======================================
//
//	�M�~�b�N�̏���[gimmick.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "gimmick.h"
#include "manager.h"
#include "game.h"
#include "explodingbarrel.h"

//�萔
const D3DXVECTOR3 CGimmick::COLLISION_POS = { 0.0f, 30.0f, 0.0f };

//============================
//�R���X�g���N�^
//============================
CGimmick::CGimmick(int nPriority) : CObjectX(nPriority),
	m_Collision(nullptr)
{
	//�Q�[���V�[���̎擾
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

	//�}�l�[�W���[�ɓo�^
	pGame->GetGimmickManager()->Regist(this);

	//�Q�[���^�O��ݒ�
	SetTag(CObject::TAG_GAME);
}

//============================
//�f�X�g���N�^
//============================
CGimmick::~CGimmick()
{
	//�Q�[���V�[���̎擾
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

	//�}�l�[�W���[����폜
	if (pGame->GetGimmickManager() != nullptr)
	{
		pGame->GetGimmickManager()->Erase(this);
	}	

	//�����蔻��̏���
	if (m_Collision != nullptr)
	{
		m_Collision->Uninit();
		m_Collision = nullptr;
	}
}

//============================
//������
//============================
HRESULT CGimmick::Init()
{
	//������
	CObjectX::Init();

	//�����蔻��̐���
	if (m_Collision == nullptr)
	{
		m_Collision = CCollision::Create(COLLISION_RADIUS, COLLISION_POS);
	}

	return S_OK;
}

//============================
//�I������
//============================
void CGimmick::Uninit()
{
	//������
	CObjectX::Uninit();
}

//============================
//�X�V
//============================
void CGimmick::Update()
{
	//�Q�[���I�u�W�F�N�g�̋��ʏ����X�V
	CObjectX::Update();
	m_Collision->Update(GetPos());
}

//============================
//��������
//============================
CGimmick* CGimmick::Create(D3DXVECTOR3 pos, TYPE type)
{
	CGimmick* pGimmick = nullptr;

	//��ނɉ����Ĕh��
	switch (type)
	{
	case TYPE::TYPE_EXPLODINGBARREL:
		pGimmick = new CExplodingBarrel();
		break;

	default:
		assert("�͈͊O�̃M�~�b�N��ނł�");
	}

	//�p�����[�^�̐ݒ�
	pGimmick->Init();		//������
	pGimmick->SetPos(pos);	//�ʒu�̐ݒ�

	return pGimmick;
}