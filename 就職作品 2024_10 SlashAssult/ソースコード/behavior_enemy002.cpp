//================================
//
//�G�̍s���܂Ƃ�[behavior_enemy002.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "behavior_enemy002.h"
#include "enemy002.h"
#include "enemybullet.h"
#include "game.h"
#include "manager.h"
#include "effect_death_boss.h"
#include "effect_explosion.h"
#include "direction_boss_destroy.h"

//======================================================================
//�ҋ@
//======================================================================

//====================================
//�R���X�g���N�^
//====================================
CEnemyBehavior_Standby::CEnemyBehavior_Standby(CEnemy* enemy) : m_nCoolTime(0)
{
	//�ݒ�
	enemy->SetMotion(CEnemy002::ENEMY002MOTION_NORMAL);	//���[�V����
	m_nCoolTime = COOL_TIME;							//�N�[���^�C��
	enemy->SetCollisionProcess(true);					//�����蔻��̏������s��
};

//====================================
//�A�N�V����(�ҋ@)
//====================================
void CEnemyBehavior_Standby::Action(CEnemy* enemy)
{
	//�N�[���^�C�������炷
	m_nCoolTime--;

	//�N�[���^�C�����I������玟�̍s�����s��
	if (m_nCoolTime < 0)
	{
		NextAction(enemy);
	}
}

//====================================
//���̍s����ݒ�
//====================================
void CEnemyBehavior_Standby::NextAction(CEnemy* enemy)
{
	//������
	SetNextAction(new CEnemyBehavior_Disappear(enemy));
}

//======================================================================
//�����鎞��
//======================================================================

//====================================
//�R���X�g���N�^
//====================================
CEnemyBehavior_Disappear::CEnemyBehavior_Disappear(CEnemy* enemy) : m_nDisappearTime(0)
{
	//��{�̐ݒ�
	enemy->SetMotion(CEnemy002::ENEMY002MOTION_NORMAL);	//���[�V����
	m_nDisappearTime = DISAPPEAR_TIME;					//�N�[���^�C��
	enemy->SetCollisionProcess(false);					//�����蔻��̏���
	
	//�ŗL�̐ݒ�
	CEnemy002* pEnemy002 = dynamic_cast<CEnemy002*>(enemy);
	pEnemy002->SetAlpha(0.0f);	//�����ɂȂ�
};

//====================================
//�A�N�V����(�ҋ@)
//====================================
void CEnemyBehavior_Disappear::Action(CEnemy* enemy)
{
	//�N�[���^�C�������炷
	m_nDisappearTime--;

	//�N�[���^�C�����I������玟�̍s�����s��
	if (m_nDisappearTime < 0)
	{
		//���̍s����ݒ�
		NextAction(enemy);

		//�ŗL�̐ݒ�
		CEnemy002* pEnemy002 = dynamic_cast<CEnemy002*>(enemy);
		pEnemy002->SetAlpha(CEnemy002::VALUE_INVISIBLE_ALPHA);	//�����ɂȂ�
	}
}

//====================================
//���̍s����ݒ�
//====================================
void CEnemyBehavior_Disappear::NextAction(CEnemy* enemy)
{
	//�c��̗͂ɉ����čs����ω�
	if (enemy->GetLife() > LIFE_FIRST_ATTACK)
	{
		//�U������
		SetNextAction(new CEnemyBehavior_WarpShot(enemy));
	}
	else
	{
		//�U������
		SetNextAction(new CEnemyBehavior_AlterEgoAttack(enemy));
	}
}

//======================================================================
//�`���[�W�V���b�g
//======================================================================

//====================================
//�R���X�g���N�^
//====================================
CEnemyBehavior_ChargeShot::CEnemyBehavior_ChargeShot(CEnemy* enemy) : 
	m_nChargeCount(0),	//�`���[�W�J�E���g
	m_pBullet(nullptr), //�e�̃|�C���^
	m_pEffect(nullptr), //�G�t�F�N�g�̃|�C���^
	m_bNext(false)		//���̍s���̈ڍs�t���O
{
	//�ݒ�
	enemy->SetMotion(CEnemy002::ENEMY002MOTION_CHARGESHOT);	//���[�V����
	enemy->SetCollisionProcess(false);
};

//====================================
//�f�X�g���N�^
//====================================
CEnemyBehavior_ChargeShot::~CEnemyBehavior_ChargeShot()
{
	//�e�̔j��
	if (m_pBullet != nullptr)
	{
		m_pBullet->Uninit();
		m_pBullet = nullptr;

		//�G�t�F�N�g�̔j��
		if (m_pEffect != nullptr)
		{
			m_pEffect->Uninit();
			m_pEffect = nullptr;
		}
	}
}

