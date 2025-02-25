//================================
//
//animation.cpp�ɕK�v�Ȑ錾[animation.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _FOG_H_ //���̃}�N����`������Ă��Ȃ�������
#define _FOG_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"

//�t�H�O�N���X
class CFog
{
private:

	//�����o�֐�
	CFog();		//�R���X�g���N�^

public:

	//�����o�֐�
	~CFog();		//�f�X�g���N�^

	//�C���X�^���X�̐���
	static CFog* GetInstance()
	{
		static CFog instance;	//�ÓI�C���X�^���X
		return &instance;
	}

	//�t�H�O�̐ݒ�
	void SetFog();		//�t�H�O��ݒ�
	void ClearFog();	//�t�H�O������
	void SetColor(D3DXCOLOR color) { m_Color = color; }			//�t�H�O�̐F��ݒ�
	void SetDensity(float density) { m_fDensity = density; }	//�t�H�O�̖��x��ݒ�

private:

	//�萔
	static const D3DXCOLOR DEFAULT_COLOR;					//�f�t�H���g�̐F
	static constexpr float DEFAULT_DENDITY{ 0.0005f };		//�f�t�H���g�̖��x

	//�ϐ�
	D3DXCOLOR m_Color;		//�t�H�O�̐F
	float m_fDensity;		//�t�H�O�̖��x
	
};

#endif