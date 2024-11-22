////================================
////
////normalattack.cppに必要な宣言[normalattack.h]
////Author:yuuto shimadu
//// 
////================================
//
//#ifndef _NORMALATTACK_H_ //このマクロ定義がされていなかったら
//#define _NORMALATTACK_H_ //２重インクルード防止のマクロ定義
//
////ヘッダーのインクルード
//#include "behavior_player.h"
//#include "enemy.h"
//
////ノーマルアタッククラス
////class CNormalAttack : public CContinuousAttack
////{
////public:
////
////	//定数
////	static const int END_TIME = 40;	//終了までの時間
////	static const int END_MOVE = 10;	//移動する時間
////	static const float VALUE_MOVE;	//移動量
////
////	//メンバ関数
////	CNormalAttack();			//コンストラクタ
////	~CNormalAttack()  override;	//デストラクタ
////	HRESULT Init()  override;	//初期化
////	void Update()  override;	//更新
////
////	//キャンセルの処理
////	void Cancel() override;
////};
//
//#endif