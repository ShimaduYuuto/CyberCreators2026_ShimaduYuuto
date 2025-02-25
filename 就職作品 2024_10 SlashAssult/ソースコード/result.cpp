//======================================
//
//	���U���g�̏���[result.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "result.h"
#include "manager.h"
#include "result_bg.h"
#include "sky.h"
#include "model.h"
#include "cleartime.h"
#include "oldpaper.h"
#include "rank.h"
#include "result_txtui.h"
#include "camera_result.h"
#include "fog.h"

//�萔
const D3DXVECTOR3 CResult::TIME_POS = { SCREEN_WIDTH * 0.4f, 355.0f, 0.0f };

//============================
//���U���g�̃R���X�g���N�^
//============================
CResult::CResult() :
	m_pField(nullptr)
{
	
}

//============================
//���U���g�̃f�X�g���N�^
//============================
CResult::~CResult()
{
	//�t�H�O�̉���
	CFog::GetInstance()->ClearFog();
}

//============================
//���U���g�̏�����
//============================
HRESULT CResult::Init()
{
	//�t�B�[���h�̐���
	if (m_pField == nullptr)
	{
		m_pField = CField::Create({ 0.0f, 0.0f, 0.0f });
	}

	//�N���A�^�C���̏�����
	CClearTime::GetInstance()->SetPos(TIME_POS);
	CClearTime::GetInstance()->Init();

	//���̑��̃I�u�W�F�N�g
	CSky::Create();
	CModel::Create({ 0.0f, 0.0f, 3.0f }, { 0.0f, D3DX_PI * 0.5f, 0.0f }, CModel::MODEL_TYPE_FENCE);
	COldPaper::Create();
	CRank::Create();
	CResult_Txtui::Create();

	//�t�H�O�̐ݒ�
	CFog::GetInstance()->SetFog();

	//BGM
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_RESULT);

	//�J������؂�ւ�
	CManager::GetInstance()->ChangeCamera(new CCamera_Result());
	
	return S_OK;
}

//============================
//���U���g�̏I������
//============================
void CResult::Uninit()
{
	//�t�B�[���h�̔j��
	if (m_pField != nullptr)
	{
		m_pField = nullptr;
	}

	//�I������
	CScene::Uninit();
}

//============================
//���U���g�̍X�V����
//============================
void CResult::Update()
{
	//�}�l�[�W���[�̃C���X�^���X���擾
	CManager* pManager = CManager::GetInstance();

	//�t�F�[�h���I����Ă�����X�V
	if (CManager::GetInstance()->GetFade()->GetEnd())
	{
		//�G���^�[�ŉ�ʑJ��
		if (pManager->GetKeyboard()->GetTrigger(DIK_RETURN) || pManager->GetJoypad()->GetPress(CInputJoypad::JOYKEY_A) || pManager->GetJoypad()->GetPress(CInputJoypad::JOYKEY_START))
		{
			//�^�C�g���ɉ�ʑJ��
			pManager->GetFade()->SetFade(CScene::MODE_TITLE);
		}
	}
}

//============================
//���U���g�̕`�揈��
//============================
void CResult::Draw()
{

}