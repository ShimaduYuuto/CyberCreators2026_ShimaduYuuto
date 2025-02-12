//================================
//
//enemy003.cpp�ɕK�v�Ȑ錾[enemy003.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _ENEMY003_H_ //���̃}�N����`������Ă��Ȃ�������
#define _ENEMY003_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "enemy.h"
#include "state_enemy003.h"

//�G�l�~�[�N���X
class CEnemy003 : public CEnemy
{
public:

	//�萔
	static const std::string FILEPATH;		//�ǂݍ��ރt�@�C��
	static const float MOVE_VALUE;			//�ړ���
	static const float STARTATTACK_RANGE;	//�U�����n�߂�͈�
	static constexpr int LIFE{ 10 };		//�̗�

	//�G�̃��[�V����
	typedef enum
	{
		ENEMY003MOTION_NORMAL = 0,	//�j���[�g����
		ENEMY003MOTION_WALK,		//�ړ�
		ENEMY003MOTION_ACTION,		//�A�N�V����
		ENEMY003MOTION_DAMAGE,		//�_���[�W
		ENEMY003MOTION_MAX			//�ő�
	}ENEMY003MOTION;

	//�����o�֐�
	CEnemy003();						//�R���X�g���N�^
	~CEnemy003() override;				//�f�X�g���N�^
	HRESULT Init() override;			//������
	void Uninit() override;				//�I��
	void Update() override;				//�X�V
	void Draw() override;				//�`��

	//�_���[�W�̐ݒ�
	bool SetDamage(int damage, float angle) override;	//�_���[�W�̐ݒ�

	//��Ԃ̃��Z�b�g
	void StateReset() override;

	//�\��t����ԂɕύX
	void ChangeStickState() override;

	//�X�^����ԂɕύX
	void ChangeStanState() override;

	//�U������
	void SetAttacking(bool attacking) { m_bAttacking = attacking; }	//�ݒ�
	bool GetAttacking() { return m_bAttacking; }					//�擾

private:

	//�ϐ�
	bool m_bAttacking;	//�U������
};

#endif