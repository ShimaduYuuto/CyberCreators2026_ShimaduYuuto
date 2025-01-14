//================================
//
//explosionmanager.cppに必要な宣言[explosionmanager.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _EXPLOSIONMANAGER_H_ //このマクロ定義がされていなかったら
#define _EXPLOSIONMANAGER_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"
#include "explosion.h"

//エネミーマネージャーのクラス
class CExplosionManager
{
public:

	//メンバ関数
	CExplosionManager();		//コンストラクタ
	~CExplosionManager();		//デストラクタ
	HRESULT Init();				//初期化
	void Uninit();				//終了
	void Regist(CExplosion* explosion);	//登録
	void Erase(CExplosion* explosion);	//削除

	//リストの取得
	std::list<CExplosion*> GetList() { return m_apManager; }

private:

	//メンバ変数
	std::list<CExplosion*> m_apManager;	//爆発を管理
};

#endif