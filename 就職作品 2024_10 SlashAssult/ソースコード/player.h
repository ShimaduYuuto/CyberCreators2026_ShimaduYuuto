//================================
//
//player.cpp�ɕK�v�Ȑ錾[player.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _PLAYER_H_ //���̃}�N����`������Ă��Ȃ�������
#define _PLAYER_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

#include "game_character.h"
#include "gauge_playerlife.h"
#include "orbit.h"
#include "state_player.h"
#include "enemy.h"

//�O���錾
class CState_Player;

//�v���C���[�N���X
class CPlayer : public CGame_Character
{
public:
	//�萔
	static const float DAMAGE_IMPULSE;		//�_���[�W�̃m�b�N�o�b�N��
	static const std::string FILEPATH;		//�ǂݍ��ރt�@�C��
	
	//�L�[�̎��
	typedef enum
	{
		PLAYERMOTION_NORMAL = 0,
		PLAYERMOTION_WALK,
		PLAYERMOTION_ACTION,
		PLAYERMOTION_JUMP,
		PLAYERMOTION_ARIAL000,
		PLAYERMOTION_ARIAL001,
		PLAYERMOTION_ARIAL002,
		PLAYERMOTION_KNOCKBACK,
		PLAYERMOTION_DAMAGE,
		PLAYERMOTION_ACTION001,
		PLAYERMOTION_ACTION002,
		PLAYERMOTION_ATTACKCHARGE,
		PLAYERMOTION_CHARGEATTACK,
		PLAYERMOTION_DASHATTACK000,
		PLAYERMOTION_DASHATTACK001,
		PLAYERMOTION_COUNTER,
		PLAYERMOTION_GUARD,
		PLAYERMOTION_DEATH,
		PLAYERMOTION_MAX
	}PLAYERMOTION;

	//�����o�֐�
	CPlayer(int nPriority = 2);				//�R���X�g���N�^
	~CPlayer() override;					//�f�X�g���N�^
	HRESULT Init() override;				//������
	void Uninit() override;					//�I��
	void Update() override;					//�X�V
	void Draw() override;					//�`��
	bool SetDamage(int damage, float angle) override;	//�_���[�W��ݒ�
	D3DXVECTOR3 GravityMove(D3DXVECTOR3 move) override;	//�d�͂̏���
	void UpdatePos() override;				//�ʒu�̍X�V

	//�ݒ�Ǝ擾
	void SetState(CState_Player* state);									//��Ԃ̐ݒ�
	void SetKnockBack(int time);											//�m�b�N�o�b�N�̐ݒ�
	void SetLifeGauge(CGauge_PlayerLife* gauge) { m_pLifeGauge = gauge; }	//�̗̓Q�[�W�̐ݒ�
	CGauge_PlayerLife* GetLifeGauge() { return m_pLifeGauge; }				//�̗̓Q�[�W�̎擾
	void SetGuardJudge(bool judge) { m_bGuard = judge; }					//�K�[�h����̐ݒ�
	bool GetGuardJudge() { return m_bGuard; }								//�K�[�h����̎擾

	//��ԕύX
	void ChangeState(CState_Player* state);
	CState_Player* GetState() { if (m_pState != nullptr) { return m_pState; } return nullptr; }

	//���S���̏���
	void SetCharacterDeath() override;

	//�ÓI�֐�
	static CPlayer* Create();	//Player�̐���
private:

	void CollisionJudge();	//�R���W�����̔���
	void UpdateState();		//��Ԃ̍X�V

	//�����o�ϐ�
	CGauge_PlayerLife* m_pLifeGauge;//�̗̓Q�[�W�̃|�C���^
	CState_Player* m_pState;		//��Ԃ̃C���X�^���X
	bool m_bGuard;					//�K�[�h���Ă��邩
};

#endif