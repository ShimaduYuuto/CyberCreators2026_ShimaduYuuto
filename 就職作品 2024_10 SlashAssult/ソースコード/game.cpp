//======================================
//
//	�Q�[���̏���[game.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "game.h"
#include "manager.h"
#include "object2D.h"
#include "player.h"
#include "enemy.h"
#include "explodingbarrel.h"
#include "objectdome.h"
#include "spawn_enemy.h"
#include "sky.h"
#include "battleareamanager.h"
#include "model.h"
#include "cleartime.h"
#include "ui_gameguide.h"
#include "camera_game.h"
#include "pause.h"

//�萔
const D3DXVECTOR3 CGame::TIME_POS = { SCREEN_WIDTH * 0.4f, 50.0f, 0.0f };
const std::string CGame::FILEPATH_MODEL = "data\\FILE\\model.bin";

//============================
//�Q�[���̃R���X�g���N�^
//============================
CGame::CGame() :
	m_pPlayer(nullptr),
	m_pField(nullptr),
	m_pTime(nullptr),
	m_pEnemyManager(nullptr),
	m_pLockon(nullptr),
	m_pGimmickManager(nullptr),
	m_pExplosionManager(nullptr),
	m_bClear(false),
	m_bDirectioning(false),
	m_pBarrierManager(nullptr),
	m_pEnemyBulletManager(nullptr),
	m_pDirection(nullptr),
	m_bBattle(false),
	m_bGameOver(false),
	m_bBossBattle(false),
	m_ControllerUIType(CUi_GameGuide::CONTROLLER_KEYBOARDMAUSE),
	m_bPause(false),
	m_pPause(nullptr)
{
	
}

//============================
//�Q�[���̃f�X�g���N�^
//============================
CGame::~CGame()
{
	//�t�H�O�̐ݒ�
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
}

//============================
//�Q�[���̏�����
//============================
HRESULT CGame::Init()
{
	//�v���C���[�̐���
	if (m_pPlayer == nullptr)
	{
		m_pPlayer = CPlayer::Create();
	}

	//field�̐���
	if (m_pField == nullptr)
	{
		m_pField = CField::Create({ 0.0f, 0.0f, 0.0f });
	}

	//�^�C���̐���
	if (m_pTime == nullptr)
	{
		m_pTime = new CTime;
	}

	//�G�l�~�[�}�l�[�W���[�̐���
	if (m_pEnemyManager == nullptr)
	{
		m_pEnemyManager = new CEnemyManager;
	}

	//�M�~�b�N�}�l�[�W���[�̐���
	if (m_pGimmickManager == nullptr)
	{
		m_pGimmickManager = new CGimmickManager;
	}

	//�����}�l�[�W���[�̐���
	if (m_pExplosionManager == nullptr)
	{
		m_pExplosionManager = new CExplosionManager;
	}

	//�G�l�~�[�e�}�l�[�W���[�̐���
	if (m_pEnemyBulletManager == nullptr)
	{
		m_pEnemyBulletManager = new CEnemyBulletManager;
	}

	//���E�}�l�[�W���[�̐���
	if (m_pBarrierManager == nullptr)
	{
		m_pBarrierManager = new CBarrierManager;
		m_pBarrierManager->Init();
	}

	//�o�g���G���A�̏�����
	CBattleAreaManager::GetInstance()->Init();

	//�X�e�[�W�ɔz�u����I�u�W�F�N�g
	CSky::Create();

	//�ǂݍ��ݏ���
	ModelLoad();
	GuideUILoad();

	//�N���A�^�C���̏�����
	CClearTime::GetInstance()->ResetTime();
	CClearTime::GetInstance()->SetPos(TIME_POS);
	CClearTime::GetInstance()->Init(); 

	//�t�H�O�̐ݒ�
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);					//�L��
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP);		//�t�H�O���[�h�̐ݒ�
	pDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.1f));	//�F�̐ݒ�
	float m_fFogDensity = 0.0005f;
	pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&m_fFogDensity));

	//BGM
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_WIND);

	//�J������؂�ւ�
	CManager::GetInstance()->ChangeCamera(new CCamera_Game());
	
	return S_OK;
}

