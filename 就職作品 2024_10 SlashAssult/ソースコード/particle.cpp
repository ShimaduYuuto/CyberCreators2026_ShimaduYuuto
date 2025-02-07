//======================================
//
//	�p�[�e�B�N���̏���[particle.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "particle.h"
#include "manager.h"

//�萔
const D3DXVECTOR3 CParticle::SIZE = { 5.0f, 5.0f, 0.0f };
const std::string CParticle::TEXTUREPATH = "data\\TEXTURE\\effect000.jpg";

//============================
//�p�[�e�B�N���̃R���X�g���N�^
//============================
CParticle::CParticle(int nPriority) : CObjectBillboard(nPriority),
	m_nLife(MAX_LIFE),
	m_fNormalSize(0.0f),
	m_nMaxLife(MAX_LIFE),
	m_fAttenuationValue(0.1f)
{
	//�Q�[���^�O��ݒ�
	SetTag(CObject::TAG_GAME);
}

//============================
//�p�[�e�B�N���̃f�X�g���N�^
//============================
CParticle::~CParticle()
{

}

//============================
//�p�[�e�B�N���̏�����
//============================
HRESULT CParticle::Init()
{
	CObjectBillboard::Init();
	SetSize(SIZE);
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	return S_OK;
}

//============================
//�p�[�e�B�N���̏I������
//============================
void CParticle::Uninit()
{
	CObjectBillboard::Uninit();
}

//============================
//�p�[�e�B�N���̍X�V
//============================
void CParticle::Update()
{
	//���������炷
	m_nLife--;

	float fSize = ((float)m_nLife / m_nMaxLife) * m_fNormalSize;

	SetSize({ fSize, fSize , 0.0f });

	//�������s������X�V���I����
	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}

	//��������
	D3DXVECTOR3 Move = GetMove();
	Move.x += (0.0f - Move.x) * m_fAttenuationValue;
	Move.z += (0.0f - Move.z) * m_fAttenuationValue;
	SetMove(Move);

	//�r���{�[�h�̍X�V����
	CObjectBillboard::Update();
}

//============================
//�p�[�e�B�N���̕`��
//============================
void CParticle::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���u�����f�B���O�����Z
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�t�H�O�̐ݒ�
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	CObjectBillboard::Draw(TEXTUREPATH.c_str());
	
	//���l�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//�t�H�O�̐ݒ�
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
}

//============================
//�p�[�e�B�N���̕`��
//============================
void CParticle::Draw(const char* texturepath)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���u�����f�B���O�����Z
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�t�H�O�̐ݒ�
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	CObjectBillboard::Draw(texturepath);

	//���l�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//�t�H�O�̐ݒ�
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
}

//============================
//�r���{�[�h�̃N���G�C�g
//============================
CParticle* CParticle::Create(D3DXVECTOR3 pos)
{
	//�|�C���^�p�̕ϐ�
	CParticle* pObject;

	//�������̊m��
	pObject = new CParticle;

	pObject->SetPos(pos);

	//������
	pObject->Init();

	return pObject;
}