//================================
//
//ui_gameguide.cpp�ɕK�v�Ȑ錾[ui_gameguide.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _UI_GAMEGUIDE_H_ //���̃}�N����`������Ă��Ȃ�������
#define _UI_GAMEGUIDE_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "object2D.h"
#include "animation.h"

//�Q�[����UI�N���X
class CUi_GameGuide : public CObject2D
{
public:

	//�K�C�hUI�̎��
	typedef enum
	{
		GUIDE_ATTACK = 0,
		GUIDE_GUARD,
		GUIDE_DASH,
		GUIDE_MAX,
	}GUIDE;

	//�R���g���[���̎��
	typedef enum
	{
		CONTROLLER_KEYBOARDMAUSE = 0,
		CONTROLLER_JOYPAD,
		CONTROLLER_MAX,
	}CONTROLLER;

	//�萔
	static const std::string TEXTURE_PATH[CONTROLLER_MAX][GUIDE_MAX];	//�e�N�X�`���p�X

	//�����o�֐�
	CUi_GameGuide(int nPriority = 3);		//�R���X�g���N�^
	~CUi_GameGuide() override;				//�f�X�g���N�^
	HRESULT Init() override;				//������
	void Uninit() override;					//�I��
	void Update() override;					//�X�V
	void Draw() override;					//�`��

	//����
	static CUi_GameGuide* Create(D3DXVECTOR3 pos, GUIDE type, D3DXVECTOR3 size);

private:

	GUIDE m_GuideType;	//���
	
};

#endif