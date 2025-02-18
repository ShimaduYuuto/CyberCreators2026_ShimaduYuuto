//======================================
//
//	通常状態の弾の処理[state_bullet_normal.cpp]
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
	D3DXVECTOR3 Length = bullet->GetCollision()->GetPos() - PlayerPos;	//2点の差を算出
	float fLength = D3DXVec3Length(&Length);							//距離を算出		
	float fAngle = atan2f(Length.x, Length.z);							//角度を算出

	//攻撃の範囲内なら
	if (fLength < bullet->GetCollision()->GetRadius() + pGame->GetGamePlayer()->GetCollision()->GetRadius())
	{
		//プレイヤーにダメージを与える
		if (pGame->GetGamePlayer()->SetDamage(1, fAngle))
		{
			//ヒット時の処理
			bullet->HitProcess();
		}
	}
}