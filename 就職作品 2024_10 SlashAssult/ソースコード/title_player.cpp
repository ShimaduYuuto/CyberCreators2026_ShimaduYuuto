//======================================
//
//	�v���C���[�̏���[title_player.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "title_player.h"
#include "manager.h"
#include "modelparts.h"
#include "camera.h"

//�ÓI�����o�̏�����
const std::string CTitle_Player::FILEPATH = "data\\playermotion001.txt";

//============================
//�v���C���[�̃R���X�g���N�^
//============================
CTitle_Player::CTitle_Player(int nPriority) : CCharacter(nPriority)
{
	
}

//============================
//�v���C���[�̃f�X�g���N�^
//============================
CTitle_Player::~CTitle_Player()
{

}

//============================
//�v���C���[�̏�����
//============================
HRESULT CTitle_Player::Init()
{
	//������
	CCharacter::Init();

	//�p�����[�^�̏�����
	CCharacter::SetRot({ 0.0f, 0.0f, 0.0f });
	CCharacter::SetPos({ 0.0f, 0.0f, 0.0f });
	CCharacter::SetGoalRot({ 0.0f, 0.0f, 0.0f });

	//���[�V�����̓ǂݍ���
	SetMotionInfo(FILEPATH.c_str());

	//���[�V�����̐ݒ�
	SetMotion(CTitle_Player::TITLE_PLAYERMOTION_NORMAL);

	return S_OK;
}

//============================
//�v���C���[�̏I������
//============================
void CTitle_Player::Uninit()
{
	//�I������
	CCharacter::Uninit();
}

//============================
//�v���C���[�̍X�V
//============================
void CTitle_Player::Update()
{
	//���ʏ����̍X�V
	CCharacter::Update();
}

//============================
//�v���C���[�̕`��
//============================
void CTitle_Player::Draw()
{
	//�L�����N�^�[�N���X�̕`��
	CCharacter::Draw();
}

//============================
//�v���C���[�̃N���G�C�g
//============================
CTitle_Player* CTitle_Player::Create()
{
	//�|�C���^�p�̕ϐ�
	CTitle_Player* pTitle_Player;

	//�������̊m��
	pTitle_Player = new CTitle_Player;

	//������
	pTitle_Player->Init();

	return pTitle_Player;
}