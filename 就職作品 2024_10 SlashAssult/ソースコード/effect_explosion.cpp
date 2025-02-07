//======================================
//
//	�����̏���[effect_explosion.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "effect_explosion.h"
#include "game.h"
#include "manager.h"

//�萔
const std::string CEffect_Explosion::FILEPATH = "data\\TEXTURE\\SmashMesh000.png";

//============================
//�R���X�g���N�^
//============================
CEffect_Explosion::CEffect_Explosion(int nPriority) : CObjectDome(nPriority),
	m_fSizeRate(0.3f)
{
	//�Q�[���^�O��ݒ�
	SetTag(CObject::TAG_GAME);
}

//============================
//�f�X�g���N�^
//============================
CEffect_Explosion::~CEffect_Explosion()
{

}

//============================
//������
//============================
HRESULT CEffect_Explosion::Init()
{
	//������
	CObjectDome::Init();

	return S_OK;
}

//============================
//�I������
//============================
void CEffect_Explosion::Uninit()
{
	//�I������
	CObjectDome::Uninit();
}

//============================
//�X�V
//============================
void CEffect_Explosion::Update()
{
	m_fSizeRate += 0.01f;

	//�{���̐ݒ�
	SetRate(m_fSizeRate);

	//�Q�[���I�u�W�F�N�g�̋��ʏ����X�V
	CObjectDome::Update();
}

//============================
//�`��
//============================
void CEffect_Explosion::Draw()
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	//�J�����O���@��ύX
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	//�I�u�W�F�N�g�̕`��
	CObjectDome::Draw(FILEPATH.c_str());

	//�J�����O���@��ύX
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//============================
//�N���G�C�g
//============================
CEffect_Explosion* CEffect_Explosion::Create(D3DXVECTOR3 pos)
{
	//��ނɉ����ē��I�m��
	CEffect_Explosion* pEffect_Explosion = nullptr;

	//�N���G�C�g�̏���
	pEffect_Explosion = new CEffect_Explosion;

	//�p�����[�^�̐ݒ�
	pEffect_Explosion->SetPos(pos);		//�ʒu
	pEffect_Explosion->SetRadius(100.0f);	//���a
	pEffect_Explosion->SetRate(pEffect_Explosion->m_fSizeRate);

	//������
	pEffect_Explosion->Init();

	//�ݒ肵������Ԃ�
	return pEffect_Explosion;
}