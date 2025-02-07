//================================
//
//title.cpp�ɕK�v�Ȑ錾[title.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _TITLE_H_ //���̃}�N����`������Ă��Ȃ�������
#define _TITLE_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "scene.h"
#include "field.h"
#include "title_player.h"

//�^�C�g���N���X
class CTitle : public CScene
{
public:

	//�����o�֐�
	CTitle();						//�R���X�g���N�^
	~CTitle() override;				//�f�X�g���N�^
	HRESULT Init() override;		//������
	void Uninit() override;			//�I��
	void Update() override;			//�X�V
	void Draw() override;			//�`��

	//�|�C���^�̎擾
	CTitle_Player* GetPlayer() { if (m_pPlayer == nullptr) { return nullptr; } return m_pPlayer; }				//�v���C���[�̎擾
	CField* GetField() { if (m_pField == nullptr) { return nullptr; } return m_pField; }						//�t�B�[���h�̎擾

private:
	CTitle_Player* m_pPlayer;			//�^�C�g���p�v���C���[
	CField* m_pField;					//�t�B�[���h
};

#endif