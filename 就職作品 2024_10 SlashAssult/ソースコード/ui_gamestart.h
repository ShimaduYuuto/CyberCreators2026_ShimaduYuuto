//================================
//
//ui_gamestart.cpp�ɕK�v�Ȑ錾[ui_gamestart.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _UI_GAMESTART_H_ //���̃}�N����`������Ă��Ȃ�������
#define _UI_GAMESTART_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "object2D.h"

//gamestart��UI�N���X
class CUi_GameStart : public CObject2D
{
public:

	//�萔
	static constexpr float ADD_ALPHA{ 0.025f };	//��x�ɉ�����l

	//�萔
	static const std::string TEXTURE_PATH;	//�p�X
	static constexpr float WIDTH{ 400.0f };	//����
	static constexpr float HEIGHT{ 50.0f };//����
	static const D3DXVECTOR3 POS;			//�ʒu

	//�����o�֐�
	CUi_GameStart(int nPriority = 3);	//�R���X�g���N�^
	~CUi_GameStart() override;		//�f�X�g���N�^
	HRESULT Init() override;		//������
	void Uninit() override;			//�I��
	void Update() override;			//�X�V
	void Draw() override;			//�`��
	static CUi_GameStart* Create();	//����

private:
	float m_fCurrentAlpha;
	float m_fAddAlpha;
};

#endif