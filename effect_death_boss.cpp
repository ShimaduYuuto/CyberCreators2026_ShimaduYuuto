//======================================
//
//	���S�G�t�F�N�g�̕`��[effect_death_boss.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "effect_death_boss.h"
#include "manager.h"

//�萔
const std::string CEffect_Death_Boss::TEXTURE_PATH = "data\\TEXTURE\\death_boss000.png";

//============================
//�R���X�g���N�^
//============================
CEffect_Death_Boss::CEffect_Death_Boss() :
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
CEffect_Death_Boss::~CEffect_Death_Boss()
{

}

//============================
//������
//============================
HRESULT CEffect_Death_Boss::Init()
{
	CObjectBillboard::Init();

	return S_OK;
}

//============================
//�I������
//============================
void CEffect_Death_Boss::Uninit()
{
	CObjectBillboard::Uninit();
}

//============================
//�X�V����
//============================
void CEffect_Death_Boss::Update()
{
	//�ʒu�̐ݒ�
	SetPos(*m_TargetPos);

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
void CEffect_Death_Boss::Draw()
{
	//�`��p�̃��[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̎擾�p

	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���C�e�B���O�I�t
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	//�e�N�X�`���`��
	CObjectBillboard::Draw(TEXTURE_PATH.c_str());

	//���C�e�B���O�I��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//���e�X�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//============================
//��������
//============================
CEffect_Death_Boss* CEffect_Death_Boss::Create(D3DXVECTOR3* pos)
{
	//�|�C���^�p�̕ϐ�
	CEffect_Death_Boss* pObject;

	//�������̊m��
	pObject = new CEffect_Death_Boss;

	//������
	pObject->Init();										//������
	pObject->m_TargetPos = pos;								//�Ώۂ̈ʒu
	pObject->SetPos(*pos);									//�ʒu
	pObject->SetSize(D3DXVECTOR3(RADIUS, RADIUS, 0.0f));	//�T�C�Y

	return pObject;
}