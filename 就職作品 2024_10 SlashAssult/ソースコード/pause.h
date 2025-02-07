//================================
//
//pause.cpp�ɕK�v�Ȑ錾[pause.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _PAUSE_H_ //���̃}�N����`������Ă��Ȃ�������
#define _PAUSE_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"
#include "pause_select.h"
#include "pause_bg.h"

//�|�[�Y�N���X
class CPause
{
public:

	//�����o�֐�
	CPause();					//�R���X�g���N�^
	~CPause();					//�f�X�g���N�^
	HRESULT Init();				//������
	void Update();				//�X�V
	static CPause* Create();	//����

private:

	int m_nSelect;		//�I��ԍ�
	CPause_Select* m_pPauseSelect[CPause_Select::CHOICE_MAX];
	CPause_Bg* m_pPauseBg;
};

#endif