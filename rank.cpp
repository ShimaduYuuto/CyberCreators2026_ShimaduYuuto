//======================================
//
//	�����N��UI�̏���[rank.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "rank.h"

const std::string CRank::TEXTUREPATH = "data\\TEXTURE\\rank001.png";
const D3DXVECTOR3 CRank::POS = { 880.0f, 510.0f, 0.0f };
const D3DXVECTOR3 CRank::SIZE = { 200.0f, 200.0f, 0.0f };

//============================
//�����N��UI�̃R���X�g���N�^
//============================
CRank::CRank(int nPriority) : CObject2D(nPriority)
{

}

//============================
//�����N��UI�̃f�X�g���N�^
//============================
CRank::~CRank()
{

}

//============================
//�����N��UI�̏�����
//============================
HRESULT CRank::Init()
{
	//������
	CObject2D::Init();

	//�p�����[�^�̐ݒ�
	SetPos(POS);	//�ʒu
	SetSize(SIZE);	//�T�C�Y
	SetTextureUV(0.0f, 1.0f / 5.0f, 0.0f, 1.0f);	//UV���W

	return S_OK;
}

//============================
//�����N��UI�̏I������
//============================
void CRank::Uninit()
{
	CObject2D::Uninit();
}

//============================
//�����N��UI�̍X�V
//============================
void CRank::Update()
{

}

//============================
//�����N��UI�̕`��
//============================
void CRank::Draw()
{
	//�`�揈��
	CObject2D::Draw(TEXTUREPATH.c_str());
}

//============================
//�����N��UI�̃N���G�C�g
//============================
CRank* CRank::Create()
{
	//�|�C���^�p�̕ϐ�
	CRank* pRank;

	//�������̊m��
	pRank = new CRank;

	//������
	pRank->Init();

	return pRank;
}