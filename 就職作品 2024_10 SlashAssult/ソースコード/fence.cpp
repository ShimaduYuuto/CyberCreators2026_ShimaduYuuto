//======================================
//
//	�t�F���X�̕`��[fence.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "fence.h"
#include "manager.h"

//�萔
const std::string CFence::MODEL_PATH = "data\\model\\fence000.x";

//============================
//�`��
//============================
void CFence::Draw()
{
	if ((GetPos().x < 0.0f && GetPos().x > CManager::GetInstance()->GetCamera()->GetPos().x) || (GetPos().x > 0.0f && GetPos().x < CManager::GetInstance()->GetCamera()->GetPos().x))
	{
		return;
	}

	CObjectX::Draw(MODEL_PATH.c_str());
}