////================================
////
////action_enemy000.cppに必要な宣言[action_enemy000.h]
////Author:yuuto shimadu
//// 
////================================
//
//#ifndef _ACTION_ENEMY000_H_ //このマクロ定義がされていなかったら
//#define _ACTION_ENEMY000_H_ //２重インクルード防止のマクロ定義
//
////ヘッダーのインクルード
//#include "main.h"
//#include "action.h"
//#include "character.h"
//
////アクションクラス
//class CAction_Enemy000 : public CAction
//{
//public:
//
//	//アクションの列挙型
//	typedef enum
//	{
//		ACTION_ENEMY000_NONE = 0,		//何もなし
//		ACTION_ENEMY000_NORMALATTACK,	//通常攻撃
//		ACTION_ENEMY000_MAX,			//列挙の最大
//	}ACTION_ENEMY000;
//
//	//メンバ関数
//	CAction_Enemy000();			//コンストラクタ
//	~CAction_Enemy000() override;	//デストラクタ
//	HRESULT Init() override;	//初期化
//	void Update() override;		//更新
//	static CAction_Enemy000* Create(ACTION_ENEMY000 action_enemy000, CCharacter* character);	//アクションの生成
//
//	//パラメーターの取得と設定
//	void SetNextAction(ACTION_ENEMY000 action) { m_NextAction = action; }	//次のアクションの設定
//	virtual void SetNextAction();										//次のアクションの設定
//	ACTION_ENEMY000 GetNextAction() { return m_NextAction; }				//次のアクションの取得
//	CCharacter* GetCharacter() { return m_pCharacter; }					//キャラクターの取得
//
//private:
//
//	ACTION_ENEMY000 m_NextAction;	//次のアクション
//	CCharacter* m_pCharacter;	//キャラクターのポインタ
//};
//
//#endif