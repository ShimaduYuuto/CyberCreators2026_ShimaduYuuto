//======================================
//
//	�X�^���G�t�F�N�g�̕`��[effect_stan.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "effect_stan.h"
#include "manager.h"

//�萔
const std::string CEffect_Stan::TEXTURE_PATH = "data\\TEXTURE\\staneffect000.png";

//============================
//�R���X�g���N�^
//============================
CEffect_Stan::CEffect_Stan() :
	m_pmtxParent(nullptr)
{
	//�Q�[���^�O��ݒ�
	SetTag(CObject::TAG_GAME);
}

//============================
//�f�X�g���N�^
//============================
CEffect_Stan::~CEffect_Stan()
{

}

//============================
//������
//============================
HRESULT CEffect_Stan::Init()
{
	CObjectCylinder::Init();

	return S_OK;
}

//============================
//�I������
//============================
void CEffect_Stan::Uninit()
{
	CObjectCylinder::Uninit();
}

//============================
//�X�V����
//============================
void CEffect_Stan::Update()
{
	//��]
	D3DXVECTOR3 Rot = GetRot();
	Rot.y += 0.05f;
	SetRot(Rot);

	//���̍X�V
	CObjectCylinder::Update();
}

//============================
//�`�揈��
//============================
void CEffect_Stan::Draw()
{
	//�`��p�̃��[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̎擾�p

	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���C�e�B���O�I�t
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���ʃJ�����O
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//�e�N�X�`���`��
	CObjectCylinder::Draw(TEXTURE_PATH.c_str());

	//���C�e�B���O�I��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//�ЖʃJ�����O
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//============================
//�}�g���b�N�X�̌v�Z
//============================
void CEffect_Stan::MtxCalculation()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxObject;	//�v�Z�p�}�g���b�N�X
	mtxObject = GetMtx();					//���g�̃}�g���b�N�X

	//���[���h�̏�����
	D3DXMatrixIdentity(&mtxObject);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);

	D3DXMatrixMultiply(&mtxObject, &mtxObject, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);

	D3DXMatrixMultiply(&mtxObject, &mtxObject, &mtxTrans);

	//���[���h�ϊ��s��Ɛe�̍s����������킹��
	D3DXMatrixMultiply(&mtxObject, &mtxObject, m_pmtxParent);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxObject);

	//�}�g���b�N�X�̐ݒ�
	SetMtx(mtxObject);
}

//============================
//��������
//============================
CEffect_Stan* CEffect_Stan::Create(D3DXVECTOR3 pos, D3DXMATRIX* mtx)
{
	//�|�C���^�p�̕ϐ�
	CEffect_Stan* pObject;

	//�������̊m��
	pObject = new CEffect_Stan;

	//�p�����[�^�̐ݒ�
	pObject->SetPos(pos);			//�ʒu
	pObject->SetRadius(RADIUS);		//���a
	pObject->SetHeight(HEIGHT);		//����
	pObject->m_pmtxParent = mtx;	//�e�̃}�g���b�N�X

	//������
	pObject->Init();				//������

	return pObject;
}