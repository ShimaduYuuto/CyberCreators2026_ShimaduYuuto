////================================
////
////smash.cppに必要な宣言[smash.h]
////Author:yuuto shimadu
//// 
////================================
//
//#ifndef _SMASH_H_ //このマクロ定義がされていなかったら
//#define _SMASH_H_ //２重インクルード防止のマクロ定義
//
////ヘッダーのインクルード
//#include "action_player.h"
//#include "impactrange.h"
//
////ノーマルアタッククラス
//class CSmash : public CAction_Player
//{
//public:
//
//	//定数
//	static const int DELAY_TIME = 20;	//遅延の時間
//	static const int ADD_SLOWTIME = 60;	//追加のスロー時間
//
//	//メンバ関数
//	CSmash();						//コンストラクタ
//	~CSmash()  override;			//デストラクタ
//	HRESULT Init()  override;		//初期化
//	void Update()  override;		//更新
//
//	//取得用
//	bool GetHit() { return m_bHit; }//当たり判定
//
//private:
//	CImpactRange* m_pImpact;	//スマッシュの範囲
//	bool m_bAttack;				//攻撃をしたか
//	bool m_bHit;				//攻撃が当たったか
//	int m_nDelayCount;			//遅らせる時間
//	int m_nSlowTime;			//スロウの時間
//};
//
//#endif