//================================
//
//oldpaper.cpp�ɕK�v�Ȑ錾[oldpaper.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _OLDPAPER_H_ //���̃}�N����`������Ă��Ȃ�������
#define _OLDPAPER_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "object2D.h"

//�Â�����UI�N���X
class COldPaper : public CObject2D
{
public:

	//�萔
	static const std::string TEXTUREPATH;	//�ǂݍ��ރp�X
	static const D3DXVECTOR3 POS;			//�ʒu
	static const D3DXVECTOR3 SIZE;			//�T�C�Y

	//�����o�֐�
	COldPaper(int nPriority = 3);	//�R���X�g���N�^
	~COldPaper() override;			//�f�X�g���N�^
	HRESULT Init() override;		//������
	void Uninit() override;			//�I��
	void Update() override;			//�X�V
	void Draw() override;			//�`��
	static COldPaper* Create();		//�Â�����UI�𐶐�

private:
	
};

#endif