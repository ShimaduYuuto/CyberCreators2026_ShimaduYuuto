//======================================
//
//	バトルエリアの処理[battlearea003.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "battlearea003.h"
#include "spawn_enemy.h"
#include "explodingbarrel.h"
#include "manager.h"
#include "game.h"
#include "direction.h"

//============================
//コンストラクタ
//============================
CBattleArea003::CBattleArea003()
{
	
}

//============================
//デストラクタ
//============================
CBattleArea003::~CBattleArea003()
{

}

//============================
//敵の生成
//============================
void CBattleArea003::SpawnEnemy()
{
	//敵生成
	CSpawn_Enemy::Create(GetPos(), CEnemy::ENEMYTYPE_ENEMY002);
}

//============================
//ギミックの生成
//============================
void CBattleArea003::SpawnGimmick()
{
	
}