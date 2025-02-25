//======================================
//
//	�t�H�O�̐ݒ�[fog.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "fog.h"
#include "manager.h"

//�萔�̏�����
const D3DXCOLOR CFog::DEFAULT_COLOR = D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.1f);

//============================
//�R���X�g���N�^
//============================
CFog::CFog() :
	m_Color(COLOR_RESET_ONE),	//�F
	m_fDensity(FLOAT_ZERO)		//���x
{
	//������
	m_Color = DEFAULT_COLOR;		//�F
	m_fDensity = DEFAULT_DENDITY;	//���x
}

//============================
//�f�X�g���N�^
//============================
CFog::~CFog()
{

}

//============================
//�t�H�O��ݒ�
//============================
void CFog::SetFog()
{
	//�t�H�O�̐ݒ�
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�̎擾
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);						//�L��
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP);			//�t�H�O���[�h�̐ݒ�
	pDevice->SetRenderState(D3DRS_FOGCOLOR, m_Color);					//�F�̐ݒ�
	pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&m_fDensity));	//���x�̐ݒ�
}

//============================
//�t�H�O������
//============================
void CFog::ClearFog()
{
	//�t�H�O�̉���
	LPDIRECT3DDEVICE9 pDevice;										//�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);				//�t�H�O������
}