//======================================
//
//	�G�l�~�[�̊Ǘ������鏈��[battlearea.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "battlearea.h"
#include "manager.h"

//============================
//�R���X�g���N�^
//============================
CBattleArea::CBattleArea() :
	m_apArea()
{
	m_apArea.clear();
}

//============================
//�f�X�g���N�^
//============================
CBattleArea::~CBattleArea()
{
	m_apArea.clear();
}

//============================
//������
//============================
HRESULT CBattleArea::Init()
{
	return S_OK;
}

//============================
//�I������
//============================
void CBattleArea::Uninit()
{
	m_apArea.clear();
}