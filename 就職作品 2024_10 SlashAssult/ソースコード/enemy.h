//================================
//
//enemy.cpp�ɕK�v�Ȑ錾[enemy.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _ENEMY_H_ //���̃}�N����`������Ă��Ȃ�������
#define _ENEMY_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "game_character.h"
#include "collision.h"
#include "state_enemy.h"

//�O���錾
class CState_Enemy;
class CPlayer;

//�G�l�~�[�N���X
class CEnemy : public CGame_Character
{
public:

	//�萔
	static constexpr float VALUE_KNOCKBACK = 10.0f;	//�m�b�N�o�b�N�l
	static constexpr float VALUE_BLOWOFF = 5.0f;	//������ԗ�

	//�G�l�~�[�̎�ނ̗񋓌^
	typedef enum
	{
		ENEMYTYPE_ENEMY000 = 0,	//�ʏ�̃G�l�~�[
		ENEMYTYPE_ENEMY001,		//�������̃G�l�~�[
		ENEMYTYPE_ENEMY002,		//�{�X�̃G�l�~�[
		ENEMYTYPE_ENEMY003,		//�ːi�̃G�l�~�[
		ENEMYTYPE_MAX,			//�ő�l
	}ENEMYTYPE;

	//�����o�֐�
	CEnemy(int nPriority = 3);	//�R���X�g���N�^
	virtual ~CEnemy() override;										//�f�X�g���N�^
	virtual HRESULT Init() override;								//������
	virtual void Uninit() override;									//�I��
	virtual void Update() override;									//�X�V
	virtual void Draw() override;									//�`��
	static CEnemy* Create(D3DXVECTOR3 pos, ENEMYTYPE type);			//�G�l�~�[�̐���
	ENEMYTYPE& GetType() { return m_EnemyType; }					//�G�l�~�[�̎�ނ�Ԃ�

	//��ԏ����̊֐�
	virtual bool SetBlowOff();

	//�_���[�W�̐ݒ�
	bool SetDamage(int damage, float angle) override;				//�_���[�W�̐ݒ�
	//virtual bool SetDamage(int damage, float rotY);					//�_���[�W�̐ݒ�
	virtual bool SetBlowDamage(int damage, float rotY);				//������΂��ă_���[�W��^����
	virtual bool SetBlowDamage(int damage, float rotY, float value);//������΂��ă_���[�W��^����

	//��ԕύX
	void ChangeState(CState_Enemy* state);
	CState_Enemy* GetState() { if (m_pState != nullptr) { return m_pState; } return nullptr; }

	//�ŏ��̈ʒu
	D3DXVECTOR3 GetStartPos() { return m_StartPos; }	//�擾

	//�_���[�W��^�����ۂɗ^����e��
	virtual void DamageEffect(CPlayer* player) {}

	//��Ԃ̃��Z�b�g
	virtual void StateReset()
	{
		
	}

	//�\��t����ԂɕύX
	virtual void ChangeStickState()
	{

	}

	//�X�^����ԂɕύX
	virtual void ChangeStanState()
	{

	}

	//�R���W��������
	void SetCollisionProcess(bool process) { m_bCollisionProcess = process; }	//�ݒ�
	bool GetCollisionProcess() { return m_bCollisionProcess; }					//�擾

	//���S���̏���
	void SetCharacterDeath() override;

private:

	//�����o�ϐ�
	ENEMYTYPE m_EnemyType;
	CState_Enemy* m_pState;
	D3DXVECTOR3 m_StartPos;		//�ŏ��̈ʒu
	bool m_bCollisionProcess;	//�R���W�������������邩
};

#endif