//======================================
//
//	�^�C�g���̏���[title.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "title.h"
#include "manager.h"
#include "title_logo.h"
#include "sky.h"
#include "title_player.h"
#include "field.h"
#include "model.h"
#include "camera_title.h"
#include "ui_gamestart.h"

//============================
//�^�C�g���̃R���X�g���N�^
//============================
CTitle::CTitle() :
	m_pField(nullptr),
	m_pPlayer(nullptr)
{
	
}

//============================
//�^�C�g���̃f�X�g���N�^
//============================
CTitle::~CTitle()
{
	//�t�H�O�̐ݒ�
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
}

//============================
//�^�C�g���̏�����
//============================
HRESULT CTitle::Init()
{
	//�v���C���[�̐���
	if (m_pPlayer == nullptr)
	{
		m_pPlayer = CTitle_Player::Create();
	}

	//�t�B�[���h�̐���
	if (m_pField == nullptr)
	{
		m_pField = CField::Create({ 0.0f, 0.0f, 0.0f });
		m_pPlayer->SetPos(m_pField->ConvertMeshPos(m_pPlayer->GetPos()));
	}

	//���̑��̃I�u�W�F�N�g
	CTitle_Logo::Create({ 640.0f, 200.0f, 0.0f });
	CSky::Create();
	CModel::Create({ 0.0f, 0.0f, 3.0f }, { 0.0f, D3DX_PI * 0.5f, 0.0f }, CModel::MODEL_TYPE_FENCE);
	CUi_GameStart::Create();

	//�t�H�O�̐ݒ�
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);					//�L��
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP);		//�t�H�O���[�h�̐ݒ�
	pDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.1f));	//�F�̐ݒ�
	float m_fFogDensity = 0.0005f;
	pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&m_fFogDensity));

	//BGM
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_TITLE);

	//�J������؂�ւ�
	CManager::GetInstance()->ChangeCamera(new CCamera_Title());

	return S_OK;
}

//============================
//�^�C�g���̏I������
//============================
void CTitle::Uninit()
{
	//�v���C���[�̔j��
	if (m_pPlayer != nullptr)
	{
		m_pPlayer = nullptr;
	}

	//�t�B�[���h�̔j��
	if (m_pField != nullptr)
	{
		m_pField = nullptr;
	}

	//�I������
	CScene::Uninit();
}

//============================
//�^�C�g���̍X�V����
//============================
void CTitle::Update()
{
	//�}�l�[�W���[�̃C���X�^���X���擾
	CManager* pManager = CManager::GetInstance();

	//�t�F�[�h���I����Ă�����X�V
	if (CManager::GetInstance()->GetFade()->GetEnd())
	{
		//�G���^�[�ŉ�ʑJ��
		if (pManager->GetKeyboard()->GetTrigger(DIK_RETURN) || pManager->GetJoypad()->GetPress(CInputJoypad::JOYKEY_A) || pManager->GetJoypad()->GetPress(CInputJoypad::JOYKEY_START))
		{
			//�Q�[���ɉ�ʑJ��
			pManager->GetFade()->SetFade(CScene::MODE_GAME);
			m_pPlayer->SetMotion(CTitle_Player::TITLE_PLAYERMOTION_STANDUP);
		}
	}
}

//============================
//�^�C�g���̕`�揈��
//============================
void CTitle::Draw()
{

}