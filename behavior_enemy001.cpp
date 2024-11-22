//================================
//
//敵の行動まとめ[behavior_enemy001.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "behavior_enemy001.h"
#include "enemy001.h"

//====================================
//コンストラクタ
//====================================
CEnemy001Attack::CEnemy001Attack()
{
	SetParam();
}

//====================================
//コンストラクタ(オーバーロード)
//====================================
CEnemy001Attack::CEnemy001Attack(CEnemy* enemy)
{
	//初期化
	enemy->SetMotion(CEnemy001::ENEMY001MOTION_ATTACK);
	SetParam();
}