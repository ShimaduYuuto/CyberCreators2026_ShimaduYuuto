////================================
////
////battlemanager.cppに必要な宣言[battlemanager.h]
////Author:yuuto shimadu
//// 
////================================
//
//#ifndef _BATTLEMANAGER_H_ //このマクロ定義がされていなかったら
//#define _BATTLEMANAGER_H_ //２重インクルード防止のマクロ定義
//
////ヘッダーのインクルード
//#include "main.h"
//#include "collision_wall.h"
//#include "enemy.h"
//#include "explodingbarrel.h"
//
////バトルマネージャーのクラス
//class CBattleManager
//{
//public:
//
//	//バトルステージ情報
//	struct BattleInfo
//	{
//		D3DXVECTOR3 StagePos;			//ステージ位置
//		float fRadius;					//ステージの半径
//		std::list<CEnemy*> EnemyList;	//敵のリスト
//	};
//
//	//メンバ関数
//	CBattleManager();			//コンストラクタ
//	~CBattleManager();			//デストラクタ
//	HRESULT Init();				//初期化
//	void Uninit();				//終了
//
//private:
//	std::list<BattleInfo*> a;
//};
//
//#endif