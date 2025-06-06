//================================
//
//state_enemy_normal.cppに必要な宣言[state_enemy_normal.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_ENEMY_DAMAGE_H_ //このマクロ定義がされていなかったら
#define _STATE_ENEMY_DAMAGE_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "state_enemy.h"

//ダメージステートクラス
class CState_Enemy_Damage : public CState_Enemy
{
public:

	//メンバ関数
	CState_Enemy_Damage(CEnemy* enemy);	//コンストラクタ
	~CState_Enemy_Damage() override {};		//デストラクタ

	//状態ごとの更新
	void UpdateState(CEnemy* enemy) override;	//状態の更新
};

#endif