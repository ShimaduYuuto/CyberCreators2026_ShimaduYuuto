//================================
//
//behavior_enemy002.cpp�ɕK�v�Ȑ錾[behavior_enemy002.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BEHAVIOR_ENEMY002_H_ //���̃}�N����`������Ă��Ȃ�������
#define _BEHAVIOR_ENEMY002_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "behavior_enemy.h"
#include "enemybullet.h"
#include "effect_chargeshot.h"
#include "enemy002_alterego.h"

//�O���錾
class CEnemy002_AlterEgo;

//==========================
//�ǂ�������
//==========================
class CEnemyBehavior_Standby : public CEnemyBehavior
{
public:

	//�֐�
	CEnemyBehavior_Standby(CEnemy* enemy);	//�R���X�g���N�^
	void Action(CEnemy* enemy) override;	//�A�N�V����
	void NextAction(CEnemy* enemy) override;//�U���A�N�V������ݒ�

private:

	//�萔
	static constexpr int COOL_TIME{ 90 };			//�N�[���^�C���̎���
	static constexpr int LIFE_FIRST_ATTACK{ 35 };	//�P�Ԗڂ̍U�����s���̗�

	//�ϐ�
	int m_nCoolTime;	//�N�[���^�C��
};

//==========================
//������
//==========================
class CEnemyBehavior_Disappear : public CEnemyBehavior
{
public:

	//�֐�
	CEnemyBehavior_Disappear(CEnemy* enemy);	//�R���X�g���N�^
	void Action(CEnemy* enemy) override;		//�A�N�V����
	void NextAction(CEnemy* enemy) override;	//�U���A�N�V������ݒ�

private:

	//�萔
	static constexpr int DISAPPEAR_TIME{ 60 };		//�����鎞��
	static constexpr int LIFE_FIRST_ATTACK{ 35 };	//�P�Ԗڂ̍U�����s���̗�

	//�ϐ�
	int m_nDisappearTime;	//�����鎞��
};

//�O���錾
class CEnemyBullet;

//==========================
//�`���[�W�V���b�g
//==========================
class CEnemyBehavior_ChargeShot : public CEnemyBehavior
{
public:

	//�֐�
	CEnemyBehavior_ChargeShot(CEnemy* enemy);	//�R���X�g���N�^
	~CEnemyBehavior_ChargeShot();				//�f�X�g���N�^
	void Action(CEnemy* enemy) override;	//�U��
	void NextAction(CEnemy* enemy) override;//�ҋ@�A�N�V������ݒ�
	void Erase(CEnemyBullet* bullet);		//�e�̃|�C���^���폜

	//�e�̃|�C���^
	void SetBullet(CEnemyBullet* bullet) { m_pBullet = bullet; }	//�ݒ�
	CEnemyBullet* GetBullet() { return m_pBullet; }					//�擾

	//���̍s���Ɉڍs����t���O
	void SetNextFlag(bool flag) { m_bNext = flag; }	//�ݒ�

private:

	//�萔
	static constexpr int CHARGE_TIME{ 230 };			//�`���[�W����
	static constexpr int CREATE_BULLET_TIME{ 50 };		//�e�̐�������
	static constexpr int END_TIME{ 300 };				//�A�N�V�����I������
	static constexpr float ADD_SCALE_VALUE{ 0.02f };	//�X�P�[���̉��Z��
	static constexpr float BULLET_LENGTH{ 18.0f };		//�e�̐������鋗��
	static constexpr float BULLET_SPEED{ 3.0f };		//�e��
	static constexpr float MAX_RUNDOM_LENGTH{ 400.0f };	//�����̍ő僉���_���l

	//�֐�
	void LookAtPlayer(CEnemy* enemy);	//�v���C���[�̕���������
	void CreateBullet(CEnemy* enemy);	//�e�̐���
	bool CanCreateBullet();				//�e�̐������o���邩
	void UpdateBullet(CEnemy* enemy);	//�e�̍X�V
	void EnlargeBullet(CEnemy* enemy, float angle);	//�e��傫������
	void ShotBullet(float angle);		//�e�𔭎˂���
	bool CheckBulletHit();				//�e���������Ă��邩�m�F
	void HitBullet();					//�e���q�b�g���̏���

