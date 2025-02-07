//================================
//
//pause_select.cppに必要な宣言[pause_select.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _PAUSE_SELECT_H_ //このマクロ定義がされていなかったら
#define _PAUSE_SELECT_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "object2D.h"

//ポーズ選択クラス
class CPause_Select : public CObject2D
{
public:

	//選択肢の種類
	enum CHOICE
	{
		CHOICE_CONTINUE = 0,
		CHOICE_RESTART,
		CHOICE_TITLE,
		CHOICE_MAX
	};

	static const D3DXVECTOR3 SIZE;	//サイズ

	//メンバ関数
	CPause_Select(int nPriority = 6);	//コンストラクタ
	~CPause_Select() override;			//デストラクタ
	HRESULT Init() override;			//初期化
	void Uninit() override;				//終了
	void Update() override;				//更新
	void Draw() override;				//描画
	static CPause_Select* Create(CHOICE choice, D3DXVECTOR3 pos);	//生成

	virtual void Decision();			//決定時の処理
};

#endif