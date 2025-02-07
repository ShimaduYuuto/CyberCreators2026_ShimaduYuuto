//================================
//
//state_bullet_reflection.cppに必要な宣言[state_bullet_reflection.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_BULLET_REFLECTION_H_ //このマクロ定義がされていなかったら
#define _STATE_BULLET_REFLECTION_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "state_bullet.h"

//弾の通常状態クラス
class CState_Bullet_Reflection : public CState_Bullet
{
public:

	//メンバ関数
	CState_Bullet_Reflection(CEnemyBullet* bullet) : CState_Bullet(bullet) {}	//コンストラクタ
	~CState_Bullet_Reflection() {}						//デストラクタ

	//当たり判定の確認
	void CheckCollision(CEnemyBullet* bullet) override;

};

#endif