//======================================
//
//	通常状態の弾の管理をする処理[state_bullet_normal.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "state_bullet_normal.h"
#include "manager.h"
#include "game.h"

//============================
//当たり判定の確認
//============================
void CState_Bullet_Normal::CheckCollision(CEnemyBullet* bullet)
{
	//ゲームシーンの取得
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//変数宣言
	D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetCollision()->GetPos();	//プレイヤーの位置

	//距離を計算
	D3DXVECTOR3 Length = bullet->GetCollision()->GetPos() - PlayerPos;
	float fLength = D3DXVec3Length(&Length);	//距離を算出
	D3DXVECTOR3 fDistance = PlayerPos - bullet->GetPos();
	float fAngle = atan2f(fDistance.x, fDistance.z);

	//攻撃の範囲内なら
	if (fLength < bullet->GetCollision()->GetRadius() + pGame->GetGamePlayer()->GetCollision()->GetRadius())
	{
		//プレイヤーにダメージを与える
		if (pGame->GetGamePlayer()->SetDamage(1, fAngle))
		{
			//SEの設定
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_BULLETHIT);	//ヒット音

			//カメラを揺らす
			CManager::GetInstance()->GetCamera()->SetShake(CEnemyBullet::CAMERA_SHAKE_FRAME, CEnemyBullet::CAMERA_SHAKE_VALUE);	//ヒット時カメラを揺らす

			//弾を消す
			bullet->Uninit();
		}
	}
}