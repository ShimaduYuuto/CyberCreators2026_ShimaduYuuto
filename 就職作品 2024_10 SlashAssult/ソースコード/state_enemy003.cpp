//================================
//
//�G�l�~�[003�̏�ԏ���[state_enemy003.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "state_enemy003.h"
#include "game.h"
#include "manager.h"

//===============================================
//�ʏ���
//===============================================

//====================================
//�M�~�b�N�Ƃ̓����蔻��
//====================================
void CState_Enemy003_Normal::UpdateGimmickCollison(CGame_Character* character)
{
	//�Q�[���V�[���̎擾
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//�e�M�~�b�N�Ƃ̓����蔻��
	for (auto& iter : pGame->GetGimmickManager()->GetList())
	{
		//�ʒu�̎擾
		D3DXVECTOR3 GimmickPos = iter->GetCollision()->GetPos();
		D3DXVECTOR3 EnemyPos = character->GetCollision()->GetPos();

		//�������v�Z
		float fLength = sqrtf((EnemyPos.x - GimmickPos.x) * (EnemyPos.x - GimmickPos.x) + (EnemyPos.z - GimmickPos.z) * (EnemyPos.z - GimmickPos.z));
		float fTotalRadius = iter->GetCollision()->GetRadius() + character->GetCollision()->GetRadius();

		//�͈͓��̊m�F
		if (fLength < fTotalRadius)
		{
			//�G�l�~�[003�ɃL���X�g(�_�E���L���X�g�Ȃ̂Ŕ���)
			CEnemy003* pEnemy003 = dynamic_cast<CEnemy003*>(character);

			//�U�����Ȃ�M�~�b�N���N��
			if (pEnemy003->GetAttacking())
			{
				iter->GimmickActivation();
			}
			else
			{
				//�M�̓�����Ȃ��ʒu�ɕ␳
				float fAngle = atan2f(GimmickPos.x - EnemyPos.x, GimmickPos.z - EnemyPos.z);//�Ίp���̊p�x���Z�o

				//�ʒu�̐ݒ�
				character->SetPos(D3DXVECTOR3(sinf(fAngle + D3DX_PI) * fTotalRadius + GimmickPos.x,
					character->GetPos().y,
					cosf(fAngle + D3DX_PI) * fTotalRadius + GimmickPos.z));
			}
		}
	}
}