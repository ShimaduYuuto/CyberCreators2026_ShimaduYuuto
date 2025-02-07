//================================
//
//gimmickmanager.cppに必要な宣言[gimmickmanager.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _GIMMICKMANAGER_H_ //このマクロ定義がされていなかったら
#define _GIMMICKMANAGER_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"
#include "gimmick.h"

//エネミーマネージャーのクラス
class CGimmickManager
{
public:

	//メンバ関数
	CGimmickManager();				//コンストラクタ
	~CGimmickManager();				//デストラクタ
	HRESULT Init();					//初期化
	void Uninit();					//終了
	void Regist(CGimmick* gimmick);	//登録
	void Erase(CGimmick* gimmick);	//削除

	//リストの取得
	std::list<CGimmick*> GetList() { return m_apManager; }

private:

	//メンバ変数
	std::list<CGimmick*> m_apManager;	//敵を管理
};

#endif