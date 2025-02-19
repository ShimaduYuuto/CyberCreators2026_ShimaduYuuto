//================================
//
//effect_billboard.cpp�ɕK�v�Ȑ錾[effect_billboard.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _EFFECT_BILLBOARD_H_ //���̃}�N����`������Ă��Ȃ�������
#define _EFFECT_BILLBOARD_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "objectbillboard.h"
#include "animation.h"

//�r���{�[�h�G�t�F�N�g�N���X
class CEffect_Billboard : public CObjectBillboard
{
public:

	//�����o�֐�
	CEffect_Billboard();			//�R���X�g���N�^
	~CEffect_Billboard() override;	//�f�X�g���N�^
	void Update() override;			//�X�V

	//�A�j���N���X
	CAnimation& GetAnim() { return m_Anim; }	//�擾

private:

	//�ϐ�
	CAnimation m_Anim;	//�A�j���[�V�����p�̏��
};

#endif