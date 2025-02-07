//================================
//
//letterbox.cpp�ɕK�v�Ȑ錾[letterbox.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _LETTERBOX_H_ //���̃}�N����`������Ă��Ȃ�������
#define _LETTERBOX_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"
#include "object2D.h"

//���^�[�{�b�N�X�N���X
class CLetterBox : public CObject
{
public:

	//�萔
	static constexpr int NUM_LETTERBOX{ 2 };			//���^�[�{�b�N�X�̐�
	static constexpr int TIME_INTERPOLATION{ 30 };		//��Ԃ̎���
	static constexpr float HEIGHT_LETTERBOX{ 100.0f };	//2D�I�u�W�F�N�g�̍���

	//�����o�֐�
	CLetterBox();					//�R���X�g���N�^
	~CLetterBox();					//�f�X�g���N�^
	HRESULT Init() override;		//������
	void Uninit() override;			//�I��
	void Update() override;			//�X�V
	void Draw() override;			//�`��
	static CLetterBox* Create(int time);	//���^�[�{�b�N�X�̐���

private:

	//�㉺�̃��^�[�{�b�N�X
	CObject2D* m_pLetterBox[NUM_LETTERBOX];	//2D�I�u�W�F�N�g
	int m_nTime;							//��������
	int m_nCurrentTime;						//���݂̎���
};

#endif