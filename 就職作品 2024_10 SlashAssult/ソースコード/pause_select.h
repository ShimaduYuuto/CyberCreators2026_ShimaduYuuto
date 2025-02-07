//================================
//
//pause_select.cpp�ɕK�v�Ȑ錾[pause_select.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _PAUSE_SELECT_H_ //���̃}�N����`������Ă��Ȃ�������
#define _PAUSE_SELECT_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "object2D.h"

//�|�[�Y�I���N���X
class CPause_Select : public CObject2D
{
public:

	//�I�����̎��
	enum CHOICE
	{
		CHOICE_CONTINUE = 0,
		CHOICE_RESTART,
		CHOICE_TITLE,
		CHOICE_MAX
	};

	static const D3DXVECTOR3 SIZE;	//�T�C�Y

	//�����o�֐�
	CPause_Select(int nPriority = 6);	//�R���X�g���N�^
	~CPause_Select() override;			//�f�X�g���N�^
	HRESULT Init() override;			//������
	void Uninit() override;				//�I��
	void Update() override;				//�X�V
	void Draw() override;				//�`��
	static CPause_Select* Create(CHOICE choice, D3DXVECTOR3 pos);	//����

	virtual void Decision();			//���莞�̏���
};

#endif