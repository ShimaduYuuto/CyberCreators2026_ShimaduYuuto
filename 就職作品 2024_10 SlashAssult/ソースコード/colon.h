//================================
//
//colon.cpp�ɕK�v�Ȑ錾[colon.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _COLON_H_ //���̃}�N����`������Ă��Ȃ�������
#define _COLON_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "object2D.h"

//�R�����N���X
class CColon : public CObject2D
{
public:

	//�萔
	static const std::string TEXTURE_PATH;	//�e�N�X�`���p�X

	//�����o�֐�
	CColon(int nPriority = 5);	//�R���X�g���N�^
	~CColon() override;			//�f�X�g���N�^
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��
	static CColon* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//����
};

#endif