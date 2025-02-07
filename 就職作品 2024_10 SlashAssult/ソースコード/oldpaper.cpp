//======================================
//
//	�Â�����UI�̏���[oldpaper.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "oldpaper.h"
#include "manager.h"

const std::string COldPaper::TEXTUREPATH = "data\\TEXTURE\\oldpaper002.png";
const D3DXVECTOR3 COldPaper::POS = { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f };
const D3DXVECTOR3 COldPaper::SIZE = { SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.8f, 0.0f };

//============================
//�Â�����UI�̃R���X�g���N�^
//============================
COldPaper::COldPaper(int nPriority) : CObject2D(nPriority)
{

}

//============================
//�Â�����UI�̃f�X�g���N�^
//============================
COldPaper::~COldPaper()
{

}

//============================
//�Â�����UI�̏�����
//============================
HRESULT COldPaper::Init()
{
	//������
	CObject2D::Init();

	//�p�����[�^�̐ݒ�
	SetPos(POS);	//�ʒu
	SetSize(SIZE);	//�T�C�Y

	return S_OK;
}

//============================
//�Â�����UI�̏I������
//============================
void COldPaper::Uninit()
{
	CObject2D::Uninit();
}

//============================
//�Â�����UI�̍X�V
//============================
void COldPaper::Update()
{
	
}

//============================
//�Â�����UI�̕`��
//============================
void COldPaper::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���g�厞�ɐF���ߎ��l�ɂ���
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);

	//�`�揈��
	CObject2D::Draw(TEXTUREPATH.c_str());

	//�e�N�X�`���g�厞�̐F����`���
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
}

//============================
//�Â�����UI�̃N���G�C�g
//============================
COldPaper* COldPaper::Create()
{
	//�|�C���^�p�̕ϐ�
	COldPaper* pOldPaper;

	//�������̊m��
	pOldPaper = new COldPaper;

	//������
	pOldPaper->Init();

	return pOldPaper;
}