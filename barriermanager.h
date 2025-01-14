//================================
//
//barriermanager.cppに必要な宣言[barriermanager.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BARRIERMANAGER_H_ //このマクロ定義がされていなかったら
#define _BARRIERMANAGER_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"
#include "barrier.h"

//バトルエリアマネージャークラス
class CBarrierManager
{
public:

	//メンバ関数
	CBarrierManager();		//コンストラクタ
	~CBarrierManager();		//デストラクタ

	//基本処理
	HRESULT Init();	//初期化
	void Uninit();	//終了処理
	void Update();	//更新

	//リスト関連
	void Regist(CBarrier* area);	//登録
	void Erase();					//削除
	std::list<CBarrier*> GetList() { return m_BarrierList; }	//取得

private:

	//読み込み
	void Load();

	//リスト
	std::list<CBarrier*> m_BarrierList;	//結界のリスト

};

#endif