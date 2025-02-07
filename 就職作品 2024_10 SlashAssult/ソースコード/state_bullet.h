//================================
//
//state_bullet.cppに必要な宣言[state_bullet.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_BULLET_H_ //このマクロ定義がされていなかったら
#define _STATE_BULLET_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "enemybullet.h"

//前方宣言
class CEnemyBullet;

//弾の状態クラス
class CState_Bullet
{
public:

	//メンバ関数
	CState_Bullet(CEnemyBullet* bullet) {};	//コンストラクタ
	~CState_Bullet() {}						//デストラクタ

	//当たり判定の確認
	virtual void CheckCollision(CEnemyBullet* bullet) {}

};

#endif