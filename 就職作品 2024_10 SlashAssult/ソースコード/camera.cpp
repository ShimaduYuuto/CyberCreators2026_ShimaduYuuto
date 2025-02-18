//======================================
//
//	�J�����̏���[camera.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "camera.h"
#include "manager.h"
#include "main.h"

//�萔�̐ݒ�
const float CCamera::LENGTH_NORMAL = 320.0f;				//�ʏ�J�����̋���
const float CCamera::LENGTH_RUSH = LENGTH_NORMAL * 0.7f;	//���b�V���J�����̋���

//============================
//�J�����̃R���X�g���N�^
//============================
CCamera::CCamera() :
	m_posV(),									//���_�̏�����
	m_posR(),									//�����_�̏�����
	m_vecU(D3DXVECTOR3(0.0f, 1.0f, 0.0f)),		//��x�N�g���̏�����
	m_mtxProjection(),							//�v���W�F�N�V�����}�g���b�N�X�̏�����
	m_mtxView(),								//�r���[�}�g���b�N�X�̏�����
	m_Viewport(),								//�r���[�|�[�g�̏�����
	m_fShakeFrameCount(0.0f),					//�h��鎞��
	m_rot(),									//����
	m_fLength(0.0f)								//����
{

}

//============================
//�J�����̃f�X�g���N�^
//============================
CCamera::~CCamera()
{

}

//============================
//�J�����̏�����
//============================
HRESULT CCamera::Init()
{
	//�����o�ϐ��̏����ݒ�
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���_�̏�����
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�����_�̏�����
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			//��x�N�g���̏�����
	m_mtxProjection = {};							//�v���W�F�N�V�����}�g���b�N�X�̏�����
	m_mtxView = {};									//�r���[�}�g���b�N�X�̏�����
	m_fShakeFrameCount = 0.0f;						//�h�炷����
	m_rot = { VEC3_RESET_ZERO };					//����
	m_fLength = LENGTH_NORMAL;						//����

	//�r���[�|�[�g�̏�����
	m_Viewport.X = 0;
	m_Viewport.Y = 0;
	m_Viewport.Width = SCREEN_WIDTH;
	m_Viewport.Height = SCREEN_HEIGHT;
	m_Viewport.MaxZ = 1.0f;
	m_Viewport.MinZ = 0.0f;

	return S_OK;
}

//============================
//�J�����̏I������
//============================
void CCamera::Uninit()
{
	
}

//============================
//�J�����̍X�V����
//============================
void CCamera::Update()
{
	
}

//============================
//�J�����̐ݒ菈��
//============================
void CCamera::SetCamera()
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X���擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�J�����ɕ`�悷�鋗��
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		20000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�h��̑傫���̐ݒ�
	D3DXVECTOR3 adjust = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�h��̃J�E���g���c���Ă���Ȃ珈��
	if (m_fShakeFrameCount > 0.0f)
	{
		//�f�N�������g
		m_fShakeFrameCount--;
		
		//�h��̑傫���̐ݒ�
		adjust = D3DXVECTOR3(CRandom::GetRandom(0.0f, m_fShakeMagnitude), CRandom::GetRandom(0.0f, m_fShakeMagnitude), 0.0f);
	}

	//�J�����̗h�ꂽ���̕ϐ�
	D3DXVECTOR3 ShakePosV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 ShakePosR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�J�����̗h�ꂽ���̈ʒu
	ShakePosV = m_posV + adjust;
	ShakePosR = m_posR + adjust;

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&ShakePosV, //���_
		&ShakePosR, //�����_
		&m_vecU);//������̃x�N�g��

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	pDevice->SetViewport(&m_Viewport);
}

//============================
//�J�����ɉf���Ă��邩��Ԃ�
//============================
bool CCamera::GetViewObject(D3DXMATRIX mtx)
{
	//�Ԃ��p�̕ϐ�
	bool bScreen = false;

	D3DXVECTOR3 ScreenPos, MtxPos;
	ScreenPos = MtxPos = { 0.0f, 0.0f, 0.0f };
	
	D3DXVec3Project(
		&ScreenPos,
		&MtxPos,
		&m_Viewport,
		&m_mtxProjection,
		&m_mtxView,
		&mtx
	);

	//��ʂ͈͓̔��ɂ���Ȃ�
	if (ScreenPos.x >= 0.0f && ScreenPos.x <= SCREEN_WIDTH
		&& ScreenPos.y >= 0.0f && ScreenPos.y <= SCREEN_HEIGHT)
	{
		bScreen = true;
	}

	return bScreen;
}

//============================
//�J�����ɉf���Ă��邩��Ԃ�
//============================
bool CCamera::GetViewObject(D3DXVECTOR3 pos)
{
	//�Ԃ��p�̕ϐ�
	bool bScreen = false;

	D3DXVECTOR3 ScreenPos, MtxPos;
	ScreenPos = MtxPos = { 0.0f, 0.0f, 0.0f };
	D3DXMATRIX mtx;

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtx, pos.x, pos.y, pos.z);

	D3DXVec3Project(
		&ScreenPos,
		&MtxPos,
		&m_Viewport,
		&m_mtxProjection,
		&m_mtxView,
		&mtx
	);

	//��ʂ͈͓̔��ɂ���Ȃ�
	if (ScreenPos.x >= 0.0f && ScreenPos.x <= SCREEN_WIDTH
		&& ScreenPos.y >= 0.0f && ScreenPos.y <= SCREEN_HEIGHT)
	{
		bScreen = true;
	}

	return bScreen;
}

//============================
//�J�����̗h��̐ݒ�
//============================
void CCamera::SetShake(float frame, float magnitude)
{
	//�p�����[�^�̐ݒ�
	m_fShakeFrameCount = frame;		//�t���[���J�E���g
	m_fShakeMagnitude = magnitude;	//�h��̑傫��
}