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

//======================================================================
//�ҋ@
//======================================================================

//====================================
//�A�N�V����(�ҋ@)
//====================================
void CEnemyAction_Standby::Action(CEnemy* enemy)
{
	//�N�[���^�C�����I������玟�̍s�����s��
	m_nCoolTime--;

	if (m_nCoolTime < 0)
	{
		//�c��̗͂ɉ����čs����ω�
		if (enemy->GetLife() > 90)
		{
			//�U������
			SetNextAction(new CEnemyAction_ChargeShot(enemy));
		}
		else
		{
			//�U������
			SetNextAction(new CEnemyAction_AlterEgoAttack(enemy));
		}
	}
}

//====================================
//���̍s����ݒ�
//====================================
void CEnemyAction_Standby::NextAction(CEnemy* enemy)
{
	//�U����ݒ�
	SetNextAction(new CEnemyAction_Attack002(enemy));
}

//======================================================================
//�`���[�W�V���b�g
//======================================================================

//====================================
//�f�X�g���N�^
//====================================
CEnemyAction_ChargeShot::~CEnemyAction_ChargeShot()
{
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
void CEnemyAction_ChargeShot::Action(CEnemy* enemy)
{
	//�J�E���g�����؂��Ă��Ȃ��Ȃ�X�V
	if (m_nChargeCount <= CHARGE_TIME)
	{
		CGame* pGame = nullptr;
		pGame = (CGame*)CManager::GetInstance()->GetScene();		//�Q�[���V�[���̎擾
		D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();	//�v���C���[�̈ʒu���擾
		D3DXVECTOR3 Pos = enemy->GetPos();							//�����̈ʒu���擾

		//�v���C���[�Ƃ̊p�x���Z�o
		float fAngle = atan2f(PlayerPos.x - Pos.x, PlayerPos.z - Pos.z);//�Ίp���̊p�x���Z�o

		//�p�x��ݒ�
		enemy->SetGoalRot({ enemy->GetRot().x, fAngle + D3DX_PI, enemy->GetRot().z });

		//�J�E���g�̍X�V
		m_nChargeCount++;

		//�e�̐������ԂɂȂ����琶��
		if (m_nChargeCount > CREATE_BULLET_TIME)
		{
			//�e�̐���
			if (m_pBullet == nullptr)
			{
				m_pBullet = CEnemyBullet::Create(enemy->GetCollision()->GetPos(), { 0.0f, 0.0f, 0.0f });
				m_pEffect = CEffect_ChargeShot::Create(enemy->GetCollision()->GetPos());
			}
		}

		//�e�������ς݂Ȃ�
		if (m_pBullet != nullptr)
		{
			//�X�P�[����傫������
			m_pBullet->AddSizeRate(ADD_SCALE_VALUE);
			m_pBullet->SetPos({ enemy->GetCollision()->GetPos().x + sinf(fAngle) * 20.0f * m_pBullet->GetSizeRate() , enemy->GetCollision()->GetPos().y, enemy->GetCollision()->GetPos().z + cosf(fAngle) * 20.0f * m_pBullet->GetSizeRate() });

			//�`���[�W���Ԃ��I�����甭��
			if (m_nChargeCount > CHARGE_TIME)
			{
				//�����Ă�������Ɍ���
				m_pBullet->SetMove({ sinf(fAngle) * 3.0f, 0.0f, cosf(fAngle) * 3.0f });
				m_pBullet->SetShooting(true);

				//�G�t�F�N�g�̔j��
				if (m_pEffect != nullptr)
				{
					m_pEffect->Uninit();
					m_pEffect = nullptr;
				}	
			}
		}
	}

	//�I���̎��ԂɂȂ����玟�̃A�N�V����
	if (m_nChargeCount > END_TIME)
	{
		NextAction(enemy);
	}

	//�������Ă��������
	if (m_pBullet != nullptr)
	{
		if (m_pBullet->GetDeath())
		{
			m_pBullet = nullptr;
			NextAction(enemy);
		}
	}
}

//======================================================================
//�o�ꉉ�o
//======================================================================

//====================================
//�R���X�g���N�^
//====================================
CEnemyAction_Direction::CEnemyAction_Direction(CEnemy* enemy) :
	m_nCount(0)
{
	enemy->SetMotion(6);

	//�Q�[���V�[���ɉ��o��ݒ�
	CGame* pGame = nullptr;
	pGame = (CGame*)CManager::GetInstance()->GetScene();	//�Q�[���V�[���̎擾
	pGame->SetDirection(CDirection::DIRECTIONTYPE_BOSS);	//���o�̐ݒ�

	CEnemy002* pEnemy002 = (CEnemy002*)enemy;
	pEnemy002->SetMaterialized(true);
}

//====================================
//�A�N�V����(���o)
//====================================
void CEnemyAction_Direction::Action(CEnemy* enemy)
{
	//���o�̎��Ԃ��I�������s���J�n
	m_nCount++;

	if (m_nCount > DIRECTION_TIME)
	{
		NextAction(enemy);
	}
}

//======================================================================
//���g�U��
//======================================================================

//====================================
//�R���X�g���N�^
//====================================
CEnemyAction_AlterEgoAttack::CEnemyAction_AlterEgoAttack(CEnemy* enemy) :
	m_nCount(0),
	m_pShotAction(nullptr),
	m_bCreateAlterEgo(false),
	m_pAlterEgo()
{
	enemy->SetMotion(0);

	//���g�̃|�C���^��������
	for (int i = 0; i < NUM_ALTEREGO; i++)
	{
		m_pAlterEgo[i] = nullptr;
	}
}

//====================================
//�f�X�g���N�^
//====================================
CEnemyAction_AlterEgoAttack::~CEnemyAction_AlterEgoAttack()
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
void CEnemyAction_AlterEgoAttack::Action(CEnemy* enemy)
{
	//���[�J���ϐ�
	int nNumAlterEgo = 0;		//���݂̕��g�̐�

	m_nCount++;	//�J�E���g�A�b�v

	//���X�ɏ�����
	if (m_nCount <= TIME_INTERPOLATION_ALPHA)
	{
		//�p�[�c����������
		for (auto itr : enemy->GetModelPartsVector())
		{
			//�A���t�@�l�����Z���Đݒ�
			float fAlpha = itr->GetAlpha();
			fAlpha -= CEnemy002::VALUE_INVISIBLE_ALPHA / TIME_INTERPOLATION_ALPHA;
			
			//�␳
			if (fAlpha < 0.0f)
			{
				fAlpha = 0.0f;
			}

			itr->SetAlpha(fAlpha);
		}
	}

	//���X�Ɏp��\��
	else if (m_nCount > TIME_START_APPEAR && m_nCount <= TIME_START_APPEAR + TIME_INTERPOLATION_ALPHA)
	{
		//�ŏ��̈��ڂɕ��g�𐶐�
		if (!m_bCreateAlterEgo)
		{
			enemy->SetPos(enemy->GetStartPos());
			m_bCreateAlterEgo = true;

			//���g�𐶐�
			for (int i = 0; i < NUM_ALTEREGO; i++)
			{
				m_pAlterEgo[i] = CEnemy002_AlterEgo::Create(D3DXVECTOR3(sinf(((D3DX_PI * 2.0f) / NUM_ALTEREGO) * i) * 200.0f, 0.0f, cosf(((D3DX_PI * 2.0f) / NUM_ALTEREGO) * i) * 200.0f) + enemy->GetStartPos());
			}
		}

		//�p�[�c����������
		for (auto itr : enemy->GetModelPartsVector())
		{
			//�A���t�@�l�����Z���Đݒ�
			float fAlpha = itr->GetAlpha();
			fAlpha += CEnemy002::VALUE_INVISIBLE_ALPHA / TIME_INTERPOLATION_ALPHA;

			//�␳
			if (fAlpha > CEnemy002::VALUE_INVISIBLE_ALPHA)
			{
				fAlpha = CEnemy002::VALUE_INVISIBLE_ALPHA;
			}

			itr->SetAlpha(fAlpha);
		}
	}

	//���g����������Ă��Ȃ��Ȃ甲����
	if (!m_bCreateAlterEgo)
	{
		return;
	}

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
		m_pAlterEgo[i]->Update();
		nNumAlterEgo++;
	}

	//���g�����Ȃ��Ȃ�ڍs
	if (nNumAlterEgo == 0)
	{
		NextAction(enemy);
	}
}