//================================
//
//enemy002.cpp�ɕK�v�Ȑ錾[enemy002.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _ENEMY002_H_ //���̃}�N����`������Ă��Ȃ�������
#define _ENEMY002_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "enemy.h"

//�G�l�~�[�N���X
class CEnemy002 : public CEnemy
{
public:

	//�萔
	static const std::string FILEPATH;						//�ǂݍ��ރt�@�C��
	static constexpr float VALUE_INVISIBLE_ALPHA{ 0.3f };	//������Ԃ̃��l
	static constexpr int LIFE{ 100 };						//�̗�
	
	//�G�̃��[�V����
	typedef enum
	{
		ENEMY002MOTION_NORMAL = 0,	//�j���[�g����
		ENEMY002MOTION_WALK,		//�ړ�
		ENEMY002MOTION_TAKEOUT,		//���o��
		ENEMY002MOTION_THROW,		//������
		ENEMY002MOTION_CHARGESHOT,	//�`���[�W�V���b�g
		ENEMY002MOTION_STAN,		//�X�^��
		ENEMY002MOTION_DIRECTION,	//���o�p
		ENEMY002MOTION_MAX			//�ő�
	}ENEMY002MOTION;

	//�����o�֐�
	CEnemy002();						//�R���X�g���N�^
	~CEnemy002() override;				//�f�X�g���N�^
	HRESULT Init() override;			//������
	void Uninit() override;				//�I��
	void Update() override;				//�X�V
	void Draw() override;				//�`��

	//�_���[�W�̐ݒ�
	bool SetDamage(int damage) override;								//�_���[�W�̐ݒ�
	bool SetDamage(int damage, float rotY) override;					//�_���[�W�̐ݒ�
	bool SetBlowDamage(int damage, float rotY) override;				//������΂��ă_���[�W��^����
	bool SetBlowDamage(int damage, float rotY, float value) override;	//������΂��ă_���[�W��^����

	//��Ԃ̃��Z�b�g
	void StateReset() override;

	//�\��t����ԂɕύX
	void ChangeStickState() override;

	//�X�^����ԂɕύX
	void ChangeStanState() override;

	//���̉����Ă��邩
	void SetMaterialized(bool materialized);									//�ݒ�
	bool GetMaterialized() { return m_bMaterialized; }							//�擾

private:
	bool m_bMaterialized;	//���̉����Ă��邩
};

#endif