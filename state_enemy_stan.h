//================================
//
//state_enemy_stan.cppに必要な宣言[state_enemy_stan.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_ENEMY_STAN_H_ //このマクロ定義がされていなかったら
#define _STATE_ENEMY_STAN_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "state_enemy.h"

//スタンステートクラス
class CState_Enemy_Stan : public CState_Enemy
{
public:

	//メンバ関数
	CState_Enemy_Stan();					//コンストラクタ
	CState_Enemy_Stan(CEnemy* enemy) {};	//コンストラクタ
	~CState_Enemy_Stan() override {};		//デストラクタ

	//状態ごとの更新
	void UpdateState(CEnemy* enemy) override;	//状態の更新
};

#endif