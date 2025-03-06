//================================
//
//������я�ԏ��������s[state_enemy_blow.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "state_enemy_blow.h"
#include "state_enemy_normal.h"
#include "game.h"
#include "manager.h"
#include "battleareamanager.h"
#include "effect_brow.h"

//====================================
//�R���X�g���N�^
//====================================
CState_Enemy_Blow::CState_Enemy_Blow(CEnemy* enemy) : CState_Enemy(enemy)
{
	//�����A�N�V����
	SetAction(new CEnemyBehavior());

	//�ݒ�
	enemy->SetCollisionProcess(true);	//�����蔻��̏������s��
}

//====================================
//��ԍX�V����
//====================================
void CState_Enemy_Blow::UpdateState(CEnemy* enemy)
{
	//�Q�[���V�[���̎擾
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//�ǂɃq�b�g�������m�F
	CheckHitWall(enemy);

	//�e�M�~�b�N�Ƃ̓����蔻��
	for (auto& iter : pGame->GetGimmickManager()->GetList())
	{
		//�ʒu�̎擾
		D3DXVECTOR3 Pos = iter->GetCollision()->GetPos();
		D3DXVECTOR3 EnemyPos = enemy->GetCollision()->GetPos();

		//�������v�Z
		float fLength = sqrtf((EnemyPos.x - Pos.x) * (EnemyPos.x - Pos.x) + (EnemyPos.z - Pos.z) * (EnemyPos.z - Pos.z));

		//�͈͓��̊m�F
		if (fLength < iter->GetCollision()->GetRadius() + enemy->GetCollision()->GetRadius())
		{
			//�M�~�b�N�̍쓮
			iter->GimmickActivation();
		}
	}

	//�n�ʂɕt������ʏ��Ԃɂ���
	if (enemy->GetOnStand())
	{
		//���̏�Ԃ�ݒ�
		if (GetNextState() == nullptr)
		{
			//��Ԃ̐ݒ�
			enemy->StateReset();
			enemy->SetBlowValue({0.0f, 0.0f, 0.0f});
		}
	}
}

//====================================
//�ǂƂ̓����蔻����m�F
//====================================
void CState_Enemy_Blow::CheckHitWall(CEnemy* enemy)
{
	//�G���A�̊m�F
	if (CBattleAreaManager::GetInstance()->GetCurrentBattleArea() == nullptr) return;
	
	//�ǂɐG��Ă�����
	if (!CBattleAreaManager::GetInstance()->GetCurrentBattleArea()->GetWall()->GetHit(enemy->GetPos(), enemy->GetSizeRadius())) return;

	//�Q�[���V�[���̎擾
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//�A������Ȃ��Ȃ璣��t��
	if (!enemy->GetEnteredStick())
	{
		//����t����ԂɕύX
		enemy->ChangeStickState();

		//�J������h�炷
		CManager::GetInstance()->GetCamera()->SetShake(5, 15);	//�q�b�g���J������h�炷
	}
	else
	{
		//����
		enemy->SetBlowValue(enemy->GetBlowValue() * -1.0f);	//���΂ɐ�����΂��A����t�����͂���
		enemy->SetEnableGravity(true);						//�d�͂��󂯂�
		enemy->SetEnteredStick(false);						//����t���Ă��Ȃ���Ԃɂ���
		pGame->GetLockon()->Erase(enemy);					//���b�N�I���Ώۂ���폜
	}
}