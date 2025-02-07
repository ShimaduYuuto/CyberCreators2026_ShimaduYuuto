//================================
//
//��Ԃɉ��������������s[state_player_death.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "state_player_death.h"
#include "game.h"
#include "manager.h"
#include "state_player_normal.h"

//====================================
//�R���X�g���N�^
//====================================
CState_Player_Death::CState_Player_Death(CPlayer* player)
{
	//���S���[�V����
	player->SetMotion(CPlayer::PLAYERMOTION_DEATH);
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());
	pGame->SetGameOver(true);
}

//====================================
//��Ԃ̍X�V
//====================================
void CState_Player_Death::UpdateState(CPlayer* player)
{
	
}

//========================
//�_���[�W�̐ݒ�
//========================
bool CState_Player_Death::SetDamage(CPlayer* player, int damage, float angle)
{
	//�̗͂��Ȃ��Ȃ�X�V���Ȃ�
	if (player->GetLife() <= 0)
	{
		return false;
	}

	//���S�t���O�������Ă����甲����
	if (player->GetDeath())
	{
		return true;
	}

	return true;
}