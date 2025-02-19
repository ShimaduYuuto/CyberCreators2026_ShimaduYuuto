//======================================
//
//	�`���[�W�V���b�g�G�t�F�N�g�̕`��[effect_chargeshot.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "effect_chargeshot.h"
#include "manager.h"

//�萔
const std::string CEffect_ChargeShot::TEXTURE_PATH = "data\\TEXTURE\\charge000.png";

//============================
//�R���X�g���N�^
//============================
CEffect_ChargeShot::CEffect_ChargeShot()
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
CEffect_ChargeShot::~CEffect_ChargeShot()
{

}

//============================
//������
//============================
HRESULT CEffect_ChargeShot::Init()
{
	CObjectBillboard::Init();

	return S_OK;
}

//============================
//�I������
//============================
void CEffect_ChargeShot::Uninit()
{
	CObjectBillboard::Uninit();
}

//============================
//�X�V����
//============================
void CEffect_ChargeShot::Update()
{
	//���̍X�V
	CEffect_Billboard::Update();
}

//============================
//�`�揈��
//============================
void CEffect_ChargeShot::Draw()
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
CEffect_ChargeShot* CEffect_ChargeShot::Create(D3DXVECTOR3 pos)
{
	//�|�C���^�p�̕ϐ�
	CEffect_ChargeShot* pObject;

	//�������̊m��
	pObject = new CEffect_ChargeShot;

	//������
	pObject->Init();		//������
	pObject->SetPos(pos);	//�ʒu
	pObject->SetSize(D3DXVECTOR3(RADIUS, RADIUS, 0.0f));	//�T�C�Y

	return pObject;
}