//======================================
//
//	通常状態の弾の管理をする処理[state_bullet_reflection.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "state_bullet_reflection.h"
#include "manager.h"
#include "game.h"

//============================
//当たり判定の確認
//============================
void CState_Bullet_Reflection::CheckCollision(CEnemyBullet* bullet)
{
	//ゲームシーンの取得
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//敵の周回
	for (auto& iter : pGame->GetEnemyManager()->GetList())
	{
		//当たったか
		bool bHit = false;

		//すでに当たっていたら飛ばす
		if (bHit)
		{
			continue;
		}

		//敵の位置を取得
		D3DXVECTOR3 Length = iter->GetCollision()->GetPos() - bullet->GetCollision()->GetPos();

		float fXZ = sqrtf(Length.x * Length.x + Length.z * Length.z); //XZ距離を算出する
		float fXY = sqrtf(Length.x * Length.x + Length.y * Length.y); //XY距離を算出する
		float fLength = sqrtf(fXZ * fXZ + fXY * fXY);				//距離を算出
		float fAngle = atan2f(bullet->GetMove().x, bullet->GetMove().z);				//弾と敵の角度を算出

		//敵の判定内なら
		if (fLength < iter->GetCollision()->GetRadius() + bullet->GetCollision()->GetRadius())
		{
			//ダメージ処理
			iter->ChangeStanState();
			iter->SetBlowDamage(CEnemyBullet::ENEMY_DAMAGE_VALUE, fAngle + D3DX_PI, CEnemyBullet::ENEMY_BROW_VALUE);

			//SEの設定
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_BULLETHIT);

			CManager::GetInstance()->GetCamera()->SetShake(CEnemyBullet::CAMERA_SHAKE_FRAME, CEnemyBullet::CAMERA_SHAKE_VALUE);	//ヒット時カメラを揺らす

			bullet->Uninit();
			return;
		}
	}
}