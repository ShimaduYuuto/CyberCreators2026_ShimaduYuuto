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
class CEnemyActionAlterEgo_ChargeShot : public CEnemyAction_ChargeShot
{
public:

	//関数
	CEnemyActionAlterEgo_ChargeShot(CEnemy* enemy) : CEnemyAction_ChargeShot(enemy){}	//コンストラクタ
	~CEnemyActionAlterEgo_ChargeShot() {}												//デストラクタ
	void Action(CEnemy* enemy) override;												//行動
	void NextAction(CEnemy* enemy) override;											//待機アクションを設定

};

#endif