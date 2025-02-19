//======================================
//
//	�������ۂ̉��G�t�F�N�g�̕`��[effect_runsmoke.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "effect_runsmoke.h"
#include "manager.h"

//�萔
const std::string CEffect_RunSmoke::TEXTURE_PATH = "data\\TEXTURE\\smoke000.png";

//============================
//�R���X�g���N�^
//============================
CEffect_RunSmoke::CEffect_RunSmoke()
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
CEffect_RunSmoke::~CEffect_RunSmoke()
{

}

//============================
//������
//============================
HRESULT CEffect_RunSmoke::Init()
{
	CObjectBillboard::Init();

	return S_OK;
}

//============================
//�I������
//============================
void CEffect_RunSmoke::Uninit()
{
	CObjectBillboard::Uninit();
}

//============================
//�X�V����
//============================
void CEffect_RunSmoke::Update()
{
	//���̍X�V
	CEffect_Billboard::Update();
}

//============================
//�`�揈��
//============================
void CEffect_RunSmoke::Draw()
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
CEffect_RunSmoke* CEffect_RunSmoke::Create(D3DXVECTOR3 pos)
{
	//�|�C���^�p�̕ϐ�
	CEffect_RunSmoke* pObject;

	//�������̊m��
	pObject = new CEffect_RunSmoke;

	//������
	pObject->Init();		//������
	pObject->SetPos(pos);	//�ʒu
	pObject->SetSize(D3DXVECTOR3(RADIUS, RADIUS, 0.0f));	//�T�C�Y

	return pObject;
}