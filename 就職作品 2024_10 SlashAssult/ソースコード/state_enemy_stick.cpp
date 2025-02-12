//================================
//
//��Ԃɉ��������������s[state_enemy_stick.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "state_enemy_stick.h"
#include "state_enemy_normal.h"
#include "game.h"
#include "manager.h"

//====================================
//�R���X�g���N�^
//====================================
CState_Enemy_Stick::CState_Enemy_Stick(CEnemy* enemy)
{
	//�ݒ�
	SetAction(new CEnemyBehavior());									//��̍s��
	SetEndTime(END_TIME);												//�I������
	enemy->SetEnableGravity(false);										//�d�͂��󂯂Ȃ�
	enemy->SetBlowValue({ 0.0f, 0.0f, 0.0f });							//������ԗʂ𖳂���
	enemy->SetMove({ enemy->GetMove().x, 0.0f, enemy->GetMove().z });	//�ړ���
	enemy->SetEnteredStick(true);										//����t������ɂ���

	//�Q�[���̏���
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());	//�Q�[���V�[���̎擾
	pGame->SetLockon(true);														//���b�N�I����ݒ�
	pGame->GetLockon()->Regist(enemy);											//���b�N�I���Ώۂɓo�^

	//���ʉ�
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_STICK);
}

//====================================
//��ԍX�V����
//====================================
void CState_Enemy_Stick::UpdateState(CEnemy* enemy)
{
	//�����o�ϐ��̎擾
	float fEndTime{ GetEndTime() };	//�I������
	float fCount{ GetStateCount() };//�J�E���g�̎擾

	//�J�E���g�A�b�v
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());	//�Q�[���V�[���̎擾
	fCount += pGame->GetTime()->GetValue<float>(1.0f);							//���Ԃɉ����ăJ�E���g�A�b�v

	//�J�E���g������؂������Ԃ�؂�ւ���
	if (fCount >= fEndTime)
	{
		//���̏�Ԃ�ݒ�
		if (GetNextState() == nullptr)
		{
			//��Ԃ̃��Z�b�g
			enemy->StateReset();
			enemy->SetEnteredStick(false);
			pGame->GetLockon()->Erase(enemy);
		}
	}

	//�J�E���g�̐ݒ�
	SetStateCount(fCount);
}