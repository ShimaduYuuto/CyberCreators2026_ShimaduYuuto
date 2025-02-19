//======================================
//
//	�`���[�W�G�t�F�N�g�̕`��[effect_charge.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "effect_charge.h"
#include "manager.h"

//�萔
const std::string CEffect_Charge::TEXTURE_PATH = "data\\TEXTURE\\charge001.png";

//============================
//�R���X�g���N�^
//============================
CEffect_Charge::CEffect_Charge()
{
	//���̏�����
	CAnimation::TextureInfo Info = { VERTICAL, HORIZONTAL, SPEED_UPDATE, LOOP };
	GetAnim().SetTextureInfo(Info);	//�ݒ�

	//�Q�[���^�O��ݒ�
	SetTag(CObject::TAG_GAME);
}

//============================
//�f�X�g���N�^
//============================
CEffect_Charge::~CEffect_Charge()
{

}

//============================
//������
//============================
HRESULT CEffect_Charge::Init()
{
	CObjectBillboard::Init();

	return S_OK;
}

//============================
//�I������
//============================
void CEffect_Charge::Uninit()
{
	CObjectBillboard::Uninit();
}

//============================
//�X�V����
//============================
void CEffect_Charge::Update()
{
	//���̍X�V
	CEffect_Billboard::Update();
}

//============================
//�`�揈��
//============================
void CEffect_Charge::Draw()
{
	//�`��p�̃��[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̎擾�p

	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���C�e�B���Ooff
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�e�N�X�`���`��
	CObjectBillboard::Draw(TEXTURE_PATH.c_str());

	//���C�e�B���Oon
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//============================
//��������
//============================
CEffect_Charge* CEffect_Charge::Create(D3DXVECTOR3 pos)
{
	//�|�C���^�p�̕ϐ�
	CEffect_Charge* pObject;

	//�������̊m��
	pObject = new CEffect_Charge;

	//������
	pObject->Init();		//������
	pObject->SetPos(pos);	//�ʒu
	pObject->SetSize(D3DXVECTOR3(RADIUS, RADIUS, 0.0f));	//�T�C�Y

	return pObject;
}