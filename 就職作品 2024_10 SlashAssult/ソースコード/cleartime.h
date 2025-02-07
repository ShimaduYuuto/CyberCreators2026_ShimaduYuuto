//================================
//
//cleartime.cpp�ɕK�v�Ȑ錾[cleartime.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _CLEARTIME_H_ //���̃}�N����`������Ă��Ȃ�������
#define _CLEARTIME_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"
#include "number.h"

//�N���A�^�C���̃N���X
class CClearTime
{

private:
	//�����o�֐�
	CClearTime();								//�R���X�g���N�^

public:

	//�萔
	static constexpr int TIME_NUM{6};			//�^�C���̌���
	static constexpr float NUM_SPACE{50.0f};		//�����̌���

	//�C���X�^���X�̐���
	static CClearTime* GetInstance()
	{
		static CClearTime instance;	//�ÓI�C���X�^���X
		return &instance;
	}

	~CClearTime();								//�f�X�g���N�^
	HRESULT Init();								//������
	void Uninit();								//�I��
	void AddTime(float value);					//�^�C���̉��Z
	float GetTime() { return m_fTime; }			//�^�C���̎擾
	void SetTime();								//�^�C���̐ݒ�
	void ResetTime();							//�^�C���̏���

	//�ʒu
	void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; }	//�ݒ�

private:
	CNumber* m_pNumber[TIME_NUM];			//�^�C���̌��������m��
	float m_fTime;							//���݂̃^�C��
	D3DXVECTOR3 m_Pos;						//�ʒu
};

#endif