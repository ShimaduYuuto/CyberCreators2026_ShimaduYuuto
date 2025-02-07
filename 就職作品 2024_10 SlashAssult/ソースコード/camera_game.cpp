//======================================
//
//	�Q�[���J�����̏���[camera_game.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "camera_game.h"
#include "game.h"
#include "manager.h"

//============================
//�J�����̃R���X�g���N�^
//============================
CCamera_Game::CCamera_Game() :
	m_GoalPosR()
{
	
}

//============================
//�J�����̃f�X�g���N�^
//============================
CCamera_Game::~CCamera_Game()
{

}

//============================
//�J�����̏�����
//============================
HRESULT CCamera_Game::Init()
{
	//���̏�����
	CCamera::Init();

	//�擾
	D3DXVECTOR3 PosR = GetPosR();
	D3DXVECTOR3 PosV = GetPos();
	D3DXVECTOR3 Rot = GetRot();
	float fLength = GetLength();

	Rot.y = atan2f(PosR.x - PosV.x, PosR.z - PosV.z);
	Rot.x = D3DX_PI * -0.1f;
	fLength = LENGTH_NORMAL;

	//�ݒ�
	SetPosR(PosR);
	SetPosV(PosV);
	SetRot(Rot);
	SetLength(fLength);

	return S_OK;
}

//============================
//�J�����̏I������
//============================
void CCamera_Game::Uninit()
{

}

//============================
//�J�����̍X�V����
//============================
void CCamera_Game::Update()
{
	//�Q�[���V�[���̃v���C���[�̈ʒu���擾
	CGame* pGame = nullptr;
	pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());	//�Q�[���V�[���̎擾

	//���o���������̓|�[�Y���Ȃ甲����
	if (pGame->GetDirectioning() || pGame->GetPause())
	{
		return;
	}

	//�擾
	D3DXVECTOR3 PosR = GetPosR();
	D3DXVECTOR3 PosV = GetPos();
	D3DXVECTOR3 Rot = GetRot();
	float fLength = GetLength();
	
	//�v���C���[�̈ʒu�𒍎��_�ɑ��
	if (pGame->GetGamePlayer()->GetCollision() != nullptr)
	{
		m_GoalPosR = pGame->GetGamePlayer()->GetCollision()->GetPos();
	}

	//�}�E�X�̈ړ��ʂŌ�����ύX
	{
		//�}�E�X�̈ړ��ʂ̎擾
		D3DXVECTOR3 MouseMove = CManager::GetInstance()->GetMouse()->GetMove();

		//�J�����ɔ��f
		Rot.y += MouseMove.x * 0.004f;
	}

	//�W���C�p�b�h�̑���
	if (CManager::GetInstance()->GetJoypad()->GetStick().afTplDiameter[CInputJoypad::STICKTYPE_RIGHT] > 0.0f)
	{
		//�J�����ɔ��f
		float fAngle = CManager::GetInstance()->GetJoypad()->GetStick().afAngle[CInputJoypad::STICKTYPE_RIGHT];
		Rot.y += sinf(fAngle) * 0.04f * CManager::GetInstance()->GetJoypad()->GetStick().afTplDiameter[CInputJoypad::STICKTYPE_RIGHT];
	}

	//�����̕␳
	if (Rot.y > D3DX_PI)
	{
		Rot.y -= D3DX_PI * 2.0f;
	}
	if (Rot.y < -D3DX_PI)
	{
		Rot.y += D3DX_PI * 2.0f;
	}

	//�ړ��ʂ̌v�Z
	D3DXVECTOR3 Move = (m_GoalPosR - PosR) * MOVE_RATE;

	//���Ԃ̏�Ԃɉ����ċ�����ύX
	if (pGame->GetRushJudge())
	{
		fLength -= 0.05f * fLength;

		if (fLength < LENGTH_RUSH)
		{
			fLength = LENGTH_RUSH;
		}
	}
	else
	{
		fLength += 0.05f * fLength;

		if (fLength > LENGTH_NORMAL)
		{
			fLength = LENGTH_NORMAL;
		}
	}

	/*fLength += 0.03f * fLength;

	if (fLength > LENGTH_NORMAL)
	{
		fLength = LENGTH_NORMAL;
	}*/

	PosV.y = -sinf(Rot.x) * fLength;
	PosV.x = sinf(Rot.y + D3DX_PI) * cosf(Rot.x) * fLength;
	PosV.z = cosf(Rot.y + D3DX_PI) * cosf(Rot.x) * fLength;
	PosV += PosR + Move;

	//�ݒ�
	SetPosR(PosR + Move);
	SetPosV(PosV);
	SetRot(Rot);
	SetLength(fLength);
}