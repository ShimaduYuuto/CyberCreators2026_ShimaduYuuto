//======================================
//
//	�e�̏���[enemybullet.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "enemybullet.h"
#include "manager.h"
#include "game.h"
#include "character.h"
#include "battleareamanager.h"
#include "state_bullet_normal.h"
#include "state_bullet_reflection.h"

const std::string CEnemyBullet::FILEPATH = "data\\MODEL\\enemybullet002.x";

//============================
//�R���X�g���N�^
//============================
CEnemyBullet::CEnemyBullet(int nPriority) : CObjectX(nPriority),
	m_Move(),					//�ړ���
	m_fSizeRate(1.0f),			//�T�C�Y�{��
	m_bReflection(false),		//���˔���
	m_bShooting(false),			//�����ꂽ���̔���
	m_pParentAction(nullptr),	//�e�̃A�N�V����
	m_pParentEnemy(nullptr),	//�e�̓G
	m_pState(nullptr)			//���
{
	//�Q�[���V�[���Ȃ画��
	if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
	{
		//�Q�[���V�[���̎擾
		CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

		//�}�l�[�W���[�ɓo�^
		pGame->GetEnemyBulletManager()->Regist(this);
	}

	//�����蔻��̐���
	if (m_Collision == nullptr)
	{
		m_Collision = CCollision::Create(COLLISION_RADIUS, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	//��Ԃ̏�����
	m_pState = new CState_Bullet_Normal(this);

	//�Q�[���^�O��ݒ�
	SetTag(CObject::TAG_GAME);
}

//============================
//�f�X�g���N�^
//============================
CEnemyBullet::~CEnemyBullet()
{
	//�Q�[���V�[���Ȃ画��
	if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
	{
		//�Q�[���V�[���̎擾
		CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

		//�}�l�[�W���[����폜
		pGame->GetEnemyBulletManager()->Erase(this);
	}

	//�����蔻��̏���
	if (m_Collision != nullptr)
	{
		m_Collision->Uninit();
		m_Collision = nullptr;
	}

	//�e�ɏ��������Ƃ�`����
	if (m_pParentAction != nullptr)
	{
		m_pParentAction->Erase(this);
		m_pParentAction = nullptr;
	}

	//��Ԃ̍폜
	SafeDelete(m_pState);
}

//============================
//������
//============================
HRESULT CEnemyBullet::Init()
{
	//������
	CObjectX::Init();

	return S_OK;
}

//============================
//�I������
//============================
void CEnemyBullet::Uninit()
{
	//������
	CObjectX::Uninit();

	//�e�ɏ��������Ƃ�`����
	if (m_pParentAction != nullptr)
	{
		m_pParentAction->Erase(this);
		m_pParentAction = nullptr;
	}
}

//============================
//�X�V
//============================
void CEnemyBullet::Update()
{
	//�ʒu�̍X�V
	UpdatePos();

	//�X�P�[���̐ݒ�
	SetScale({ m_fSizeRate, m_fSizeRate , m_fSizeRate });

	//�����蔻��̍X�V
	UpdateCollision();

	//������Ă��Ȃ��Ȃ甲����
	if (!m_bShooting)
	{
		return;
	}

	//��Ԃɉ����ď�����ύX
	if (m_pState != nullptr)
	{
		m_pState->CheckCollision(this);
	}

	//�q�b�g�m�F
	if (IsHitWall())
	{
		//�q�b�g���̏���
		HitProcess();
	}
}

//============================
//�ʒu�̍X�V
//============================
void CEnemyBullet::UpdatePos()
{
	//�ړ��ʂ̉��Z
	D3DXVECTOR3 Pos = GetPos();
	Pos += m_Move;
	SetPos(Pos);
}

//============================
//�����蔻��̍X�V
//============================
void CEnemyBullet::UpdateCollision()
{
	//null�`�F�b�N
	if (m_Collision != nullptr)
	{
		m_Collision->SetRadius(m_fSizeRate * COLLISION_RADIUS);	//���a��ݒ�
		m_Collision->Update(GetPos());							//�ʒu���X�V
	}
}

//============================
//�ǂɓ���������
//============================
bool CEnemyBullet::IsHitWall()
{
	return CBattleAreaManager::GetInstance()->GetCurrentBattleArea()->GetWall()->
		GetHit(m_Collision->GetPos(), m_Collision->GetRadius());
}

//============================
//�q�b�g���̏���
//============================
void CEnemyBullet::HitProcess()
{
	//�J�����̏���
	CManager::GetInstance()->GetCamera()->SetShake(CAMERA_SHAKE_FRAME, CAMERA_SHAKE_VALUE);	//�q�b�g���J������h�炷

	//�T�E���h����
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_BULLETHIT);

	//�I������
	Uninit();
}

//============================
//�`��
//============================
void CEnemyBullet::Draw()
{
	CObjectX::Draw(FILEPATH.c_str());
}

//============================
//�N���G�C�g
//============================
CEnemyBullet* CEnemyBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, CEnemyBehavior_ChargeShot* action, CEnemy* enemy)
{
	//��ނɉ����ē��I�m��
	CEnemyBullet* pEnemyBullet = NULL;

	//�N���G�C�g�̏���
	pEnemyBullet = new CEnemyBullet;

	//������
	pEnemyBullet->Init();

	//�p�����[�^�̐ݒ�
	pEnemyBullet->SetPos(pos);				//�ʒu
	pEnemyBullet->m_Move = move;			//�ړ���
	pEnemyBullet->m_pParentAction = action;	//�e�̃A�N�V����
	pEnemyBullet->m_pParentEnemy = enemy;	//�e�̓G

	//�ݒ肵������Ԃ�
	return pEnemyBullet;
}

//============================
//���ˏ���
//============================
void CEnemyBullet::Reflection(float angle)
{
	//���˂��Ă��Ȃ��Ȃ甽��
	if (!m_bReflection)
	{
		//�ړ��ʂ𔽓]
		m_bReflection = true;
		SafeDelete(m_pState);
		m_pState = new CState_Bullet_Reflection(this);

		//���ˊp�x�v�Z�p�̕ϐ�
		float fPlayerRot = angle;
		float fRot = atan2f(m_pParentEnemy->GetPos().x - GetPos().x, m_pParentEnemy->GetPos().z - GetPos().z);
		float fMin = fPlayerRot - D3DX_PI * 0.5f;
		float fMax = fPlayerRot + D3DX_PI * 0.5f;

		//��납��̍U���Ȃ�ʂ�
		if (fRot > fMin && fRot < fMax)
		{
			m_Move *= -1.0f;
		}
		else
		{
			m_Move = D3DXVECTOR3(sinf(angle + D3DX_PI) * REFLECTION_SPEED, 0.0f, cosf(angle + D3DX_PI) * REFLECTION_SPEED);
		}
	}
}