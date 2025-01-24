//================================
//
//state_enemy_normal.cppに必要な宣言[state_enemy_normal.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_ENEMY_NORMAL_H_ //このマクロ定義がされていなかったら
#define _STATE_ENEMY_NORMAL_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "state_enemy.h"

//ノーマルステートクラス
class CState_Enemy_Normal : public CState_Enemy
{
public:

	//定数
	static const float MOVE_SPEED;		//移動量
	static const float GRAVITY_SPEED;	//重力の強さ
	static const float JUMP_SPEED;		//ジャンプの速度

	//メンバ関数
	CState_Enemy_Normal(CEnemy* enemy);		//コンストラクタ
	~CState_Enemy_Normal() override  {};	//デストラクタ

	//状態ごとの更新
	void UpdateState(CEnemy* enemy) override;	//状態の更新

	//状態ごとの更新
	void SetDamage(CEnemy* enemy, int damage) override { enemy->SetDamage(damage, enemy->GetRot().y); }	//ダメージの設定
};

#endif