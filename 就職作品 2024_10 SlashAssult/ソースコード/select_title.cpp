//======================================
//
//	�|�[�Y�̑I�����̏���[select_title.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "select_title.h"
#include "manager.h"
#include "game.h"

//�萔
const std::string CSelect_Title::TEXTURE_PATH =
{
	"data\\TEXTURE\\pause002.png"
};

//============================
//�R���X�g���N�^
//============================
CSelect_Title::CSelect_Title(int nPriority) : CPause_Select(nPriority)
{

}

//============================
//�f�X�g���N�^
//============================
CSelect_Title::~CSelect_Title()
{

}

//============================
//���莞�̏���
//============================
void CSelect_Title::Decision()
{
	//�V�����Q�[���V�[���Ɉڍs
	CManager* pManager = CManager::GetInstance();
	pManager->GetFade()->SetFade(CScene::MODE_TITLE);
}

//============================
//�`��
//============================
void CSelect_Title::Draw()
{
	//�`�揈��
	CObject2D::Draw(TEXTURE_PATH.c_str());
}