//================================
//
//dot.cpp�ɕK�v�Ȑ錾[dot.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _DOT_H_ //���̃}�N����`������Ă��Ȃ�������
#define _DOT_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "object2D.h"

//�Q�[�W�N���X
class CDot : public CObject2D
{
public:

	//�萔
	static const std::string TEXTURE_PATH;	//�e�N�X�`���p�X

	//�����o�֐�
	CDot(int nPriority = 3);	//�R���X�g���N�^
	~CDot() override;			//�f�X�g���N�^
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��
	static CDot* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//�Q�[�W�̐���
};

#endif