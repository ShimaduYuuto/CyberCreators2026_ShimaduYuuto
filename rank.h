//================================
//
//rank.cpp�ɕK�v�Ȑ錾[rank.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _RANK_H_ //���̃}�N����`������Ă��Ȃ�������
#define _RANK_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "object2D.h"

//�����N��UI�N���X
class CRank : public CObject2D
{
public:

	//�萔
	static const std::string TEXTUREPATH;	//�ǂݍ��ރp�X
	static const D3DXVECTOR3 POS;			//�ʒu
	static const D3DXVECTOR3 SIZE;			//�T�C�Y

	//�����o�֐�
	CRank(int nPriority = 3);	//�R���X�g���N�^
	~CRank() override;			//�f�X�g���N�^
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��
	static CRank* Create();		//�����N��UI�𐶐�

private:

};

#endif