//================================
//
//number.cpp�ɕK�v�Ȑ錾[number.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _NUMBER_H_ //���̃}�N����`������Ă��Ȃ�������
#define _NUMBER_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "object2D.h"

//�i���o�[�̃N���X
class CNumber : public CObject2D
{
public:

	//�萔
	static const std::string TEXTUREPATH;	//�ǂݍ��ރt�@�C��

	//�����o�֐�
	CNumber(int nPriority = 5);								//�R���X�g���N�^
	~CNumber() override;									//�f�X�g���N�^
	HRESULT Init() override;								//������
	void Uninit() override;									//�I��
	void Update() override;									//�X�V
	void Draw() override;									//�`��
	void SetTexture(int Num);								//�e�N�X�`���̐ݒ�
	static CNumber* Create(D3DXVECTOR3 pos, int number);	//�i���o�[�̐���

private:
};

#endif