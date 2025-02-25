//======================================
//
//	�Q�[�W�̏���[gauge_playerlife.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "gauge_playerlife.h"
#include "manager.h"
#include "game.h"

//�萔�̐錾
const std::string CGauge_PlayerLife::TEXTURE_PATH = "data\\TEXTURE\\gauge001.png";
const D3DXVECTOR3 CGauge_PlayerLife::POS = { 150.0f, 50.0f, 0.0f };			//�ʒu
const D3DXVECTOR3 CGauge_PlayerLife::SIZE = { 200.0f, 20.0f, 0.0f };		//�Q�[�W�g�̃T�C�Y
const D3DXVECTOR3 CGauge_PlayerLife::SIZE_GAUGE = { 173.0f, 20.0f, 0.0f };	//�Q�[�W�̃T�C�Y

//============================
//�R���X�g���N�^
//============================
CGauge_PlayerLife::CGauge_PlayerLife(int nPriority) : CObject2D(nPriority),
	m_pGauge(nullptr)	//�Q�[�W�̃|�C���^
{

}

//============================
//�f�X�g���N�^
//============================
CGauge_PlayerLife::~CGauge_PlayerLife()
{

}

//============================
//������
//============================
HRESULT CGauge_PlayerLife::Init()
{
	//������
	CObject2D::Init();

	return S_OK;
}

//============================
//�I������
//============================
void CGauge_PlayerLife::Uninit()
{
	//�Q�[�W�̔j��
	if (m_pGauge != nullptr)
	{
		//�Q�[�W�̐���
		m_pGauge->Uninit();
		m_pGauge = nullptr;
	}

	CObject2D::Uninit();
}

//============================
//�X�V
//============================
void CGauge_PlayerLife::Update()
{
	//�X�V����
	CObject2D::Update();
}

//============================
//�`��
//============================
void CGauge_PlayerLife::Draw()
{
	//�`�揈��
	CObject2D::Draw(TEXTURE_PATH.c_str());
}

//============================
//�N���G�C�g
//============================
CGauge_PlayerLife* CGauge_PlayerLife::Create(float max)
{
	//�|�C���^�p�̕ϐ�
	CGauge_PlayerLife* pGauge_PlayerLife;

	//�������̊m��
	pGauge_PlayerLife = new CGauge_PlayerLife;

	//������
	pGauge_PlayerLife->Init();			//������
	pGauge_PlayerLife->SetPos(POS);		//�ʒu
	pGauge_PlayerLife->SetSize(SIZE);	//�T�C�Y
	pGauge_PlayerLife->SetGauge(max);	//�Q�[�W�̐ݒ�

	return pGauge_PlayerLife;
}

//============================
//�Q�[�W�̐ݒ菈��
//============================
void CGauge_PlayerLife::SetGauge(float max)
{
	//�Q�[�W�̃|�C���^�������Ă��Ȃ��Ȃ琶��
	if (m_pGauge == nullptr)
	{
		//�Q�[�W�̐���
		m_pGauge = CLifeGauge::Create(POS, SIZE_GAUGE, max);
		m_pGauge->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	}
	else //���łɃQ�[�W������Ȃ�p�����[�^��ݒ�
	{
		m_pGauge->SetPos(POS);		//�ʒu
		m_pGauge->SetSize(SIZE);	//�T�C�Y
		m_pGauge->SetMaxGauge(max);	//�Q�[�W�̍ő�
	}
}