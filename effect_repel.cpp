//======================================
//
//	�q�b�g�G�t�F�N�g�̕`��[effect_repel.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "effect_repel.h"
#include "manager.h"

//�萔
const std::string CEffect_Repel::TEXTURE_PATH = "data\\TEXTURE\\repel000.png";

//============================
//�R���X�g���N�^
//============================
CEffect_Repel::CEffect_Repel() :
	m_Anim()
{
	//���̏�����
	CAnimation::TextureInfo Info = { VERTICAL, HORIZONTAL, SPEED_UPDATE, LOOP };
	m_Anim.SetTextureInfo(Info);
}

//============================
//�f�X�g���N�^
//============================
CEffect_Repel::~CEffect_Repel()
{

}

//============================
//������
//============================
HRESULT CEffect_Repel::Init()
{
	CObjectBillboard::Init();

	return S_OK;
}

//============================
//�I������
//============================
void CEffect_Repel::Uninit()
{
	CObjectBillboard::Uninit();
}

//============================
//�X�V����
//============================
void CEffect_Repel::Update()
{
	//�e�N�X�`�����W�̍X�V
	D3DXVECTOR2 UV = m_Anim.UpdateAnim();
	SetTextureUV(
		UV.x * m_Anim.GetTextureCount().nHorizontalAnimCount,
		UV.x * (m_Anim.GetTextureCount().nHorizontalAnimCount + 1),
		UV.y * m_Anim.GetTextureCount().nVerticalAnimCount,
		UV.y * (m_Anim.GetTextureCount().nVerticalAnimCount + 1));

	//�I��
	if (m_Anim.GetEnd())
	{
		Uninit();
	}
}

//============================
//�`�揈��
//============================
void CEffect_Repel::Draw()
{
	//�`��p�̃��[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̎擾�p

	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�e�N�X�`���`��
	CObjectBillboard::Draw(TEXTURE_PATH.c_str());

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//============================
//��������
//============================
CEffect_Repel* CEffect_Repel::Create(D3DXVECTOR3 pos)
{
	//�|�C���^�p�̕ϐ�
	CEffect_Repel* pObject;

	//�������̊m��
	pObject = new CEffect_Repel;

	//������
	pObject->Init();		//������
	pObject->SetPos(pos);	//�ʒu
	pObject->SetSize(D3DXVECTOR3(RADIUS, RADIUS, 0.0f));	//�T�C�Y

	return pObject;
}