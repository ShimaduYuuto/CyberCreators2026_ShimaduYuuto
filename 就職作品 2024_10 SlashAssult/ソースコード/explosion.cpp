//======================================
//
//	�����M�̏���[explosion.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "explosion.h"
#include "game.h"
#include "manager.h"

//�萔
const std::string CExplosion::FILEPATH = "data\\TEXTURE\\SmashMesh000.png";

//============================
//�R���X�g���N�^
//============================
CExplosion::CExplosion(int nPriority) : CObjectDome(nPriority),
	m_fLife(LIFE),
	m_pCollision(nullptr),
	m_fSizeRate(SIZE_STRAT_RATE)
{
	//�Q�[���V�[���̎擾
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//�}�l�[�W���[�ɓo�^
	pGame->GetExplosionManager()->Regist(this);

	//�Q�[���^�O��ݒ�
	SetTag(CObject::TAG_GAME);

	//�J������h�炷
	CManager::GetInstance()->GetCamera()->SetShake(30, 20);	//�q�b�g���J������h�炷
}

//============================
//�f�X�g���N�^
//============================
CExplosion::~CExplosion()
{
	//�Q�[���V�[���̎擾
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

	//�}�l�[�W���[����폜
	pGame->GetExplosionManager()->Erase(this);
}

//============================
//������
//============================
HRESULT CExplosion::Init()
{
	//������
	CObjectDome::Init();

	if (m_pCollision == nullptr)
	{
		m_pCollision = CCollision::Create(SIZE_RADIUS, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	
	//SE�̐ݒ�
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_EXPLOSION);

	return S_OK;
}

//============================
//�I������
//============================
void CExplosion::Uninit()
{
	//�����蔻��̔j��
	if (m_pCollision != nullptr)
	{
		m_pCollision->Uninit();
		m_pCollision = nullptr;
	}

	//�I������
	CObjectDome::Uninit();
}

//============================
//�X�V
//============================
void CExplosion::Update()
{
	//�T�C�Y�{���̍X�V
	UpdateSizeRate();

	//�{���̐ݒ�
	SetRate(m_fSizeRate);

	//�����̍X�V
	m_fLife--;

	if (m_fLife <= 0.0f)
	{
		Uninit();
		return;
	}

	//�Q�[���I�u�W�F�N�g�̋��ʏ����X�V
	CObjectDome::Update();

	//�����蔻��̍X�V
	m_pCollision->Update(GetPos());
}

//============================
//�T�C�Y�{���̍X�V
//============================
void CExplosion::UpdateSizeRate()
{
	//�{���𑝂₷��
	if (IsIncreaseSizeRate())
	{
		//�{���𑝉�
		m_fSizeRate += INCREASE_VALUE;

		//�ő�{�����̂ݓ����蔻����s��
		if (m_fSizeRate >= MAX_SIZE_VALUE)
		{
			//�ő�T�C�Y�ɕ␳
			m_fSizeRate = MAX_SIZE_VALUE;

			//�����蔻��̏���
			CollisionProcess();
		}
	}
	else if (IsDecreaseSizeRate())
	{
		//�{��������
		m_fSizeRate -= DECREASE_VALUE;

		//�ŏ��l�����������␳
		if (m_fSizeRate < MIN_SIZE_VALUE)
		{
			//�ŏ��T�C�Y�ɕ␳
			m_fSizeRate = MIN_SIZE_VALUE;
		}
	}
}

//============================
//�T�C�Y�{���𑝂₷��
//============================
bool CExplosion::IsIncreaseSizeRate()
{
	//����
	if (m_fLife <= INCREASE_RATE_LIFE) return false;	//���₷�������ԊO�Ȃ甲����
	if (m_fSizeRate >= MAX_SIZE_VALUE) return false;	//�ő�{���Ȃ甲����
	
	return true;
}

//============================
//�T�C�Y�{�������炷��
//============================
bool CExplosion::IsDecreaseSizeRate()
{
	//����
	if (m_fLife >= DECREASE_RATE_LIFE)return false;	//���炷�������ԊO�Ȃ甲����
	if (m_fSizeRate <= MIN_SIZE_VALUE) return false;//�ŏ��{���Ȃ甲����

	return true;
}

//============================
//�����蔻��̏���
//============================
void CExplosion::CollisionProcess()
{
	//�Q�[���V�[���̎擾
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//����̐���
	D3DXVECTOR3 ExplosionPos = GetPos();

	//�G�̎���
	for (auto& iter : pGame->GetEnemyManager()->GetList())
	{
		//�G�̈ʒu���擾
		D3DXVECTOR3 EnemyLength = iter->GetCollision()->GetPos() - ExplosionPos;

		float fXZ = sqrtf(EnemyLength.x * EnemyLength.x + EnemyLength.z * EnemyLength.z); //XZ�������Z�o����
		float fXY = sqrtf(EnemyLength.x * EnemyLength.x + EnemyLength.y * EnemyLength.y); //XY�������Z�o����
		float fLength = sqrtf(fXZ * fXZ + fXY * fXY);	//�������Z�o

		//�G�̔�����Ȃ�
		if (fLength < iter->GetCollision()->GetRadius() + m_pCollision->GetRadius())
		{
			//�p�x���Z�o
			float fAngleXZ = atan2f(EnemyLength.x, EnemyLength.z);
			float fAngleXY = atan2f(EnemyLength.x, EnemyLength.y);

			//������΂��Ȃ���_���[�W��^����
			iter->SetBlowDamage(DAMAGE_VALUE, fAngleXZ, BLOW_VALUE);
		}
	}
}

//============================
//�`��
//============================
void CExplosion::Draw()
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	
	//�J�����O���@��ύX
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	//�I�u�W�F�N�g�̕`��
	CObjectDome::Draw(FILEPATH.c_str());

	//�J�����O���@��ύX
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//============================
//�N���G�C�g
//============================
CExplosion* CExplosion::Create(D3DXVECTOR3 pos)
{
	//��ނɉ����ē��I�m��
	CExplosion* pExplosion = nullptr;

	//�N���G�C�g�̏���
	pExplosion = new CExplosion;

	//�p�����[�^�̐ݒ�
	pExplosion->SetPos(pos);			//�ʒu
	pExplosion->SetRadius(SIZE_RADIUS);	//���a
	pExplosion->SetRate(pExplosion->m_fSizeRate);

	//������
	pExplosion->Init();

	//�ݒ肵������Ԃ�
	return pExplosion;
}