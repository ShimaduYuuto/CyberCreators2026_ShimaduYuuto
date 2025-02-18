//======================================
//
//	�G�l�~�[�̏���[enemy002_alterego.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "enemy002_alterego.h"
#include "state_enemy002_alterego.h"
#include "battleareamanager.h"

//�萔
const std::string CEnemy002_AlterEgo::FILEPATH = "data\\enemy012AlterEgomotion.txt";

//============================
//�G�l�~�[�̃R���X�g���N�^
//============================
CEnemy002_AlterEgo::CEnemy002_AlterEgo() :
	m_pMainEnemyBehavior(nullptr)
{
	//�G�̐������炷
	if (CBattleAreaManager::GetInstance()->GetCurrentBattleArea() != nullptr)
	{
		CBattleAreaManager::GetInstance()->GetCurrentBattleArea()->AddEnemyNum();
	}
}

//============================
//�G�l�~�[�̃f�X�g���N�^
//============================
CEnemy002_AlterEgo::~CEnemy002_AlterEgo()
{
	//�{�̂ɏ��������Ƃ�`����
	m_pMainEnemyBehavior->Erase(this);
}

//============================
//�G�l�~�[�̏�����
//============================
HRESULT CEnemy002_AlterEgo::Init()
{
	//������
	CEnemy::Init();

	//�p�����[�^�̏�����
	SetLife(LIFE);	//�̗�

	//���[�V�����̓ǂݍ���
	SetMotionInfo(FILEPATH.c_str());

	//�|�C���^�ɍs����ݒ�
	ChangeState(new CState_Enemy002_AlterEgo_Normal(this));

	//�����ɐݒ�
	SetMaterialized(false);

	return S_OK;
}

//============================
//�G�l�~�[�̏I������
//============================
void CEnemy002_AlterEgo::Uninit()
{
	//�I��
	CEnemy002::Uninit();
}

//============================
//�G�l�~�[�̍X�V
//============================
void CEnemy002_AlterEgo::Update()
{
	//���S�t���O�������Ă���Ȃ甲����
	if (GetDeath())
	{
		return;
	}

	//���ʏ����̍X�V
	CEnemy002::Update();
}

//============================
//�G�l�~�[�̕`��
//============================
void CEnemy002_AlterEgo::Draw()
{
	//�`��
	CCharacter::Draw();
}

//============================
//����
//============================
CEnemy002_AlterEgo* CEnemy002_AlterEgo::Create(D3DXVECTOR3 pos, CEnemyBehavior_AlterEgoAttack* action)
{
	//����
	CEnemy002_AlterEgo* pEnemy = nullptr;
	pEnemy = new CEnemy002_AlterEgo;

	//�p�����[�^�̐ݒ�
	pEnemy->SetPos(pos);
	pEnemy->m_pMainEnemyBehavior = action;

	//������
	pEnemy->Init();

	return pEnemy;
}

//============================
//��Ԃ̃��Z�b�g
//============================
void CEnemy002_AlterEgo::StateReset()
{
	//�ʏ�̏�Ԃɖ߂�
	ChangeState(new CState_Enemy002_Normal(this));
	SetEnableGravity(true);
	SetMaterialized(false);
}

//============================
//���S���̏���
//============================
void CEnemy002_AlterEgo::SetCharacterDeath()
{
	//�e�̎��S����
	CEnemy::SetCharacterDeath();
}