//================================
//
//venue.cpp�ɕK�v�Ȑ錾[venue.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _VENUE_H_ //���̃}�N����`������Ă��Ȃ�������
#define _VENUE_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "model.h"

//���N���X
class CVenue : public CModel
{
public:

	//�e�N�X�`���p�X
	static const std::string MODEL_PATH;
	static const std::string BOSSBATTLE_MODEL_PATH;

	//�`��
	void Draw() override;
};

#endif