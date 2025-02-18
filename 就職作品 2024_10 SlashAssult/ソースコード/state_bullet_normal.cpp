//======================================
//
//	�ʏ��Ԃ̒e�̏���[state_bullet_normal.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "state_bullet_normal.h"
#include "manager.h"
#include "game.h"

//============================
//�����蔻��̊m�F
//============================
void CState_Bullet_Normal::CheckCollision(CEnemyBullet* bullet)
{
	//�Q�[���V�[���̎擾
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//�ϐ��錾
	D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetCollision()->GetPos();	//�v���C���[�̈ʒu

	//�������v�Z
	D3DXVECTOR3 Length = bullet->GetCollision()->GetPos() - PlayerPos;	//2�_�̍����Z�o
	float fLength = D3DXVec3Length(&Length);							//�������Z�o		
	float fAngle = atan2f(Length.x, Length.z);							//�p�x���Z�o

	//�U���͈͓̔��Ȃ�
	if (fLength < bullet->GetCollision()->GetRadius() + pGame->GetGamePlayer()->GetCollision()->GetRadius())
	{
		//�v���C���[�Ƀ_���[�W��^����
		if (pGame->GetGamePlayer()->SetDamage(1, fAngle))
		{
			//�q�b�g���̏���
			bullet->HitProcess();
		}
	}
}