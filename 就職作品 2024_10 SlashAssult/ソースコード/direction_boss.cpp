//======================================
//
//	�o�ꉉ�o�̏���[direction_boss.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "direction_boss.h"
#include "manager.h"
#include "game.h"

const D3DXVECTOR3 CDirection_Boss::CAMERA_POSR = { 0.0f, 50.0f, 3500.0f };
const D3DXVECTOR3 CDirection_Boss::CAMERA_POSV = { 0.0f, 50.0f, 3300.0f };

//============================
//���o�̃R���X�g���N�^
//============================
CDirection_Boss::CDirection_Boss()
{
	//�J�����̈ʒu���Œ�
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	pCamera->SetPosR(CAMERA_POSR);
	pCamera->SetPosV(CAMERA_POSV);

	//�Q�[���V�[���Ȃ画��
	if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
	{
		//�{�X�킪�n�܂������}���o��
		CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());
		pGame->SetBossBattleJudge(true);
	}

	//�I������
	SetEndTime(END_TIME);
}

//============================
//���o�̃f�X�g���N�^
//============================
CDirection_Boss::~CDirection_Boss()
{
	CManager::GetInstance()->GetSound()->Stop(CSound::SOUND_LABEL_RUMBLING);
}

//============================
//���o�̏�����
//============================
HRESULT CDirection_Boss::Init()
{
	return S_OK;
}

//============================
//���o�̍X�V
//============================
bool CDirection_Boss::TimeUpdate()
{
	//�h�炷����
	if (GetCount() == START_SHAKE_FRAME)
	{
		//�J������h�炷
		CCamera* pCamera = CManager::GetInstance()->GetCamera();
		pCamera->SetShake(SHAKE_FRAME, SHAKE_MAGNITUDE);
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_RUMBLING);
	}

	//�I�����Ԃ̏���
	if (GetCount() == END_TIME)
	{
		CManager::GetInstance()->GetSound()->Stop(CSound::SOUND_LABEL_RUMBLING);
	}

	//���o�̍X�V
	return CDirection::TimeUpdate();
}