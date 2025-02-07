//================================
//
//title_player.cpp�ɕK�v�Ȑ錾[title_player.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _TITLE_PLAYER_H_ //���̃}�N����`������Ă��Ȃ�������
#define _TITLE_PLAYER_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

#include "character.h"

//�^�C�g���v���C���[�N���X
class CTitle_Player : public CCharacter
{
public:

	static const std::string FILEPATH;		//�ǂݍ��ރt�@�C��

	//�L�[�̎��
	typedef enum
	{
		TITLE_PLAYERMOTION_NORMAL = 0,
		TITLE_PLAYERMOTION_STANDUP,
		TITLE_PLAYERMOTION_MAX
	}TITLE_PLAYERMOTION;

	//�����o�֐�
	CTitle_Player(int nPriority = 2);		//�R���X�g���N�^
	~CTitle_Player() override;				//�f�X�g���N�^
	HRESULT Init() override;				//������
	void Uninit() override;					//�I��
	void Update() override;					//�X�V
	void Draw() override;					//�`��

	//�ÓI�֐�
	static CTitle_Player* Create();	//Player�̐���

};

#endif