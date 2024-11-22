////================================
////
////action.cppに必要な宣言[action.h]
////Author:yuuto shimadu
//// 
////================================
//
//#ifndef _ACTION_H_ //このマクロ定義がされていなかったら
//#define _ACTION_H_ //２重インクルード防止のマクロ定義
//
////ヘッダーのインクルード
//#include "main.h"
//
////アクションクラス(ストラテジーパターン)
//class CAction
//{
//public:
//
//	//メンバ関数
//	CAction();								//コンストラクタ
//	virtual ~CAction() = 0;					//デストラクタ
//	virtual HRESULT Init() = 0;				//初期化
//	virtual void Update() = 0;				//更新
//	
//	//取得と設定
//	bool GetEndAction() { return m_bEndAction; }		//アクションが終わったかの取得
//	void SetEndAction(bool end) { m_bEndAction = end; }	//アクションが終わったかの設定
//
//private:
//	bool m_bEndAction;		//アクションが終わったか
//};
//
//#endif