//====================================
//�A�N�V����(�`���[�W�V���b�g)
//====================================
void CEnemyBehavior_ChargeShot::Action(CEnemy* enemy)
{
	//�J�E���g�����؂��Ă��Ȃ��Ȃ�X�V
	if (m_nChargeCount <= CHARGE_TIME)
	{
		//�J�E���g�̍X�V
		m_nChargeCount++;

		//�v���C���[�̕���������
		LookAtPlayer(enemy);

		//�m�F��A�e�̐���
		if (CanCreateBullet())
		{
			CreateBullet(enemy);
		}

		//�e�������ς݂Ȃ�
		if (m_pBullet != nullptr)
		{
			UpdateBullet(enemy);
		}
	}

	//�������Ă��������
	if (CheckBulletHit())
	{
		HitBullet();
	}

	//�t���O�������Ă����玟�̍s����
	if (m_bNext)
	{
		NextAction(enemy);
	}
}

//====================================
//�v���C���[�̕���������
//====================================
void CEnemyBehavior_ChargeShot::LookAtPlayer(CEnemy* enemy)
{
	//�v���C���[�̊p�x���擾
	CGame* pGame = nullptr;
	pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());	//�Q�[���V�[���̎擾
	D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();			//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 Pos = enemy->GetPos();									//�����̈ʒu���擾

	//�v���C���[�Ƃ̊p�x���Z�o
	float fAngle = atan2f(PlayerPos.x - Pos.x, PlayerPos.z - Pos.z);//�Ίp���̊p�x���Z�o

	//�p�x��ݒ�
	enemy->SetGoalRot({ enemy->GetRot().x, fAngle + D3DX_PI, enemy->GetRot().z });
}

//====================================
//�e�̐������\�����m�F
//====================================
bool CEnemyBehavior_ChargeShot::CanCreateBullet()
{
	//�m�F
	if (m_nChargeCount <= CREATE_BULLET_TIME) return false;	//�J�E���g�������Ă���Ȃ�ʂ�
	if (m_pBullet != nullptr) return false;					//�e�͂܂���������Ă��Ȃ��Ȃ�ʂ�

	return true;
}

//====================================
//�e�̐���
//====================================
void CEnemyBehavior_ChargeShot::CreateBullet(CEnemy* enemy)
{
	//�e�ƃG�t�F�N�g�̐���
	m_pBullet = CEnemyBullet::Create(enemy->GetCollision()->GetPos(), { 0.0f, 0.0f, 0.0f }, this, enemy);	//�e�̐���
	m_pEffect = CEffect_ChargeShot::Create(enemy->GetCollision()->GetPos());								//�G�t�F�N�g�̐���

	//SE�̐ݒ�
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_CHARGE001);
}

//====================================
//�e�̍X�V
//====================================
void CEnemyBehavior_ChargeShot::UpdateBullet(CEnemy* enemy)
{
	//�v���C���[�̎擾
	CGame* pGame = nullptr;
	pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());	//�Q�[���V�[���̎擾
	D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();			//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 Pos = enemy->GetPos();									//�����̈ʒu���擾

	//�v���C���[�Ƃ̊p�x���Z�o
	float fAngle = atan2f(PlayerPos.x - Pos.x, PlayerPos.z - Pos.z);//�Ίp���̊p�x���Z�o

	//�e��傫������
	EnlargeBullet(enemy, fAngle);

	//�G�t�F�N�g�̈ʒu���X�V
	m_pEffect->SetPos(enemy->GetCollision()->GetPos());

	//�`���[�W���Ԃ��I�����甭��
	if (m_nChargeCount > CHARGE_TIME)
	{
		ShotBullet(fAngle);
	}
}

//====================================
//�e��傫������
//====================================
void CEnemyBehavior_ChargeShot::EnlargeBullet(CEnemy* enemy, float angle)
{
	//�X�P�[����傫������
	m_pBullet->AddSizeRate(ADD_SCALE_VALUE);

	//�傫���ɉ����Ēe�̋�����G���牓������
	m_pBullet->SetPos({ enemy->GetCollision()->GetPos().x + sinf(angle) * BULLET_LENGTH * m_pBullet->GetSizeRate(),
		enemy->GetCollision()->GetPos().y,
		enemy->GetCollision()->GetPos().z + cosf(angle) * BULLET_LENGTH * m_pBullet->GetSizeRate() });

}