//============================
//�Q�[���̏I������
//============================
void CGame::Uninit()
{
	//�������̔j��
	if (m_pPlayer != nullptr)
	{
		m_pPlayer = nullptr;
	}

	//�������̔j��
	if (m_pField != nullptr)
	{
		m_pField = nullptr;
	}

	//�������̔j��
	if (m_pTime != nullptr)
	{
		m_pTime = nullptr;
	}

	//�������̔j��
	if (m_pEnemyManager != nullptr)
	{
		m_pEnemyManager = nullptr;
	}

	//�������̔j��
	if (m_pGimmickManager != nullptr)
	{
		delete m_pGimmickManager;
		m_pGimmickManager = nullptr;
	}

	//�������̔j��
	if (m_pExplosionManager != nullptr)
	{
		delete m_pExplosionManager;
		m_pExplosionManager = nullptr;
	}

	//�������̔j��
	if (m_pEnemyBulletManager != nullptr)
	{
		delete m_pEnemyBulletManager;
		m_pEnemyBulletManager = nullptr;
	}

	//�������̔j��
	if (m_pBarrierManager != nullptr)
	{
		delete m_pBarrierManager;
		m_pBarrierManager = nullptr;
	}

	//�������̔j��
	if (m_pLockon != nullptr)
	{
		m_pLockon = nullptr;
	}

	//�o�g���G���A�̏�����
	CBattleAreaManager::GetInstance()->Uninit();

	//�I������
	CScene::Uninit();
}

//============================
//�Q�[���̍X�V����
//============================
void CGame::Update()
{
	//���Ԃ̍X�V
	m_pTime->Update();

	//�퓬���̓N���A���Ԃ����Z
	if (m_bBattle && !m_bDirectioning && !m_bPause)
	{
		CClearTime::GetInstance()->AddTime(1.0f / 60.0f);
	}

	//�G���A�}�l�[�W���[�X�V
	CBattleAreaManager::GetInstance()->Update();

	//���b�N�I���̍X�V
	if (m_pLockon != nullptr)
	{
		m_pLockon->Update();
	}

	//���o���̏���
	DirectioningProcess();

	//�\��UI�̊m�F
	CheckGuideUI();

	//�|�[�Y�̏���
	PauseProcess();

	//���̃V�[���ֈڍs
	NextScene();
}

//============================
//���o���̏���
//============================
void CGame::DirectioningProcess()
{
	//����
	if (!IsDeleteDirection()) return;

	//���o�̔j��
	delete m_pDirection;
	m_pDirection = nullptr;
	m_bDirectioning = false;
}

//============================
//���o��j�����邩
//============================
bool CGame::IsDeleteDirection()
{
	//����
	if (!m_bDirectioning) return false;				//���o�����m�F
	if (m_pDirection == nullptr) return false;		//�k���`�F�b�N
	if (!m_pDirection->TimeUpdate()) return false;	//�X�V���I�������j��

	return true;
}

//============================
//�K�C�hUI�̊m�F
//============================
void CGame::CheckGuideUI()
{
	//�}�l�[�W���[�̃C���X�^���X���擾
	CManager* pManager = CManager::GetInstance();

	//�K�C�hUI�̊m�F
	//�W���C�p�b�h��G���Ă��邩
	if (IsUsedJoipad())
	{
		//�W���C�p�b�h�p��UI�ɕύX
		m_ControllerUIType = CUi_GameGuide::CONTROLLER_JOYPAD;
	}

	//�L�[�{�[�h���}�E�X��G���Ă��邩
	if (IsUsedKeyboardMouse())
	{
		//�L�[�}�E�p��UI�ɕύX
		m_ControllerUIType = CUi_GameGuide::CONTROLLER_KEYBOARDMAUSE;
	}
}

