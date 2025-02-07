//======================================
//
//	��̏���[shadow.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "shadow.h"
#include "game.h"
#include "manager.h"

//�萔
const std::string CShadow::FILEPATH = "data\\TEXTURE\\effect000.jpg";
const D3DXCOLOR CShadow::COLOR = { 1.0f, 1.0f, 1.0f, 0.5f };

//============================
//�R���X�g���N�^
//============================
CShadow::CShadow(int nPriority) : CObject3D(nPriority),
	m_TargetPos(),
	m_bDrawJudge(true)
{

}

//============================
//�f�X�g���N�^
//============================
CShadow::~CShadow()
{
	//�|�C���^��null
	if (m_TargetPos != nullptr)
	{
		m_TargetPos = nullptr;
	}
}

//============================
//������
//============================
HRESULT CShadow::Init()
{
	//������
	CObject3D::Init();

	return S_OK;
}

//============================
//�I������
//============================
void CShadow::Uninit()
{
	//�I������
	CObject3D::Uninit();
}

//============================
//�X�V
//============================
void CShadow::Update()
{
	//�ʒu�̍X�V
	D3DXVECTOR3 Pos = *m_TargetPos;		//�^�[�Q�b�g�̈ʒu���擾
	D3DXVECTOR3 Rot = GetRot();			//����

	Pos.y = 0.01f;		//���������ύX

	//�Q�[���V�[���Ȃ�t�B�[���h�̍����Ɉʒu��␳
	if (CManager::GetInstance()->GetScene()->GetMode() == CScene::MODE_GAME)
	{
		CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();
		pGame->GetGameField()->MeshCollision(Pos, Rot);
		Pos.y += 1.0f;												//���܂�Ȃ��悤�ɏ���������������
	}

	//�ʒu�ƌ�����ݒ�
	SetPos(Pos);
	SetRot(Rot);

	CObject3D::Update();
}

//============================
//�`��
//============================
void CShadow::Draw()
{
	//�`�悵�Ȃ�����Ȃ甲����
	if (!m_bDrawJudge) return;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//Z�̔�r���@�ύX
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//Z�o�b�t�@�ɏ������܂Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//�t�H�O�̐ݒ�
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	//�I�u�W�F�N�g�̕`��
	CObject3D::Draw(FILEPATH.c_str());

	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//Z�̔�r���@�ύX
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//Z�o�b�t�@�ɏ�������
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//�t�H�O�̐ݒ�
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
}

//============================
//�N���G�C�g
//============================
CShadow* CShadow::Create(D3DXVECTOR3* pos, float radius)
{
	//��ނɉ����ē��I�m��
	CShadow* pShadow = nullptr;

	//�N���G�C�g�̏���
	pShadow = new CShadow;

	//������
	pShadow->Init();

	pShadow->SetSize(D3DXVECTOR3(radius * 2.0f, 0.0f, radius * 2.0f), CObject3D::TYPE_FLOOR);	//�T�C�Y
	pShadow->SetRate(1.0f);												//�T�C�Y�{��
	pShadow->SetPos(D3DXVECTOR3(pos->x, 1.0f, pos->z));					//�ʒu
	pShadow->m_TargetPos = pos;											//�Ώۂ̈ʒu
	pShadow->SetColor(COLOR);											//�F�̐ݒ�

	//�ݒ肵������Ԃ�
	return pShadow;
}