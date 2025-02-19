//======================================
//
//	�K�[�h�G�t�F�N�g�̕`��[effect_guard.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "effect_guard.h"
#include "manager.h"

//�萔
const std::string CEffect_Guard::TEXTURE_PATH = "data\\TEXTURE\\barrier003.png";

//============================
//�R���X�g���N�^
//============================
CEffect_Guard::CEffect_Guard() :
	m_bEnd(false),
	m_nRatioInterpolationCount(0),
	m_pTargetPos(nullptr)
{
	//���̏�����
	CAnimation::TextureInfo Info = { VERTICAL, HORIZONTAL, SPEED_UPDATE, LOOP };
	GetAnim().SetTextureInfo(Info);

	//�Q�[���^�O��ݒ�
	SetTag(CObject::TAG_GAME);
}

//============================
//�f�X�g���N�^
//============================
CEffect_Guard::~CEffect_Guard()
{
	m_pTargetPos = nullptr;
}

//============================
//������
//============================
HRESULT CEffect_Guard::Init()
{
	CObjectBillboard::Init();

	return S_OK;
}

//============================
//�I������
//============================
void CEffect_Guard::Uninit()
{
	CObjectBillboard::Uninit();
}

//============================
//�X�V����
//============================
void CEffect_Guard::Update()
{
	//���̍X�V
	CEffect_Billboard::Update();

	//�ʒu�̐ݒ�
	SetPos(*m_pTargetPos);

	//�T�C�Y�{���̍X�V
	UpdateSizeRatio();
}

//============================
//�T�C�Y�{���̍X�V
//============================
void CEffect_Guard::UpdateSizeRatio()
{
	//�������Ȃ�{�����X�V
	if (!m_bEnd)
	{
		//��Ԃ��I����Ă����甲����
		if (m_nRatioInterpolationCount > TIME_INTERPOLATION_RATIO)
		{
			return;
		}

		//�{����ݒ肵�ăJ�E���g�A�b�v
		SetRatio(m_nRatioInterpolationCount / (float)TIME_INTERPOLATION_RATIO);
		m_nRatioInterpolationCount++;
	}
	else
	{
		//��Ԃ��I����Ă�����j��
		if (m_nRatioInterpolationCount < 0)
		{
			Uninit();
			return;
		}

		//�{����ݒ肵�ăJ�E���g�_�E��
		SetRatio(m_nRatioInterpolationCount / (float)TIME_INTERPOLATION_RATIO);
		m_nRatioInterpolationCount--;
	}
}

//============================
//�`�揈��
//============================
void CEffect_Guard::Draw()
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
CEffect_Guard* CEffect_Guard::Create(D3DXVECTOR3* pos)
{
	//�|�C���^�p�̕ϐ�
	CEffect_Guard* pObject;

	//�������̊m��
	pObject = new CEffect_Guard;

	//������
	pObject->Init();							//������
	pObject->m_pTargetPos = pos;				//�Ώۂ̈ʒu
	pObject->SetPos(*pObject->m_pTargetPos);	//�ʒu
	pObject->SetSize(D3DXVECTOR3(RADIUS, RADIUS, 0.0f));	//�T�C�Y
	pObject->SetRatio(0.0f);//�{����0����X�^�[�g������

	return pObject;
}