//============================
//�W���C�p�b�h���g���Ă��邩
//============================
bool CGame::IsUsedJoipad()
{
	//�}�l�[�W���[�̃C���X�^���X���擾
	CManager* pManager = CManager::GetInstance();

	//����
	if (pManager->GetJoypad()->GetAnyTrigger()) return true;													//�ǂꂩ�̃{�^���ɐG�ꂽ��
	if (pManager->GetJoypad()->GetStick().afTplDiameter[CInputJoypad::STICKTYPE_LEFT] > 0.0f) return true;		//���X�e�B�b�N��|���Ă��邩
	if (pManager->GetJoypad()->GetStick().afTplDiameter[CInputJoypad::STICKTYPE_RIGHT] > 0.0f) return true;		//�E�X�e�B�b�N��|���Ă��邩

	return false;
}

//============================
//�L�[�{�[�h�}�E�X���g���Ă��邩
//============================
bool CGame::IsUsedKeyboardMouse()
{
	//�}�l�[�W���[�̃C���X�^���X���擾
	CManager* pManager = CManager::GetInstance();

	//����
	if (pManager->GetKeyboard()->GetAnyTrigger()) return true;	//�ǂꂩ�̃{�^���ɐG�ꂽ��
	if (pManager->GetMouse()->GetAnyTrigger()) return true;		//�ǂꂩ�̃{�^�����N���b�N������
	if (pManager->GetMouse()->GetMove().x > 0.0f) return true;	//�}�E�X��X���ɓ�������
	if (pManager->GetMouse()->GetMove().y > 0.0f) return true;	//�}�E�X��Y���ɓ�������

	return false;
}

//============================
//���̃V�[���ֈڍs
//============================
void CGame::NextScene()
{
	//���̃V�[���ֈڍs�ł��邩
	if (!CanNextScene()) return;

	//�}�l�[�W���[�̃C���X�^���X���擾
	CManager* pManager = CManager::GetInstance();

	//����ł�����^�C�g���ɑJ��
	if (m_bGameOver)
	{
		pManager->GetFade()->SetFade(CScene::MODE_TITLE);
	}
	else
	{
		//���U���g�ɉ�ʑJ��
		pManager->GetFade()->SetFade(CScene::MODE_RESULT);
	}
}

//============================
//���̃V�[���ֈڍs�ł��邩
//============================
bool CGame::CanNextScene()
{
	//����
	if (!CManager::GetInstance()->GetFade()->GetEnd()) return false; //�t�F�[�h���I����Ă�����X�V
	if (!m_bClear && !m_bGameOver) return false;					 //�N���A�����𖞂����Ă��邩

	return true;
}

//============================
//�|�[�Y�̏���
//============================
void CGame::PauseProcess()
{
	//�}�l�[�W���[�̃C���X�^���X���擾
	CManager* pManager = CManager::GetInstance();

	//�|�[�Y�̐ݒ�
	if ((pManager->GetKeyboard()->GetTrigger(DIK_P) || pManager->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_START)) && !m_bDirectioning && !m_bPause)
	{
		SetPause();
	}

	//�|�[�Y�̍X�V
	if (m_pPause != nullptr)
	{
		m_pPause->Update();
	}
}

//============================
//�Q�[���̕`�揈��
//============================
void CGame::Draw()
{
	
}

//============================
//�Q�[���̓ǂݍ���
//============================
void CGame::Load()
{

}

