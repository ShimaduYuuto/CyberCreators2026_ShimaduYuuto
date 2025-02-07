//================================
//
//��Ԃɉ��������������s[state.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "state.h"
#include "game.h"
#include "manager.h"

//====================================
//���[�V�����̏���
//====================================
void CState::Motion(CGame_Character* character)
{
	//���[�V�����̍X�V
	character->UpdateMotion();
}

//====================================
//�M�~�b�N�Ƃ̓����蔻��
//====================================
void CState::UpdateGimmickCollison(CGame_Character* character)
{
	//�Q�[���V�[���̎擾
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//�e�M�~�b�N�Ƃ̓����蔻��
	for (auto& iter : pGame->GetGimmickManager()->GetList())
	{
		//�ʒu�̎擾
		D3DXVECTOR3 GimmickPos = iter->GetCollision()->GetPos();
		D3DXVECTOR3 CharacterPos = character->GetCollision()->GetPos();

		//�������v�Z
		float fLength = sqrtf((CharacterPos.x - GimmickPos.x) * (CharacterPos.x - GimmickPos.x) + (CharacterPos.z - GimmickPos.z) * (CharacterPos.z - GimmickPos.z));
		float fTotalRadius = iter->GetCollision()->GetRadius() + character->GetCollision()->GetRadius();
		float fHeightLength = CharacterPos.y - GimmickPos.y;

		//�����̋������Βl�ɕύX
		if (fHeightLength < 0.0f) { fHeightLength *= -1.0f; }

		//�͈͓��̊m�F
		if (fLength < fTotalRadius && fHeightLength < fTotalRadius)
		{
			//�M�̓�����Ȃ��ʒu�ɕ␳
			float fAngle = atan2f(GimmickPos.x - CharacterPos.x, GimmickPos.z - CharacterPos.z);//�Ίp���̊p�x���Z�o

			//�ʒu�̐ݒ�
			character->SetPos(D3DXVECTOR3(sinf(fAngle + D3DX_PI) * fTotalRadius + GimmickPos.x,
				character->GetPos().y,
				cosf(fAngle + D3DX_PI) * fTotalRadius + GimmickPos.z));
		}
	}
}