////================================================================
////
////normalattack_enemy001.cppに必要な宣言[normalattack_enemy001.h]
////Author:yuuto shimadu
//// 
////=================================================================
//
//#ifndef _NORMALATTACK_ENEMY001_H_ //このマクロ定義がされていなかったら
//#define _NORMALATTACK_ENEMY001_H_ //２重インクルード防止のマクロ定義
//
////ヘッダーのインクルード
//#include "action_enemy001.h"
//
////ノーマルアタッククラス
//class CNormalAttack_Enemy001 : public CAction_Enemy001
//{
//public:
//
//	//定数
//	static const int END_TIME = 100;		//終了までの時間
//	static const float ATTACK_RANGE;		//攻撃の範囲
//	static const int START_COLLISION = 45;	//コリジョンの判定を始めるカウント
//	static const int DAMAGE_VALUE = 1;		//ダメージ量
//
//	//メンバ関数
//	CNormalAttack_Enemy001();				//コンストラクタ
//	~CNormalAttack_Enemy001()  override;	//デストラクタ
//	HRESULT Init()  override;				//初期化
//	void Update()  override;				//更新
//
//private:
//	float m_fEndCount;	//終了カウント
//	bool m_bHit;		//当たったか
//};
//
//#endif