//================================
//
//select_continue.cpp�ɕK�v�Ȑ錾[select_continue.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _SELECT_CONTINUE_H_ //���̃}�N����`������Ă��Ȃ�������
#define _SELECT_CONTINUE_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "pause_select.h"

//�|�[�Y�I���N���X
class CSelect_Continue : public CPause_Select
{
public:

	//�萔
	static const std::string TEXTURE_PATH;	//�e�N�X�`���p�X

	//�����o�֐�
	CSelect_Continue(int nPriority = 6);	//�R���X�g���N�^
	~CSelect_Continue() override;			//�f�X�g���N�^
	void Draw() override;					//�`��
	void Decision() override;				//���莞�̏���
};

#endif