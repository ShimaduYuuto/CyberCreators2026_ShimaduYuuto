//======================================
//
//	�X�R�A�̕`��[score.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "number.h"
#include "manager.h"
#include "game.h"

//�萔�̏�����
const std::string CNumber::TEXTUREPATH = "data\\TEXTURE\\number001.png";

//�萔
static const float NUMBER_SIZE_X = 70.0f;
static const float NUMBER_SIZE_Y = 120.0f;

//============================
//�����̃R���X�g���N�^
//============================
CNumber::CNumber(int nPriority) : CObject2D(nPriority)
{

}

//============================
//�����̃f�X�g���N�^
//============================
CNumber::~CNumber()
{

}

//============================
//�����̏�����
//============================
HRESULT CNumber::Init()
{
	//������
	CObject2D::Init();

	//UV���W�̐ݒ�i�������j
	CObject2D::SetTextureUV(0.0f, 0.1f, 0.0f, 1.0f);

	return S_OK;
}

//============================
//�����̏�����
//============================
void CNumber::Uninit()
{
	//������
	CObject2D::Uninit();
}

//============================
//�����̍X�V
//============================
void CNumber::Update()
{
	CObject2D::Update();
}

//============================
//�����̕`��
//============================
void CNumber::Draw()
{
	//�`��
	CObject2D::Draw(CNumber::TEXTUREPATH.c_str());
}

//============================
//�����̃N���G�C�g
//============================
CNumber* CNumber::Create(D3DXVECTOR3 pos, int number)
{
	//�|�C���^�p�̕ϐ�
	CNumber* pNumber = nullptr;

	//�������̊m��
	pNumber = new CNumber;

	//������
	pNumber->Init();

	//�ʒu�̐ݒ�
	pNumber->SetPos(pos);

	//�T�C�Y�̐ݒ�
	pNumber->SetSize({ NUMBER_SIZE_X, NUMBER_SIZE_Y, 0.0f});

	//�e�N�X�`���̐ݒ�
	pNumber->SetTexture(0);

	return pNumber;
}

//============================
//�����̃e�N�X�`���ݒ�
//============================
void CNumber::SetTexture(int Num)
{
	//UV���W�̐ݒ�
	CObject2D::SetTextureUV(Num / 10.0f, (Num + 1) / 10.0f, 0.0f, 1.0f);
}