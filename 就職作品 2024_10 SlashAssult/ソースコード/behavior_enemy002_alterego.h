//================================
//
//behavior_enemy002_alterego.cppに必要な宣言[behavior_enemy002_alterego.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BEHAVIOR_ENEMY002_ALTEREGO_H_ //このマクロ定義がされていなかったら
#define _BEHAVIOR_ENEMY002_ALTEREGO_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "behavior_enemy002.h"

//==========================
//チャージショット
//==========================
class CEnemyBehaviorAlterEgo_ChargeShot : public CEnemyBehavior_ChargeShot
{
public:

	//関数
	CEnemyBehaviorAlterEgo_ChargeShot(CEnemy* enemy) : CEnemyBehavior_ChargeShot(enemy){}	//コンストラクタ
	~CEnemyBehaviorAlterEgo_ChargeShot() {}												//デストラクタ
	void Action(CEnemy* enemy) override;												//行動
	void NextAction(CEnemy* enemy) override;											//待機アクションを設定

};

#endif