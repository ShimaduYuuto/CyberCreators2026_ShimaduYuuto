//================================
//
//lockon.cppに必要な宣言[lockon.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _LOCKON_H_ //このマクロ定義がされていなかったら
#define _LOCKON_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"
#include "lockonmark.h"
#include "enemy.h"
#include "ui_rushchance.h"

//ロックオンクラス
class CLockon
{
public:

	//印の半径
	static constexpr float MARK_RADIUS{ 30.0f };	//印の半径

	//メンバ関数
	CLockon();					//コンストラクタ
	~CLockon();					//デストラクタ
	HRESULT Init();				//初期化
	void Uninit();				//終了
	void Update();				//更新
	static CLockon* Create();	//生成
	void Regist(CEnemy* enemy);	//登録
	void Erase(CEnemy* enemy);	//削除

	//印
	CLockonMark* GetMark() { return m_pMark; }	//取得

	//ロックオン対象
	CEnemy* GetTarget() { return m_pTarget; }	//取得

private:
	CLockonMark* m_pMark;				//印
	CUi_RushChance* m_pRushUi;			//ラッシュのUI
	CEnemy* m_pTarget;					//ターゲットのポインタ
	std::list<CEnemy*> m_LockonList;	//ロックオンリスト
};

#endif