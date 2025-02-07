//================================
//
//pause.cppに必要な宣言[pause.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _PAUSE_H_ //このマクロ定義がされていなかったら
#define _PAUSE_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"
#include "pause_select.h"
#include "pause_bg.h"

//ポーズクラス
class CPause
{
public:

	//メンバ関数
	CPause();					//コンストラクタ
	~CPause();					//デストラクタ
	HRESULT Init();				//初期化
	void Update();				//更新
	static CPause* Create();	//生成

private:

	int m_nSelect;		//選択番号
	CPause_Select* m_pPauseSelect[CPause_Select::CHOICE_MAX];
	CPause_Bg* m_pPauseBg;
};

#endif