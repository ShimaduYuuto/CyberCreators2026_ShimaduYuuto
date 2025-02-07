//================================
//
//state_enemy_blow.cppに必要な宣言[state_enemy_blow.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_ENEMY_BLOW_H_ //このマクロ定義がされていなかったら
#define _STATE_ENEMY_BLOW_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "state_enemy.h"

//ブローステートクラス
class CState_Enemy_Blow : public CState_Enemy
{
public:

	//定数
	static constexpr float VALUE_BLOW = 10.0f;	//吹き飛ぶ値

	//メンバ関数
	CState_Enemy_Blow();					//コンストラクタ
	CState_Enemy_Blow(CEnemy* enemy);		//コンストラクタ
	~CState_Enemy_Blow() override {};		//デストラクタ

	//状態ごとの更新
	void UpdateState(CEnemy* enemy) override;	//状態の更新
};

#endif