//====================================
//�e�𔭎˂���
//====================================
void CEnemyBehavior_ChargeShot::ShotBullet(float angle)
{
	//�����Ă�������Ɍ���
	m_pBullet->SetMove({ sinf(angle) * BULLET_SPEED, 0.0f, cosf(angle) * BULLET_SPEED });
	m_pBullet->SetShooting(true);

	//SE�̐ݒ�
	CManager::GetInstance()->GetSound()->Stop(CSound::SOUND_LABEL_CHARGE001);	//�`���[�W�����~�߂�
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SHOT);	//���ˉ����~�߂�

	//�G�t�F�N�g�̔j��
	if (m_pEffect != nullptr)
	{
		m_pEffect->Uninit();
		m_pEffect = nullptr;
	}
}

//====================================
//�e���������Ă��邩���m�F
//====================================
bool CEnemyBehavior_ChargeShot::CheckBulletHit()
{
	//�m�F
	if (m_pBullet == nullptr) return false;		//�e���c���Ă���Ȃ�ʂ�
	if (!m_pBullet->GetDeath()) return false;	//�e�̎��S�t���O�������Ă���Ȃ�ʂ�

	return true;
}

//====================================
//�e���q�b�g���̏���
//====================================
void CEnemyBehavior_ChargeShot::HitBullet()
{
	m_pBullet = nullptr;	//�e�̃|�C���^�������Ȃ�
	m_bNext = true;			//���̍s���ֈڍs�t���O�𗧂Ă�
}

//====================================
//���̍s����ݒ�
//====================================
void CEnemyBehavior_ChargeShot::NextAction(CEnemy* enemy)
{
	//�ҋ@�s����ݒ�
	SetNextAction(new CEnemyBehavior_Standby(enemy));
}

//====================================
//�e�̃|�C���^�̍폜
//====================================
void CEnemyBehavior_ChargeShot::Erase(CEnemyBullet* bullet)
{
	//�����|�C���^�Ȃ璆�g��nullptr�ɂ���
	if (m_pBullet == bullet)
	{
		m_pBullet = nullptr;
		m_bNext = true;
	}
}

//======================================================================
//���[�v�V���b�g
//======================================================================

//====================================
//�R���X�g���N�^
//====================================
CEnemyBehavior_WarpShot::CEnemyBehavior_WarpShot(CEnemy* enemy) : CEnemyBehavior_ChargeShot(enemy)
{
	//�ݒ�
	enemy->SetMotion(CEnemy002::ENEMY002MOTION_CHARGESHOT);	//���[�V����

	//�����_���Ȉʒu�ɓG�𐶐�
	enemy->SetPos(D3DXVECTOR3(sinf(CRandom::GetInstance()->GetRandom(-D3DX_PI, D3DX_PI)) * CRandom::GetInstance()->GetRandom(0.0f, MAX_RUNDOM_LENGTH)
		, 0.0f
		, cosf(CRandom::GetInstance()->GetRandom(-D3DX_PI, D3DX_PI)) * CRandom::GetInstance()->GetRandom(0.0f, MAX_RUNDOM_LENGTH)) + enemy->GetStartPos());
};

//====================================
//�f�X�g���N�^
//====================================
CEnemyBehavior_WarpShot::~CEnemyBehavior_WarpShot()
{
	
}

//====================================
//�A�N�V����(�`���[�W�V���b�g)
//====================================
void CEnemyBehavior_WarpShot::Action(CEnemy* enemy)
{
	//�`���[�W�V���b�g�̍X�V
	CEnemyBehavior_ChargeShot::Action(enemy);
}

//====================================
//���̍s����ݒ�
//====================================
void CEnemyBehavior_WarpShot::NextAction(CEnemy* enemy)
{
	//�ҋ@��Ԃ̐ݒ�
	SetNextAction(new CEnemyBehavior_Standby(enemy));
}

//======================================================================
//�o�ꉉ�o
//======================================================================

//====================================
//�R���X�g���N�^
//====================================
CEnemyBehavior_Direction::CEnemyBehavior_Direction(CEnemy* enemy) :
	m_nCount(0)
{
	//��{�̐ݒ�
	enemy->SetMotion(CEnemy002::ENEMY002MOTION_DIRECTION);	//���[�V����

	//�Q�[���V�[���ɉ��o��ݒ�
	CGame* pGame = nullptr;
	pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());	//�Q�[���V�[���̎擾
	pGame->SetDirection(CDirection::DIRECTIONTYPE_BOSS);				//���o�̐ݒ�

	//�ŗL�̐ݒ�
	CEnemy002* pEnemy002 = dynamic_cast<CEnemy002*>(enemy);	//�_�E���L���X�g
	pEnemy002->SetMaterialized(true);						//���̉��̔���					
}

