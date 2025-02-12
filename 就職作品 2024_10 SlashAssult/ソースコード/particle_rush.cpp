//======================================
//
//	�p�[�e�B�N���̏���[particle.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "particle_rush.h"
#include "manager.h"

//�萔
const D3DXVECTOR3 CParticle_Rush::SIZE = { 50.0f, 50.0f, 0.0f };
const std::string CParticle_Rush::TEXTUREPATH = "data\\TEXTURE\\effect000.jpg";
const D3DXCOLOR CParticle_Rush::COLOR = { 0.3f, 0.1f, 0.1f, 0.5f };

//============================
//�p�[�e�B�N���̃R���X�g���N�^
//============================
CParticle_Rush::CParticle_Rush(int nPriority) : CParticle(nPriority)
{
	//�Q�[���^�O��ݒ�
	SetTag(CObject::TAG_GAME);
}

//============================
//�p�[�e�B�N���̃f�X�g���N�^
//============================
CParticle_Rush::~CParticle_Rush()
{

}

//============================
//�p�[�e�B�N���̏�����
//============================
HRESULT CParticle_Rush::Init()
{
	//������
	CParticle::Init();

	//�p�����[�^�̐ݒ�
	SetColor(COLOR);			//�F
	SetMaxLife(MAX_LIFE);		//����
	SetNormalSize(NORMAL_SIZE);	//�T�C�Y
	return S_OK;
}

//============================
//�p�[�e�B�N���̏I������
//============================
void CParticle_Rush::Uninit()
{
	CParticle::Uninit();
}

//============================
//�p�[�e�B�N���̍X�V
//============================
void CParticle_Rush::Update()
{
	CParticle::Update();
}

//============================
//�p�[�e�B�N���̕`��
//============================
void CParticle_Rush::Draw()
{
	CParticle::Draw(TEXTUREPATH.c_str());
}

//============================
//�p�[�e�B�N���̃N���G�C�g
//============================
CParticle_Rush* CParticle_Rush::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�|�C���^�p�̕ϐ�
	CParticle_Rush* pObject;

	//�������̊m��
	pObject = new CParticle_Rush;

	pObject->SetPos(pos);

	//������
	pObject->Init();

	return pObject;
}