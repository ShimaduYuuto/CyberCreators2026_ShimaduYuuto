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

//============================
//�G�l�~�[�̃R���X�g���N�^
//============================
CEnemy002_AlterEgo::CEnemy002_AlterEgo()
{
	//�G�̐������炷
	if (CBattleAreaManager::GetInstance()->GetCurrentBattleArea() != nullptr)
	{
		CBattleAreaManager::GetInstance()->GetCurrentBattleArea()->AddEnemyNum();
	}

	//�I�u�W�F�N�g�̎����X�V�͂��Ȃ�
	SetUpdateJudge(false);
}

//============================
//�G�l�~�[�̃f�X�g���N�^
//============================
CEnemy002_AlterEgo::~CEnemy002_AlterEgo()
{

}

//============================
//�G�l�~�[�̏�����
//============================
HRESULT CEnemy002_AlterEgo::Init()
{
	//������
	CEnemy::Init();

	//�p�����[�^�̏�����
	CCharacter::SetLife(LIFE);	//�̗�

	//���[�V�����̓ǂݍ���
	SetMotionInfo("data\\enemy012motion.txt");

	//�|�C���^�ɍs����ݒ�
	ChangeState(new CState_Enemy002_AlterEgo_Normal(this));

	return S_OK;
}

//============================
//�G�l�~�[�̏I������
//============================
void CEnemy002_AlterEgo::Uninit()
{
	//������
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
	CEnemy::Update();
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
CEnemy002_AlterEgo* CEnemy002_AlterEgo::Create(D3DXVECTOR3 pos)
{
	//����
	CEnemy002_AlterEgo* pEnemy = nullptr;
	pEnemy = new CEnemy002_AlterEgo;

	//�p�����[�^�̐ݒ�
	pEnemy->SetPos(pos);

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