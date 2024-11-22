////================================
////
////arial.cppに必要な宣言[arial.h]
////Author:yuuto shimadu
//// 
////================================
//
//#ifndef _ARIAL_H_ //このマクロ定義がされていなかったら
//#define _ARIAL_H_ //２重インクルード防止のマクロ定義
//
////ヘッダーのインクルード
//#include "behavior_player.h"
//
////エリアルクラス
//class CArial : public CContinuousAttack
//{
//public:
//
//	//定数
//	static const int END_TIME = 40;			//終了までの時間
//	static const int START_COLLISION = 10;	//コリジョンの判定を始めるカウント
//
//	//メンバ関数
//	CArial();					//コンストラクタ
//	~CArial() override;			//デストラクタ
//
//	//キャンセルの処理
//	void Cancel() override;
//};
//
//#endif