	//�ϐ�
	int m_nChargeCount;				//�`���[�W�̃J�E���g
	CEnemyBullet* m_pBullet;		//�e�̃|�C���^
	CEffect_ChargeShot* m_pEffect;	//�G�t�F�N�g�̃|�C���^
	bool m_bNext;					//���̍s�������邩
};

//==========================
//���[�v�V���b�g
//==========================
class CEnemyBehavior_WarpShot : public CEnemyBehavior_ChargeShot
{
public:

	//�֐�
	CEnemyBehavior_WarpShot(CEnemy* enemy);		//�R���X�g���N�^
	~CEnemyBehavior_WarpShot() override;			//�f�X�g���N�^
	void Action(CEnemy* enemy) override;		//�U��
	void NextAction(CEnemy* enemy) override;	//�ҋ@�A�N�V������ݒ�

private:

	//�萔
	static constexpr float MAX_RUNDOM_LENGTH{ 400.0f };	//�����̍ő僉���_���l
	
};

//==========================
//���o
//==========================
class CEnemyBehavior_Direction : public CEnemyBehavior
{
public:

	//�֐�
	CEnemyBehavior_Direction(CEnemy* enemy);	//�R���X�g���N�^
	void Action(CEnemy* enemy) override;	//���o
	void NextAction(CEnemy* enemy) override;//�X�^���o�C�A�N�V������ݒ�

private:

	//�萔
	static constexpr int DIRECTION_TIME{ 300 };	//���o�̎���

	//�ϐ�
	int m_nCount;	//�J�E���g�p
};

//==========================
//���j���o
//==========================
class CEnemyBehavior_Direction_Destroy : public CEnemyBehavior
{
public:

	//�֐�
	CEnemyBehavior_Direction_Destroy(CEnemy* enemy);	//�R���X�g���N�^
	void Action(CEnemy* enemy) override;			//���o

private:

	//�萔
	static constexpr int DIRECTION_TIME{ 500 };	//���o�̎���
	static const D3DXVECTOR3 CAMERA_POSV;		//�J�������_�̈ʒu

	//�ϐ�
	int m_nCount;	//�J�E���g�p
};


//==========================
//���g�U��
//==========================
class CEnemyBehavior_AlterEgoAttack : public CEnemyBehavior_ChargeShot
{
public:

	
	//�֐�
	CEnemyBehavior_AlterEgoAttack(CEnemy* enemy);	//�R���X�g���N�^
	~CEnemyBehavior_AlterEgoAttack();				//�f�X�g���N�^
	void Action(CEnemy* enemy) override;			//���g��Ɏˌ�
	void NextAction(CEnemy* enemy) override;		//�ҋ@�A�N�V������ݒ�
	void Erase(CEnemy002_AlterEgo* enemy);			//���g�̃|�C���^���폜

private:

	//�萔
	static constexpr float TIME_INTERPOLATION_ALPHA{ 10 };	//�A���t�@�l��ω������鎞��
	static constexpr int TIME_START_APPEAR{ 60 };			//�o�����n�߂鎞��
	static constexpr int TIME_END_ACTION{ 90 };				//�A�N�V�����̏I��鎞��
	static constexpr int NUM_ALTEREGO{ 3 };					//���g�̐�
	static constexpr float LENGTH_ENEMY{ 300.0f };			//�G�̋���
	static constexpr float ADD_RUNDOM{ 0.03f };			//�����_���l�̉��Z��

	//�֐�
	void UpdatePos(CEnemy* enemy);	//�ʒu�̍X�V

	//�ϐ�
	bool m_bCreateAlterEgo;							//���g�𐶐�������
	CEnemyBehavior_ChargeShot* m_pShotAction;		//�V���b�g�̃|�C���^
	CEnemy002_AlterEgo* m_pAlterEgo[NUM_ALTEREGO];	//���g�̃|�C���^
	float m_fRundam;								//�����̕ۑ�
};

#endif