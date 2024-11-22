////================================
////
////action_enemy.cppに必要な宣言[action_enemy.h]
////Author:yuuto shimadu
//// 
////================================
//
//#ifndef _ACTION_ENEMY_H_ //このマクロ定義がされていなかったら
//#define _ACTION_ENEMY_H_ //２重インクルード防止のマクロ定義
//
////ヘッダーのインクルード
//#include "main.h"
//#include "action.h"
//#include "character.h"
//
////前方宣言
//class CEnemy;
//
////アクションクラス
//class CAction_Enemy : public CAction
//{
//public:
//
//	//メンバ関数
//	CAction_Enemy() : m_NextAction(nullptr) {}		//コンストラクタ
//	~CAction_Enemy() override {};					//デストラクタ
//	void Update(CEnemy* enemy);						//更新
//
//	//パラメーターの取得と設定
//	void SetNextAction(CAction_Enemy* next) { m_NextAction = next; }	//次のアクションの設定
//	CAction_Enemy* GetNextAction() { return m_NextAction; }				//次のアクションの取得
//
//private:
//
//	CAction_Enemy* m_NextAction;	//次のアクション
//};
//
//#endif