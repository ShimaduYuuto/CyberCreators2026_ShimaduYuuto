//================================
//
//lifegauge.cpp�ɕK�v�Ȑ錾[lifegauge.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _LIFEGAUGE_H_ //���̃}�N����`������Ă��Ȃ�������
#define _LIFEGAUGE_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "gauge.h"

//�Q�[�W�N���X
class CLifeGauge : public CGauge
{
public:

	//�萔
	static const std::string TEXTUREPATH;	//�ǂݍ��ރp�X

	//�����o�֐�
	CLifeGauge(int nPriority = 3);	//�R���X�g���N�^
	~CLifeGauge() override;			//�f�X�g���N�^
	void Draw() override;		//�`��
	static CLifeGauge* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float max);	//�Q�[�W�̐���
};

#endif