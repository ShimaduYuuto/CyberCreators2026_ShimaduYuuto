//======================================
//
//	���b�V���`�����X��UI�̕`��[ui_rushchance.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "ui_rushchance.h"
#include "manager.h"

//�萔
const std::string CUi_RushChance::TEXTURE_PATH = "data\\TEXTURE\\ui_rushchance000.png";

//============================
//�R���X�g���N�^
//============================
CUi_RushChance::CUi_RushChance(int nPriority) : CObjectBillboard(nPriority),
	m_Anim(),
	m_TargetPos(nullptr)
{
	//���̏�����
	CAnimation::TextureInfo Info = { VERTICAL, HORIZONTAL, SPEED_UPDATE, LOOP };
	m_Anim.SetTextureInfo(Info);
}

//============================
//�f�X�g���N�^
//============================
CUi_RushChance::~CUi_RushChance()
{

}

//============================
//������
//============================
HRESULT CUi_RushChance::Init()
{
	CObjectBillboard::Init();

	return S_OK;
}

//============================
//�I������
//============================
void CUi_RushChance::Uninit()
{
	CObjectBillboard::Uninit();
}

//============================
//�X�V����
//============================
void CUi_RushChance::Update()
{
	//�e�N�X�`�����W�̍X�V
	D3DXVECTOR2 UV = m_Anim.UpdateAnim();
	SetTextureUV(
		UV.x * m_Anim.GetTextureCount().nHorizontalAnimCount,
		UV.x * (m_Anim.GetTextureCount().nHorizontalAnimCount + 1),
		UV.y * m_Anim.GetTextureCount().nVerticalAnimCount,
		UV.y * (m_Anim.GetTextureCount().nVerticalAnimCount + 1));

	SetPos(*m_TargetPos + D3DXVECTOR3{100.0f, 0.0f, 0.0f});
}

//============================
//�`�揈��
//============================
void CUi_RushChance::Draw()
{
	//�`��p�̃��[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̎擾�p

	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Z�̔�r���@�ύX
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//�e�N�X�`���`��
	CObjectBillboard::Draw(TEXTURE_PATH.c_str());

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//Z�̔�r���@�ύX
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}

//============================
//��������
//============================
CUi_RushChance* CUi_RushChance::Create(D3DXVECTOR3* pos)
{
	//�|�C���^�p�̕ϐ�
	CUi_RushChance* pObject;

	//�������̊m��
	pObject = new CUi_RushChance();

	//������
	pObject->Init();			//������
	pObject->m_TargetPos = pos;	//�^�[�Q�b�g�̈ʒu
	pObject->SetPos(*pos);		//�ʒu
	pObject->SetSize(D3DXVECTOR3(RADIUS, RADIUS, 0.0f));	//�T�C�Y

	return pObject;
}