//======================================
//
//	UI�̏���[ui_gamestart.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "ui_gamestart.h"

//�萔
const std::string CUi_GameStart::TEXTURE_PATH = "data\\TEXTURE\\GameStart001.png";
const D3DXVECTOR3 CUi_GameStart::POS = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.7f, 0.0f };

//============================
//UI�̃R���X�g���N�^
//============================
CUi_GameStart::CUi_GameStart(int nPriority) : CObject2D(nPriority),
	m_fCurrentAlpha(1.0f),
	m_fAddAlpha(0.0f)
{

}

//============================
//UI�̃f�X�g���N�^
//============================
CUi_GameStart::~CUi_GameStart()
{

}

//============================
//UI�̏�����
//============================
HRESULT CUi_GameStart::Init()
{
	//������
	CObject2D::Init();

	return S_OK;
}

//============================
//UI�̏I������
//============================
void CUi_GameStart::Uninit()
{
	CObject2D::Uninit();
}

//============================
//UI�̍X�V
//============================
void CUi_GameStart::Update()
{
	//���l�̍X�V
	m_fCurrentAlpha += m_fAddAlpha;

	//���Z���Z�̊m�F
	if (m_fCurrentAlpha >= 1.0f)
	{
		m_fCurrentAlpha = 1.0f;
		m_fAddAlpha = -ADD_ALPHA;
	}
	else if (m_fCurrentAlpha <= 0.0f)
	{
		m_fCurrentAlpha = 0.0f;
		m_fAddAlpha = ADD_ALPHA;
	}

	//�F�̐ݒ�
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fCurrentAlpha));

	CObject2D::Update();
}

//============================
//UI�̕`��
//============================
void CUi_GameStart::Draw()
{
	//�`�揈��
	CObject2D::Draw(TEXTURE_PATH.c_str());
}

//============================
//UI�̃N���G�C�g
//============================
CUi_GameStart* CUi_GameStart::Create()
{
	//�|�C���^�p�̕ϐ�
	CUi_GameStart* pUi_GameStart;

	//�������̊m��
	pUi_GameStart = new CUi_GameStart;

	//������
	pUi_GameStart->Init();
	pUi_GameStart->SetPos(POS);	//�ʒu
	pUi_GameStart->SetSize({ WIDTH, HEIGHT, 0.0f });	//�T�C�Y
	pUi_GameStart->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });

	return pUi_GameStart;
}