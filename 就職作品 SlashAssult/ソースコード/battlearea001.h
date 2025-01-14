//================================
//
//battlearea001.cppに必要な宣言[battlearea001.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BATTLEAREA001_H_ //このマクロ定義がされていなかったら
#define _BATTLEAREA001_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "battlearea.h"

//バトルエリアのクラス
class CBattleArea001 : public CBattleArea
{
public:

	//メンバ関数
	CBattleArea001();			//コンストラクタ
	~CBattleArea001() override;	//デストラクタ

	//発生させる処理
	void SpawnEnemy() override;	//エネミー
	void SpawnGimmick() override;//ギミック
};

#endif