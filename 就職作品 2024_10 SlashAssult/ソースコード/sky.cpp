//======================================
//
//	��̏���[sky.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "sky.h"
#include "manager.h"

//�萔
const std::string CSky::FILEPATH = "data\\TEXTURE\\sky001.jpg";
const D3DXVECTOR3 CSky::POS = { 0.0f, -100.0f, 0.0f };

//============================
//�R���X�g���N�^
//============================
CSky::CSky(int nPriority) : CObjectDome(nPriority)
{

}

//============================
//�f�X�g���N�^
//============================
CSky::~CSky()
{

}

//============================
//������
//============================
HRESULT CSky::Init()
{
	//������
	CObjectDome::Init();

	return S_OK;
}

//============================
//�I������
//============================
void CSky::Uninit()
{
	//�I������
	CObjectDome::Uninit();
}

//============================
//�X�V
//============================
void CSky::Update()
{
	CObjectDome::Update();
}

//============================
//�`��
//============================
void CSky::Draw()
{
	//�f�o�C�X�̎擾
	 LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�I�u�W�F�N�g�̕`��
	CObjectDome::Draw(FILEPATH.c_str());

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//============================
//�N���G�C�g
//============================
CSky* CSky::Create()
{
	//��ނɉ����ē��I�m��
	CSky* pSky = nullptr;

	//�N���G�C�g�̏���
	pSky = new CSky;

	pSky->SetRadius(RADIUS);		//���a
	pSky->SetRate(RATE);			//�{��
	pSky->SetPos(D3DXVECTOR3(POS));	//�ʒu

	//������
	pSky->Init();

	//�ݒ肵������Ԃ�
	return pSky;
}