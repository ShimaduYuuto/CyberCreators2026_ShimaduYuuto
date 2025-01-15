//================================
//
//battlearea002.cppに必要な宣言[battlearea002.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BATTLEAREA002_H_ //このマクロ定義がされていなかったら
#define _BATTLEAREA002_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "battlearea.h"

//バトルエリアのクラス
class CBattleArea002 : public CBattleArea
{
public:

	//メンバ関数
	CBattleArea002();			//コンストラクタ
	~CBattleArea002() override;	//デストラクタ

	//発生させる処理
	void SpawnEnemy() override;	//エネミー
	void SpawnGimmick() override;//ギミック
};

#endif