//====================================
//�A�N�V����(���o)
//====================================
void CEnemyBehavior_Direction::Action(CEnemy* enemy)
{
	//�J�E���g�̑���
	m_nCount++;

	//���o�̎��Ԃ��}�����玟�̍s����ݒ�
	if (m_nCount > DIRECTION_TIME)
	{
		NextAction(enemy);
	}
}

//====================================
//���̍s����ݒ�
//====================================
void CEnemyBehavior_Direction::NextAction(CEnemy* enemy)
{
	//�ҋ@�s����ݒ�
	SetNextAction(new CEnemyBehavior_Standby(enemy));
}

//======================================================================
//���g�U��
//======================================================================

//====================================
//�R���X�g���N�^
//====================================
CEnemyBehavior_AlterEgoAttack::CEnemyBehavior_AlterEgoAttack(CEnemy* enemy) : CEnemyBehavior_ChargeShot(enemy),
	m_pShotAction(nullptr),		//�A�N�V�����̃|�C���^
	m_bCreateAlterEgo(false),	//���g�𐶐�������
	m_pAlterEgo(),				//���g�̃|�C���^
	m_fRundam(0.0f)				//�����_���l
{
	//�ݒ�
	enemy->SetMotion(CEnemy002::ENEMY002MOTION_NORMAL);	//���[�V����

	//���g�̃|�C���^��������
	for (int i = 0; i < NUM_ALTEREGO; i++)
	{
		m_pAlterEgo[i] = nullptr;
	}

	//�{�̂̐ݒ�
	m_fRundam = CRandom::GetInstance()->GetRandom(-D3DX_PI, D3DX_PI);
	enemy->SetPos(D3DXVECTOR3(sinf(m_fRundam) * LENGTH_ENEMY, 0.0f, cosf(m_fRundam) * LENGTH_ENEMY) + enemy->GetStartPos());	//�ʒu�̐ݒ�
	enemy->SetMotion(CEnemy002::ENEMY002MOTION_CHARGESHOT);																		//���[�V�����̐ݒ�

	//���g�𐶐�
	for (int i = 0; i < NUM_ALTEREGO; i++)
	{
		float fAngle = (D3DX_PI * 2.0f) / (NUM_ALTEREGO + 1) * (i + 1) + m_fRundam;	//�p�x���Z�o
		D3DXVECTOR3 Pos = (D3DXVECTOR3(
			sinf(fAngle) * LENGTH_ENEMY,
			0.0f,
			cosf(fAngle) * LENGTH_ENEMY));	//�ʒu���Z�o

		//����
		m_pAlterEgo[i] = CEnemy002_AlterEgo::Create(Pos + enemy->GetStartPos(), this);
	}
}

//====================================
//�f�X�g���N�^
//====================================
CEnemyBehavior_AlterEgoAttack::~CEnemyBehavior_AlterEgoAttack()
{
	//���g��j��
	for (int i = 0; i < NUM_ALTEREGO; i++)
	{
		if (m_pAlterEgo[i] != nullptr)
		{
			m_pAlterEgo[i]->Uninit();
			m_pAlterEgo[i] = nullptr;
		}
	}
}

//====================================
//�A�N�V����(���g)
//====================================
void CEnemyBehavior_AlterEgoAttack::Action(CEnemy* enemy)
{
	//���[�J���ϐ�
	int nNumAlterEgo = 0;		//���݂̕��g�̐�

	//���g���X�V
	for (int i = 0; i < NUM_ALTEREGO; i++)
	{
		//���݂��Ȃ��A�܂��͎��S���Ă���Ȃ�X�V���Ȃ�
		if (m_pAlterEgo[i] == nullptr || m_pAlterEgo[i]->GetDeath())
		{
			m_pAlterEgo[i] = nullptr;
			continue;
		}

		//�X�V
		nNumAlterEgo++;
	}

	//�ʒu�̍X�V
	UpdatePos(enemy);

	//���g�����Ȃ��Ȃ�ڍs
	if (nNumAlterEgo == 0 && GetBullet() == nullptr)
	{
		SetNextFlag(true);
	}

	//�A�N�V����
	CEnemyBehavior_ChargeShot::Action(enemy);
}

