//================================
//
//state_bullet_normal.cppに必要な宣言[state_bullet_normal.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_BULLET_NORMAL_H_ //このマクロ定義がされていなかったら
#define _STATE_BULLET_NORMAL_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "state_bullet.h"

//弾の通常状態クラス
class CState_Bullet_Normal : public CState_Bullet
{
public:

	//メンバ関数
	CState_Bullet_Normal(CEnemyBullet* bullet) : CState_Bullet(bullet){}	//コンストラクタ
	~CState_Bullet_Normal() {}						//デストラクタ

	//当たり判定の確認
	void CheckCollision(CEnemyBullet* bullet) override;

};

#endif