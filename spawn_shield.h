////================================================================
////
////spawn_shield.cppに必要な宣言[spawn_shield.h]
////Author:yuuto shimadu
//// 
////=================================================================
//
//#ifndef _SPAWN_SHIELD_H_ //このマクロ定義がされていなかったら
//#define _SPAWN_SHIELD_H_ //２重インクルード防止のマクロ定義
//
////ヘッダーのインクルード
//#include "action_enemy001.h"
//
////シールドスポーンクラス(ストラテジーパターン)
//class CSpawn_Shield : public CAction_Enemy001
//{
//public:
//
//	//定数
//	static const int END_TIME = 100;	//終了までの時間
//	static const int SPAWN_TIME = 80;	//盾をスポーンさせる時間
//	
//	//メンバ関数
//	CSpawn_Shield();				//コンストラクタ
//	~CSpawn_Shield()  override;	//デストラクタ
//	HRESULT Init()  override;				//初期化
//	void Update()  override;				//更新
//
//private:
//	int m_nEndCount;	//終了カウント
//};
//
//#endif