//============================
//�K�C�hUI�̏��
//============================
void CGame::GuideUILoad()
{
	// �t�@�C���̓ǂݍ���
	FILE* pFile = fopen("data\\FILE\\gameui.txt", "r");

	if (pFile == NULL)
	{// ��ޖ��̏��̃f�[�^�t�@�C�����J���Ȃ������ꍇ�A
	 //�������I������
		return;
	}

	char aDataSearch[256];	// �f�[�^�����p
	int nDataCount = 0;		//�f�[�^�̃J�E���g

	// END��������܂œǂݍ��݂��J��Ԃ�
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch);	// ����

		if (!strcmp(aDataSearch, "END_SCREPT"))
		{// �ǂݍ��݂��I��
			fclose(pFile);
			break;
		}

		if (aDataSearch[0] == '#')
		{// �܂�Ԃ�
			continue;
		}

		if (!strcmp(aDataSearch, "INFO"))
		{
			D3DXVECTOR3 Pos = { 0.0f, 0.0f, 0.0f };
			D3DXVECTOR3 Size = { 0.0f, 0.0f, 0.0f };

			while (1)
			{
				fscanf(pFile, "%s", aDataSearch);	// ����

				//�ǂݍ��݂̏I��
				if (!strcmp(aDataSearch, "END_INFO"))
				{
					//UI�̐���
					CUi_GameGuide::Create(Pos, static_cast<CUi_GameGuide::GUIDE>(nDataCount), Size);
					nDataCount++;
					break;
				}

				//�ʒu
				if (!strcmp(aDataSearch, "POS"))
				{
					fscanf(pFile, "%f", &Pos.x);
					fscanf(pFile, "%f", &Pos.y);
					fscanf(pFile, "%f", &Pos.z);
				}

				//�T�C�Y
				if (!strcmp(aDataSearch, "SIZE"))
				{
					fscanf(pFile, "%f", &Size.x);
					fscanf(pFile, "%f", &Size.y);
					fscanf(pFile, "%f", &Size.z);
				}
			}
		}
	}
}

//============================
//���b�N�I���̐ݒ�
//============================
void CGame::SetLockon(bool lockon)
{
	//���b�N�I���̔���
	if (lockon)
	{
		//���b�N�I�����Ă��Ȃ��Ȃ琶��
		if (m_pLockon != nullptr)
		{
			return;
		}

		//����
		m_pLockon = CLockon::Create();
	}
	else //�����ꍇ
	{
		//���b�N�I�����Ă�Ȃ����
		if (m_pLockon == nullptr)
		{
			return;
		}

		//����
		m_pLockon->Uninit();
		m_pLockon = nullptr;
	}
}

//============================
//���f���̓ǂݍ���
//============================
void CGame::ModelLoad()
{
	//���[�J���ϐ��錾
	FILE* pFile;

	//�t�@�C�����J��
	pFile = fopen(FILEPATH_MODEL.c_str(), "rb");

	//�t�@�C���ɏ��������o��
	if (pFile != NULL)
	{
		//�ǂݍ��ݗp�̕ϐ�
		int nModelNum = 0;

		//���f���̐�
		fread(&nModelNum, sizeof(int), 1, pFile);

		//�z�u�������f���̐��������������o��
		for (int i = 0; i < nModelNum; i++)
		{
			//�ǂݍ��ݗp�ϐ�
			D3DXVECTOR3 Pos;
			D3DXVECTOR3 Rot;
			CModel::MODEL_TYPE Type;

			//���f���̏��
			fread(&Pos, sizeof(D3DXVECTOR3), 1, pFile);			//�ʒu
			fread(&Rot, sizeof(D3DXVECTOR3), 1, pFile);			//����
			fread(&Type, sizeof(CModel::MODEL_TYPE), 1, pFile);	//���

			//����
			CModel::Create(Pos, Rot, Type);
		}

		//�t�@�C�������
		fclose(pFile);
	}
}

//============================
//���o�̐ݒ�
//============================
void CGame::SetDirection(CDirection::DIRECTIONTYPE type)
{
	//�͈͊O�̎�ނȂ�e��
	if (type < 0 && type >= CDirection::DIRECTIONTYPE_MAX)
	{
		return;
	}

	//���o������Ȃ�e��
	if (m_pDirection != nullptr)
	{
		return;
	}

	//���o�̐���
	m_pDirection = CDirection::Create(type);
	m_bDirectioning = true;
}

//============================
//�|�[�Y�̐ݒ�
//============================
void CGame::SetPause()
{
	m_bPause = m_bPause ? false : true;

	if (m_bPause)
	{
		CObject::ChangeUpdateObject(CObject::TAG_PAUSE);

		if (m_pPause == nullptr)
		{
			m_pPause = CPause::Create();
		}
	}
	else
	{
		CObject::ChangeUpdateObject(CObject::TAG_GAME);

		if (m_pPause != nullptr)
		{
			m_pPause = nullptr;
		}
	}
}