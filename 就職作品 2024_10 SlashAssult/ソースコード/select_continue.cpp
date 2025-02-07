//======================================
//
//	�|�[�Y�̑I�����̏���[select_continue.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "select_continue.h"
#include "manager.h"
#include "game.h"

//�萔
const std::string CSelect_Continue::TEXTURE_PATH =
{
	"data\\TEXTURE\\pause000.png"
};

//============================
//�R���X�g���N�^
//============================
CSelect_Continue::CSelect_Continue(int nPriority) : CPause_Select(nPriority)
{

}

//============================
//�f�X�g���N�^
//============================
CSelect_Continue::~CSelect_Continue()
{

}

//============================
//���莞�̏���
//============================
void CSelect_Continue::Decision()
{
	//�|�[�Y�̉���
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());
	pGame->SetPause();
}

//============================
//�`��
//============================
void CSelect_Continue::Draw()
{
	//�`�揈��
	CObject2D::Draw(TEXTURE_PATH.c_str());
}