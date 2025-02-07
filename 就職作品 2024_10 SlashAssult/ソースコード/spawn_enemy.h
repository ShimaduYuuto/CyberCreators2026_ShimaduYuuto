//================================
//
//spawn_enemy.cppに必要な宣言[spawn_enemy.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _SPAWN_ENEMY_H_ //このマクロ定義がされていなかったら
#define _SPAWN_ENEMY_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "object.h"
#include "enemy.h"
#include "particle_spawn.h"

//スポーンエネミークラス
class CSpawn_Enemy : public CObject
{
public:

	static constexpr int SPAWN_TIME{ 30 };

	//メンバ関数
	CSpawn_Enemy(int nPriority = 2);					//コンストラクタ
	~CSpawn_Enemy() override;							//デストラクタ
	HRESULT Init() override;							//初期化
	void Uninit() override;								//終了
	void Update() override;								//更新
	void Draw() override {};							//描画
	static CSpawn_Enemy* Create(D3DXVECTOR3 pos, CEnemy::ENEMYTYPE type);	//敵スポーンの生成

private:
	int m_nCount;						//カウント用
	CParticle_Spawn* m_pPaticleManager;	//パーティクルマネージャー
	CEnemy::ENEMYTYPE m_EnemyType;		//敵の種類
};

#endif