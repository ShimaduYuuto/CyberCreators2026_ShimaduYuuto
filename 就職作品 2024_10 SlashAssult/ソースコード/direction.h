//================================
//
//direction.cpp�ɕK�v�Ȑ錾[direction.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _DIRECTION_H_ //���̃}�N����`������Ă��Ȃ�������
#define _DIRECTION_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"
#include "letterbox.h"

//���o�N���X
class CDirection
{
public:

	//���o�̎��
	typedef enum
	{
		DIRECTIONTYPE_BOSS = 0,
		DIRECTIONTYPE_BOSS_DESTROY,
		DIRECTIONTYPE_MAX,
	}DIRECTIONTYPE;

	//�����o�֐�
	CDirection();	//�R���X�g���N�^
	~CDirection();	//�f�X�g���N�^

	//��{����
	virtual HRESULT Init();		//������
	virtual bool TimeUpdate();	//�X�V

	//����
	static CDirection* Create(DIRECTIONTYPE type);

	//�I������
	void SetEndTime(int time);					//�ݒ�
	int GetEndTime() { return m_nEndTime; }		//�擾

	//�J�E���g
	int GetCount() { return m_nCount; }	//�擾

private:

	//�����o�ϐ�
	int m_nEndTime;				//�I������
	int m_nCount;				//�J�E���g
	CLetterBox* m_pLetterBox;	//���^�[�{�b�N�X
};

#endif