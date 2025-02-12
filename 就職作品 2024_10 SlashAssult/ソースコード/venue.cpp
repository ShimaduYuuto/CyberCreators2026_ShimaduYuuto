//======================================
//
//	���̕`��[venue.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "venue.h"
#include "game.h"
#include "manager.h"

//�萔
const std::string CVenue::MODEL_PATH = "data\\model\\venue004.x";
const std::string CVenue::BOSSBATTLE_MODEL_PATH = "data\\model\\bossvenue000.x";

//============================
//�`��
//============================
void CVenue::Draw()
{
	//�Q�[���V�[���Ȃ画��
	if (CManager::GetInstance()->GetScene()->GetMode() != CManager::GetInstance()->GetScene()->MODE_GAME)
	{
		return;
	}

	//�Q�[���V�[���̎擾
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//�{�X��ɂȂ����烂�f����u��������
	if (pGame->GetBossBattleJudge())
	{
		//�O����������������郂�f���ɕύX
		CObjectX::Draw(BOSSBATTLE_MODEL_PATH.c_str());
	}
	else
	{
		//�ʏ�̃��f��
		CObjectX::Draw(MODEL_PATH.c_str());
	}
}