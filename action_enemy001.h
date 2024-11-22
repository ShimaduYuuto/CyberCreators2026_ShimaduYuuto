////================================
////
////action_enemy001.cppに必要な宣言[action_enemy001.h]
////Author:yuuto shimadu
//// 
////================================
//
//#ifndef _ACTION_ENEMY001_H_ //このマクロ定義がされていなかったら
//#define _ACTION_ENEMY001_H_ //２重インクルード防止のマクロ定義
//
////ヘッダーのインクルード
//#include "main.h"
//#include "action.h"
//#include "character.h"
//
////アクションクラス
//class CAction_Enemy001 : public CAction
//{
//public:
//
//	//アクションの列挙型
//	typedef enum
//	{
//		ACTION_ENEMY001_NONE = 0,		//何もなし
//		ACTION_ENEMY001_SPAWN_SHIELD,	//盾のスポーン
//		ACTION_ENEMY001_ATTACK,			//攻撃
//		ACTION_ENEMY001_MAX,			//列挙の最大
//	}ACTION_ENEMY001;
//
//	//メンバ関数
//	CAction_Enemy001();			//コンストラクタ
//	~CAction_Enemy001() override;	//デストラクタ
//	HRESULT Init() override;	//初期化
//	void Update() override;		//更新
//	static CAction_Enemy001* Create(ACTION_ENEMY001 action_enemy001, CCharacter* character);	//アクションの生成
//
//	//パラメーターの取得と設定
//	void SetNextAction(ACTION_ENEMY001 action) { m_NextAction = action; }	//次のアクションの設定
//	virtual void SetNextAction();											//次のアクションの設定
//	ACTION_ENEMY001 GetNextAction() { return m_NextAction; }				//次のアクションの取得
//	ACTION_ENEMY001 GetNowAction() { return m_NowAction; }					//現在のアクションの取得
//	CCharacter* GetCharacter() { return m_pCharacter; }						//キャラクターの取得
//
//private:
//
//	ACTION_ENEMY001 m_NowAction;	//現在のアクション
//	ACTION_ENEMY001 m_NextAction;	//次のアクション
//	CCharacter* m_pCharacter;	//キャラクターのポインタ
//};
//
//#endif