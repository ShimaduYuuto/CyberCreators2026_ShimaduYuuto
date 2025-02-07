//======================================
//
//	�ʏ��Ԃ̒e�̊Ǘ������鏈��[state_bullet_reflection.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "state_bullet_reflection.h"
#include "manager.h"
#include "game.h"

//============================
//�����蔻��̊m�F
//============================
void CState_Bullet_Reflection::CheckCollision(CEnemyBullet* bullet)
{
	//�Q�[���V�[���̎擾
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//�G�̎���
	for (auto& iter : pGame->GetEnemyManager()->GetList())
	{
		//����������
		bool bHit = false;

		//���łɓ������Ă������΂�
		if (bHit)
		{
			continue;
		}

		//�G�̈ʒu���擾
		D3DXVECTOR3 Length = iter->GetCollision()->GetPos() - bullet->GetCollision()->GetPos();

		float fXZ = sqrtf(Length.x * Length.x + Length.z * Length.z); //XZ�������Z�o����
		float fXY = sqrtf(Length.x * Length.x + Length.y * Length.y); //XY�������Z�o����
		float fLength = sqrtf(fXZ * fXZ + fXY * fXY);				//�������Z�o
		float fAngle = atan2f(bullet->GetMove().x, bullet->GetMove().z);				//�e�ƓG�̊p�x���Z�o

		//�G�̔�����Ȃ�
		if (fLength < iter->GetCollision()->GetRadius() + bullet->GetCollision()->GetRadius())
		{
			//�_���[�W����
			iter->ChangeStanState();
			iter->SetBlowDamage(CEnemyBullet::ENEMY_DAMAGE_VALUE, fAngle + D3DX_PI, CEnemyBullet::ENEMY_BROW_VALUE);

			//SE�̐ݒ�
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_BULLETHIT);

			CManager::GetInstance()->GetCamera()->SetShake(CEnemyBullet::CAMERA_SHAKE_FRAME, CEnemyBullet::CAMERA_SHAKE_VALUE);	//�q�b�g���J������h�炷

			bullet->Uninit();
			return;
		}
	}
}