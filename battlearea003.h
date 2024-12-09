//================================
//
//battlearea003.cppに必要な宣言[battlearea003.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BATTLEAREA003_H_ //このマクロ定義がされていなかったら
#define _BATTLEAREA003_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "battlearea.h"

//バトルエリアのクラス
class CBattleArea003 : public CBattleArea
{
public:

	//メンバ関数
	CBattleArea003();			//コンストラクタ
	~CBattleArea003() override;	//デストラクタ

	//発生させる処理
	void SpawnEnemy() override;	//エネミー
	void SpawnGimmick() override;//ギミック
};

#endif