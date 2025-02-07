//================================
//
//pause_bg.cpp�ɕK�v�Ȑ錾[pause_bg.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _PAUSE_BG_H_ //���̃}�N����`������Ă��Ȃ�������
#define _PAUSE_BG_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "object2D.h"

//�|�[�Y�w�i�N���X
class CPause_Bg : public CObject2D
{
public:

	//�萔
	static const std::string TEXTURE_PATH;	//�e�N�X�`���p�X

	//�����o�֐�
	CPause_Bg(int nPriority = 5);	//�R���X�g���N�^
	~CPause_Bg() override;			//�f�X�g���N�^
	HRESULT Init() override;		//������
	void Uninit() override;			//�I��
	void Update() override;			//�X�V
	void Draw() override;			//�`��
	static CPause_Bg* Create();		//����
};

#endif