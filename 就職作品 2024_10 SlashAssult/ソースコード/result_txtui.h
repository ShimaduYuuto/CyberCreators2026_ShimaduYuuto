//================================
//
//result_txtui.cpp�ɕK�v�Ȑ錾[result_txtui.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _RESULT_TEXTUI_H_ //���̃}�N����`������Ă��Ȃ�������
#define _RESULT_TEXTUI_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "object2D.h"

//�Q�[�W�N���X
class CResult_Txtui : public CObject2D
{
public:

	//�萔
	static const std::string TEXTUREPATH;	//�ǂݍ��ރp�X
	static const D3DXVECTOR3 POS;			//�ʒu
	static const D3DXVECTOR3 SIZE;			//�T�C�Y

	//�����o�֐�
	CResult_Txtui(int nPriority = 3);	//�R���X�g���N�^
	~CResult_Txtui() override;		//�f�X�g���N�^
	HRESULT Init() override;		//������
	void Uninit() override;			//�I��
	void Update() override;			//�X�V
	void Draw() override;			//�`��
	static CResult_Txtui* Create();	//����
};

#endif