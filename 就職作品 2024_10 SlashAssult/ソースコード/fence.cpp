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
	//�`�悷�邩���m�F
	if (IsDraw())
	{
		return;
	}

	//�e�N���X�ŕ`��
	CObjectX::Draw(MODEL_PATH.c_str());
}

//============================
//�`������邩�̔����Ԃ�
//============================
bool CFence::IsDraw()
{
	//����
	if ((GetPos().x < 0.0f && GetPos().x > CManager::GetInstance()->GetCamera()->GetPos().x)) return true;	//���g��X���W��-�ŃJ�����̎��_���l���������Ȃ�`�悷��
	if ((GetPos().x > 0.0f && GetPos().x < CManager::GetInstance()->GetCamera()->GetPos().x)) return true;	//���g��X���W��+�ŃJ�����̎��_���l���傫���Ȃ�`�悷��

	return false;
}