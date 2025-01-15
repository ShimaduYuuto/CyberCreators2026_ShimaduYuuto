//================================
//
//battlearea000.cppに必要な宣言[battlearea000.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BATTLEAREA000_H_ //このマクロ定義がされていなかったら
#define _BATTLEAREA000_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "battlearea.h"

//バトルエリアのクラス
class CBattleArea000 : public CBattleArea
{
public:

	//メンバ関数
	CBattleArea000();			//コンストラクタ
	~CBattleArea000() override;	//デストラクタ

	//発生させる処理
	void SpawnEnemy() override;	//エネミー
	void SpawnGimmick() override;//ギミック
};

#endif