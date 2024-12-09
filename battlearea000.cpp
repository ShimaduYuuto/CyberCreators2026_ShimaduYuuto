//======================================
//
//	バトルエリアの処理[battlearea000.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "battlearea000.h"
#include "spawn_enemy.h"
#include "explodingbarrel.h"

//============================
//コンストラクタ
//============================
CBattleArea000::CBattleArea000()
{

}

//============================
//デストラクタ
//============================
CBattleArea000::~CBattleArea000()
{
	
}

//============================
//敵の生成
//============================
void CBattleArea000::SpawnEnemy()
{
	//敵生成
	CSpawn_Enemy::Create(GetPos(), CEnemy::ENEMYTYPE_ENEMY001);
	//CSpawn_Enemy::Create(GetPos() + D3DXVECTOR3(150.0f, 0.0f, 150.0f), CEnemy::ENEMYTYPE_ENEMY000);
	//CSpawn_Enemy::Create(GetPos() + D3DXVECTOR3(-150.0f, 0.0f, -150.0f), CEnemy::ENEMYTYPE_ENEMY000);
	//CSpawn_Enemy::Create(GetPos() + D3DXVECTOR3(-0.0f, 0.0f, -150.0f), CEnemy::ENEMYTYPE_ENEMY000);
	//CSpawn_Enemy::Create(GetPos() + D3DXVECTOR3(-150.0f, 0.0f, -300.0f), CEnemy::ENEMYTYPE_ENEMY000);
}

//============================
//ギミックの生成
//============================
void CBattleArea000::SpawnGimmick()
{
	//ギミック生成
	CExplodingBarrel::Create(GetPos(), { 0.0f, 0.0f, 0.0f });
	CExplodingBarrel::Create(GetPos() + D3DXVECTOR3(150.0f, 0.0f, 150.0f), { 0.0f, 0.0f, 0.0f });
}