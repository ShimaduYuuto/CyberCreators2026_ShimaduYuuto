//======================================
//
//	���f���p�[�c�̏���[modelparts.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "modelparts.h"
#include "manager.h"
#include "game.h"
#include "character.h"

//============================
//���f���p�[�c�̃R���X�g���N�^
//============================
CModelparts::CModelparts(int nPriority) : CObjectX(nPriority),
	m_pParent(nullptr),
	m_fAlpha(0.0f),
	m_ModelPartsName()
{
	m_fAlpha = 1.0f;
}

//============================
//���f���p�[�c�̃f�X�g���N�^
//============================
CModelparts::~CModelparts()
{

}

//============================
//���f���p�[�c�̏�����
//============================
HRESULT CModelparts::Init()
{
	//������
	CObjectX::Init();

	return S_OK;
}

//============================
//���f���p�[�c�̏I������
//============================
void CModelparts::Uninit()
{
	//�I��
	CObjectX::Uninit();
}

//============================
//���f���p�[�c�̍X�V
//============================
void CModelparts::Update()
{
	//�Q�[���I�u�W�F�N�g�̋��ʏ����X�V
	CObject::Update();
}

//============================
//���f���p�[�c�̕`��
//============================
void CModelparts::Draw()
{
	//�p�[�c�������Ă���N���X�ŕ`�悷��̂ŋ�
}

//============================
//���f���p�[�c�̕`��
//============================
void CModelparts::Draw(int damagestate, int damagecount)
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;										//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;												//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;													//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxWorld = GetMtx();										//�}�g���b�N�X�̎擾
	D3DXVECTOR3 pos = GetPos();											//�ʒu�̎擾
	D3DXVECTOR3 rot = GetRot();											//�����̎擾

	//X�t�@�C���̓ǂݍ���
	CXfile* pCXfile = CManager::GetInstance()->GetXfile();

	//���[���h�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	//�e�̍s��̎擾
	D3DXMATRIX mtxParent;

	//�e������Ȃ�
	if (m_pParent != nullptr)
	{
		//�e�̃��[���h�ϊ��s����擾
		mtxParent = m_pParent->GetMtx();
	}
	else
	{
		//�Ō�̃��[���h�ϊ��s����擾(�v���C���[�̍s��)
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	//�p�[�c�̃��[���h�ϊ��s��Ɛe�̍s����������킹��
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxParent);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)pCXfile->GetAddress(pCXfile->Regist(m_ModelPartsName.c_str())).pBuffmat->GetBufferPointer();

	//�e�N�X�`���̐����J�E���g
	int nTextureCount = 0;

	//�}�e���A���̐���������
	for (int nCntMat = 0; nCntMat < (int)pCXfile->GetAddress(pCXfile->Regist(m_ModelPartsName.c_str())).dwNumMat; nCntMat++)
	{
		//�����x�𔽉f
		pMat[nCntMat].MatD3D.Diffuse.a = m_fAlpha;

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`������������
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, pCXfile->GetAddress(pCXfile->Regist(m_ModelPartsName.c_str())).pTexture[nTextureCount]);

			//�e�N�X�`���p�̃J�E���g��i�߂�
			nTextureCount++;
		}
		else
		{
			//�e�N�X�`����ݒ肵�Ȃ�
			pDevice->SetTexture(0, NULL);
		}

		//�Q�[���V�[���̃I�u�W�F�N�g(�p�[�c)�̕`��
		pCXfile->GetAddress(pCXfile->Regist(m_ModelPartsName.c_str())).pMesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

	//�}�g���b�N�X�̐ݒ�
	SetMtx(mtxWorld);
}

//============================
//���f���p�[�c�̃N���G�C�g
//============================
CModelparts* CModelparts::Create(const char* filename, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//��ނɉ����ē��I�m��
	CModelparts* pModelparts = NULL;

	//�N���G�C�g�̏���
	pModelparts = new CModelparts;

	//������
	pModelparts->Init();

	//�p�����[�^�̐ݒ�
	pModelparts->m_ModelPartsName = filename;	//�t�@�C����
	pModelparts->SetPos(pos);					//�ʒu
	pModelparts->SetRot(rot);					//����
	pModelparts->m_pParent = nullptr;			//�e�̃|�C���^

	//�ݒ肵������Ԃ�
	return pModelparts;
}

//============================
//���[���h���W�̈ʒu���擾
//============================
D3DXVECTOR3 CModelparts::GetWorldPos()
{
	//���[�J���ϐ��錾
	D3DXMATRIX mtxWorld = GetMtx();		//�}�g���b�N�X�̎擾

	//���[���h�ϊ���̍��W
	return D3DXVECTOR3(mtxWorld._41, mtxWorld._42, mtxWorld._43);
}