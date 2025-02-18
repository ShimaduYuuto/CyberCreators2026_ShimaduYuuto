//======================================
//
//	�����蔻��̈ʒu�̉���[collision_view.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "collision_view.h"
#include "manager.h"

//�萔
const std::string CCollision_View::TEXTURE_PATH = "data\\TEXTURE\\circle000.png";

//============================
//�R���X�g���N�^
//============================
CCollision_View::CCollision_View() :
	m_fRadius(),	//���a
	m_Pos()			//�ʒu
{

}

//============================
//�f�X�g���N�^
//============================
CCollision_View::~CCollision_View()
{

}

//============================
//������
//============================
HRESULT CCollision_View::Init()
{
	CObjectBillboard::Init();

	return S_OK;
}

//============================
//�I������
//============================
void CCollision_View::Uninit()
{
	CObjectBillboard::Uninit();
}

//============================
//�X�V����
//============================
void CCollision_View::Update()
{
	//�ʒu�̐ݒ�
	SetPos(*m_Pos);
	CObjectBillboard::Update();
}

//============================
//�`�揈��
//============================
void CCollision_View::Draw()
{
	CObjectBillboard::Draw(TEXTURE_PATH.c_str());
}

//============================
//�N���G�C�g
//============================
CCollision_View* CCollision_View::Create(float radius, D3DXVECTOR3* pos)
{
	//�|�C���^�p�̕ϐ�
	CCollision_View* pCollision_View = nullptr;
	pCollision_View = new CCollision_View;

	//������
	pCollision_View->Init();

	//�p�����[�^�̑��
	pCollision_View->m_fRadius = radius;
	pCollision_View->m_Pos = pos;
	pCollision_View->SetSize(D3DXVECTOR3(radius * 2.0f, radius * 2.0f, 0.0f));
	pCollision_View->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));

	return pCollision_View;
}