//======================================
//
//	���o�̏���[direction_boss.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "direction_boss_destroy.h"
#include "manager.h"

const D3DXVECTOR3 CDirection_Boss_Destroy::CAMERA_POSR = { 0.0f, 100.0f, 3500.0f };
const D3DXVECTOR3 CDirection_Boss_Destroy::CAMERA_POSV = { 0.0f, 100.0f, 3300.0f };

//============================
//���o�̃R���X�g���N�^
//============================
CDirection_Boss_Destroy::CDirection_Boss_Destroy()
{
	//�J�����̈ʒu���Œ�
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	pCamera->SetPosR(CAMERA_POSR);
	pCamera->SetPosV(CAMERA_POSV);

	//�I������
	SetEndTime(END_TIME);
}

//============================
//���o�̃f�X�g���N�^
//============================
CDirection_Boss_Destroy::~CDirection_Boss_Destroy()
{

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
	}

	//���o�̍X�V
	return CDirection::TimeUpdate();
}