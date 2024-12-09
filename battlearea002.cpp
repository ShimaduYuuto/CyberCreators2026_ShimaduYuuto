//======================================
//
//	バトルエリアの処理[battlearea002.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "battlearea002.h"
#include "spawn_enemy.h"
#include "explodingbarrel.h"

//============================
//コンストラクタ
//============================
CBattleArea002::CBattleArea002()
{

}

//============================
//デストラクタ
//============================
CBattleArea002::~CBattleArea002()
{

}

//============================
//敵の生成
//============================
void CBattleArea002::SpawnEnemy()
{
	//敵生成
	CSpawn_Enemy::Create(GetPos(), CEnemy::ENEMYTYPE_ENEMY003);
	CSpawn_Enemy::Create(GetPos() + D3DXVECTOR3(150.0f, 0.0f, 150.0f), CEnemy::ENEMYTYPE_ENEMY003);
	CSpawn_Enemy::Create(GetPos() + D3DXVECTOR3(-150.0f, 0.0f, -150.0f), CEnemy::ENEMYTYPE_ENEMY003);
	CSpawn_Enemy::Create(GetPos() + D3DXVECTOR3(-0.0f, 0.0f, -150.0f), CEnemy::ENEMYTYPE_ENEMY003);
	CSpawn_Enemy::Create(GetPos() + D3DXVECTOR3(-150.0f, 0.0f, -300.0f), CEnemy::ENEMYTYPE_ENEMY003);
}

//============================
//ギミックの生成
//============================
void CBattleArea002::SpawnGimmick()
{
	//ギミック生成
	CExplodingBarrel::Create(GetPos(), { 0.0f, 0.0f, 0.0f });
	CExplodingBarrel::Create(GetPos() + D3DXVECTOR3(150.0f, 0.0f, 150.0f), { 0.0f, 0.0f, 0.0f });
}