//====================================
//�ʒu�̍X�V
//====================================
void CEnemyBehavior_AlterEgoAttack::UpdatePos(CEnemy* enemy)
{
	//�e�̔��ˏ󋵂��m�F
	if (GetBullet() == nullptr) return;
	if (GetBullet()->GetShooting()) return;

	//�{�̂̐ݒ�
	m_fRundam += ADD_RUNDOM;
	enemy->SetPos(D3DXVECTOR3(sinf(m_fRundam) * LENGTH_ENEMY, 0.0f, cosf(m_fRundam) * LENGTH_ENEMY) + enemy->GetStartPos());

	//���g�𐶐�
	for (int i = 0; i < NUM_ALTEREGO; i++)
	{
		//���g�̊m�F
		if (m_pAlterEgo[i] == nullptr) continue;

		//�ʒu��ݒ�
		float fAngle = (D3DX_PI * 2.0f) / (NUM_ALTEREGO + 1) * (i + 1) + m_fRundam;	//�p�x���Z�o
		D3DXVECTOR3 Pos = (D3DXVECTOR3(
			sinf(fAngle) * LENGTH_ENEMY,
			0.0f,
			cosf(fAngle) * LENGTH_ENEMY));	//�ʒu���Z�o

		m_pAlterEgo[i]->SetPos(Pos + enemy->GetStartPos());	//�ʒu�̐ݒ�
	}
}

//====================================
//���g�̃|�C���^�̍폜
//====================================
void CEnemyBehavior_AlterEgoAttack::Erase(CEnemy002_AlterEgo* enemy)
{
	//�z�񕪎���
	for (int i = 0; i < NUM_ALTEREGO; i++)
	{
		//�ێ����Ă��镪�g������Ȃ�nullptr�ɂ���
		if (m_pAlterEgo[i] == enemy)
		{
			m_pAlterEgo[i] = nullptr;
		}
	}
}

//====================================
//���̍s����ݒ�
//====================================
void CEnemyBehavior_AlterEgoAttack::NextAction(CEnemy* enemy)
{
	//�ҋ@�s����ݒ�
	SetNextAction(new CEnemyBehavior_Standby(enemy));
}

//======================================================================
//���j���o
//======================================================================

//�萔
const D3DXVECTOR3 CEnemyBehavior_Direction_Destroy::CAMERA_POSV = { 0.0f, 0.0f, -200.0f };

//====================================
//�R���X�g���N�^
//====================================
CEnemyBehavior_Direction_Destroy::CEnemyBehavior_Direction_Destroy(CEnemy* enemy) :
	m_nCount(0)
{
	//���[�V�����̐ݒ�
	enemy->SetMotion(CEnemy002::ENEMY002MOTION_DEATHDIRECTION);

	//�Q�[���V�[���ɉ��o��ݒ�
	CGame* pGame = nullptr;
	pGame = (CGame*)CManager::GetInstance()->GetScene();			//�Q�[���V�[���̎擾
	pGame->SetDirection(CDirection::DIRECTIONTYPE_BOSS_DESTROY);	//���o�̐ݒ�

	//�ŗL�̐ݒ�
	CEnemy002* pEnemy002 = (CEnemy002*)enemy;									//�_�E���L���X�g
	pEnemy002->SetMaterialized(true);											//���̉�����
	pEnemy002->SetPos(pEnemy002->GetPos() + D3DXVECTOR3(0.0f, 1.0f, 0.0f));		//�ʒu�̐ݒ�

	//�G�t�F�N�g�̐���
	CEffect_Death_Boss::Create(&pEnemy002->GetCollision()->GetPos());
}

//====================================
//�A�N�V����(���o)
//====================================
void CEnemyBehavior_Direction_Destroy::Action(CEnemy* enemy)
{
	//���o�̎��Ԃ��I�������s���J�n
	m_nCount++;

	//�J�����̈ʒu��ݒ�
	CManager::GetInstance()->GetCamera()->SetPosR(enemy->GetCollision()->GetPos());
	CManager::GetInstance()->GetCamera()->SetPosV(enemy->GetCollision()->GetPos() + CAMERA_POSV);
	
	//�J������h�炷���Ԃɔ����𐶐�
	if (m_nCount == CDirection_Boss_Destroy::START_SHAKE_FRAME)
	{
		CEffect_Explosion::Create(enemy->GetPos());
	}

	//���o�̎��Ԃ��}������G��j��
	if (m_nCount > DIRECTION_TIME)
	{
		enemy->Uninit();
	}
}