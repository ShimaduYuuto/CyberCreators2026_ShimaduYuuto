//================================
//
//select_restart.cpp�ɕK�v�Ȑ錾[select_restart.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _SELECT_RESTART_H_ //���̃}�N����`������Ă��Ȃ�������
#define _SELECT_RESTART_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "pause_select.h"

//�|�[�Y�I���N���X
class CSelect_Restart : public CPause_Select
{
public:

	//�萔
	static const std::string TEXTURE_PATH;	//�e�N�X�`���p�X

	//�����o�֐�
	CSelect_Restart(int nPriority = 6);	//�R���X�g���N�^
	~CSelect_Restart() override;			//�f�X�g���N�^
	void Draw() override;					//�`��
	void Decision() override;				//���莞�̏���
};

#endif