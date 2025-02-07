//======================================
//
//	���S�G�t�F�N�g�̕`��[effect_death.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "effect_death.h"
#include "manager.h"

//�萔
const std::string CEffect_Death::TEXTURE_PATH = "data\\TEXTURE\\death002.png";

//============================
//�R���X�g���N�^
//============================
CEffect_Death::CEffect_Death() :
	m_Anim()
{
	//���̏�����
	CAnimation::TextureInfo Info = { VERTICAL, HORIZONTAL, SPEED_UPDATE, LOOP };
	m_Anim.SetTextureInfo(Info);

	//�Q�[���^�O��ݒ�
	SetTag(CObject::TAG_GAME);
}

//============================
//�f�X�g���N�^
//============================
CEffect_Death::~CEffect_Death()
{
	
}

//============================
//������
//============================
HRESULT CEffect_Death::Init()
{
	CObjectBillboard::Init();

	return S_OK;
}

//============================
//�I������
//============================
void CEffect_Death::Uninit()
{
	CObjectBillboard::Uninit();
}

//============================
//�X�V����
//============================
void CEffect_Death::Update()
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
void CEffect_Death::Draw()
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
CEffect_Death* CEffect_Death::Create(D3DXVECTOR3 pos)
{
	//�|�C���^�p�̕ϐ�
	CEffect_Death* pObject;

	//�������̊m��
	pObject = new CEffect_Death;

	//������
	pObject->Init();										//������
	pObject->SetPos(pos);									//�ʒu
	pObject->SetSize(D3DXVECTOR3(RADIUS, RADIUS, 0.0f));	//�T�C�Y

	return pObject;
}