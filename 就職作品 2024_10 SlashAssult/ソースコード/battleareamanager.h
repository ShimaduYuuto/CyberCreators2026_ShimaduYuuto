//================================
//
//battleareamanager.cppに必要な宣言[battleareamanager.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BATTLEAREAMANAGER_H_ //このマクロ定義がされていなかったら
#define _BATTLEAREAMANAGER_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"
#include "battlearea.h"

//バトルエリアマネージャークラス
class CBattleAreaManager
{

private:

	//メンバ関数
	CBattleAreaManager();		//コンストラクタ

public:

	//メンバ関数
	~CBattleAreaManager();		//デストラクタ

	//インスタンスの生成
	static CBattleAreaManager* GetInstance()
	{
		static CBattleAreaManager instance;	//静的インスタンス
		return &instance;
	}

	//基本処理
	HRESULT Init();	//初期化
	void Uninit();	//終了処理
	void Update();	//更新

	//リスト関連
	void Regist(CBattleArea* area);	//登録
	void Erase(CBattleArea* area);	//削除

	//現在のバトルエリア
	void SetCurrentBattleArea(CBattleArea* area) { m_pCurrentBattleArea = area; }	//設定
	CBattleArea* GetCurrentBattleArea() { return m_pCurrentBattleArea; }			//取得

private:

	//読み込み
	void Load();
	void LoadBattleArea(std::ifstream& File);

	//リスト
	std::list<CBattleArea*> m_BattleAreaList;	//バトルエリアのリスト
	CBattleArea* m_pCurrentBattleArea;			//現在のバトルエリア			
	
};

#endif