////================================
////
////arial001.cppに必要な宣言[arial001.h]
////Author:yuuto shimadu
//// 
////================================
//
//#ifndef _ARIAL001_H_ //このマクロ定義がされていなかったら
//#define _ARIAL001_H_ //２重インクルード防止のマクロ定義
//
////ヘッダーのインクルード
//#include "arial.h"
//#include "enemy.h"
//
////エリアルクラス(2段目)
//class CArial001 : public CArial
//{
//public:
//
//	//定数
//	static const int END_TIME = 20;			//終了までの時間
//	static const int START_COLLISION = 5;	//コリジョンの判定を始めるカウント
//	static const int START_CANCELTIME = 10;	//キャンセルが始める時間
//
//	//メンバ関数
//	CArial001();				//コンストラクタ
//	~CArial001() override;		//デストラクタ
//	HRESULT Init() override;	//初期化
//	void Update() override;		//更新
//
//	//キャンセルの処理
//	void Cancel() override;
//};
//
//#endif