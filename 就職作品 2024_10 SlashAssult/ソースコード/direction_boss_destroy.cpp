//======================================
//
//	���o�̏���[direction_boss.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "direction_boss_destroy.h"
#include "manager.h"
#include "game.h"
#include "particle.h"

//�萔
const D3DXVECTOR3 CDirection_Boss_Destroy::CAMERA_POSR = { 0.0f, 100.0f, 3500.0f };
const D3DXVECTOR3 CDirection_Boss_Destroy::CAMERA_POSV = { 0.0f, 100.0f, 3300.0f };

//============================
//���o�̃R���X�g���N�^
//============================
CDirection_Boss_Destroy::CDirection_Boss_Destroy() :
	m_fFadeAlpfa(0.0f),
	m_pDirectionFade(nullptr)
{
	//�J�����̈ʒu���Œ�
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	pCamera->SetPosR(CAMERA_POSR);
	pCamera->SetPosV(CAMERA_POSV);

	//�I������
	SetEndTime(END_TIME);

	//���o�p�t�F�[�h
	m_pDirectionFade = new CObject2D(5);	//�v���C�I���e�B��ύX�������̂�new
	m_pDirectionFade->Init();
	m_pDirectionFade->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	m_pDirectionFade->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	m_pDirectionFade->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	//�T�E���h
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_DESTROY);
}

//============================
//���o�̃f�X�g���N�^
//============================
CDirection_Boss_Destroy::~CDirection_Boss_Destroy()
{
	//�t�F�[�h��j��
	if (m_pDirectionFade != nullptr)
	{
		m_pDirectionFade = nullptr;
	}
}

//============================
//���o�̏�����
//============================
HRESULT CDirection_Boss_Destroy::Init()
{
	return S_OK;
}

//============================
//���o�̍X�V
//============================
bool CDirection_Boss_Destroy::TimeUpdate()
{
	//�h�炷����
	if (GetCount() == START_SHAKE_FRAME)
	{
		//�J������h�炷
		CCamera* pCamera = CManager::GetInstance()->GetCamera();
		pCamera->SetShake(SHAKE_FRAME, SHAKE_MAGNITUDE);

		//�T�E���h
		CManager::GetInstance()->GetSound()->Stop(CSound::SOUND_LABEL_DESTROY);				//���SSE���~�߂�
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_EXPLOSION001);	//����SE���Đ�
	}

	//�p�[�e�B�N�����o��
	if (GetCount() >= START_SHAKE_FRAME)
	{
		CCamera* pCamera = CManager::GetInstance()->GetCamera();
		CParticle* pParticle = CParticle::Create(D3DXVECTOR3(pCamera->GetPosR()));
		float fRandom = CManager::GetInstance()->GetRundom(0, 628) * 0.01f;
		pParticle->SetMove(D3DXVECTOR3(sinf(fRandom) * 10.0f, cosf(fRandom) * 10.0f, 0.0f));
		pParticle->SetNormalSize(100.0f);
	}

	//���o�p�t�F�[�h�̍X�V
	if (GetCount() >= START_SHAKE_FRAME && GetCount() < TIME_ENDFADE_FRAME)
	{
		//���l�̍X�V
		m_fFadeAlpfa += 1.0f / (TIME_ENDFADE_FRAME - START_SHAKE_FRAME);
		if (m_fFadeAlpfa > 1.0f)
		{
			m_fFadeAlpfa = 1.0f;
		}

		//�ݒ�
		m_pDirectionFade->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fFadeAlpfa));
	}

	//�Q�[�����I��点�鎞��
	if (GetCount() == TIME_ENDGAME_FRAME)
	{
		CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());
		pGame->SetClear(true);
	}

	//���o�̍X�V
	return CDirection::TimeUpdate();
}

//============================
//�p�[�e�B�N���̐���
//============================
void CDirection_Boss_Destroy::CreateParticle()
{
	//�ϐ��錾
	CCamera* pCamera = CManager::GetInstance()->GetCamera();					//�J�������擾
	CParticle* pParticle = CParticle::Create(D3DXVECTOR3(pCamera->GetPosR()));	//�p�[�e�B�N���̐���
	float fRandom = CManager::GetInstance()->GetRundom(0, 628) * 0.01f;			//�����_���l�̎Z�o(0.0f, 6.28f)

	//�p�����[�^�̐ݒ�
	pParticle->SetMove(D3DXVECTOR3(sinf(fRandom) * PARTICLE_SPEED, cosf(fRandom) * PARTICLE_SPEED, 0.0f));	//�ړ��ʂ̐ݒ�
	pParticle->SetNormalSize(PARTICLE_SIZE);																//�ʏ�T�C�Y�̐ݒ�
}