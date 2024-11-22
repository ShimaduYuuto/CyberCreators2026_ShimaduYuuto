////================================
////
////action_player.cppに必要な宣言[action_player.h]
////Author:yuuto shimadu
//// 
////================================
//
//#ifndef _ACTION_PLAYER_H_ //このマクロ定義がされていなかったら
//#define _ACTION_PLAYER_H_ //２重インクルード防止のマクロ定義
//
////ヘッダーのインクルード
//#include "main.h"
//#include "action.h"
//#include "character.h"
//
////アクションクラス
//class CAction_Player : public CAction
//{
//public:
//
//	//メンバ関数
//	CAction_Player();			//コンストラクタ
//	~CAction_Player() override;	//デストラクタ
//	HRESULT Init() override;	//初期化
//	void Update() override;		//更新
//
//	//設定と取得
//	void SetNextAction(CAction_Player* next);								//次のアクションを設定
//	CAction_Player* GetNextAction() { return m_pNextAction; }				//次のアクションを取得
//	void SetCharacter(CCharacter* character) { m_pCharacter = character; }	//キャラクターの設定
//	CCharacter* GetCharacter() { return m_pCharacter; }						//キャラクターの取得
//
//private:
//	CAction_Player* m_pNextAction;	//次のアクション
//	CCharacter* m_pCharacter;		//キャラクターのポインタ
//};
//
//#endif