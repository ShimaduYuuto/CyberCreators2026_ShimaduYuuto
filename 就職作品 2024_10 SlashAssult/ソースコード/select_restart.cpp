//======================================
//
//	�|�[�Y�̑I�����̏���[select_restart.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "select_restart.h"
#include "manager.h"
#include "game.h"

//�萔
const std::string CSelect_Restart::TEXTURE_PATH =
{
	"data\\TEXTURE\\pause001.png"
};

//============================
//�R���X�g���N�^
//============================
CSelect_Restart::CSelect_Restart(int nPriority) : CPause_Select(nPriority)
{

}

//============================
//�f�X�g���N�^
//============================
CSelect_Restart::~CSelect_Restart()
{

}

//============================
//���莞�̏���
//============================
void CSelect_Restart::Decision()
{
	//�V�����Q�[���V�[���Ɉڍs
	CManager* pManager = CManager::GetInstance();
	pManager->GetFade()->SetFade(CScene::MODE_GAME);
}

//============================
//�`��
//============================
void CSelect_Restart::Draw()
{
	//�`�揈��
	CObject2D::Draw(TEXTURE_PATH.c_str());
}