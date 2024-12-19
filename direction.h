//================================
//
//direction.cppに必要な宣言[direction.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _DIRECTION_H_ //このマクロ定義がされていなかったら
#define _DIRECTION_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"
#include "letterbox.h"

//演出クラス
class CDirection
{
public:

	//演出の種類
	typedef enum
	{
		DIRECTIONTYPE_BOSS = 0,
		DIRECTIONTYPE_BOSS_DESTROY,
		DIRECTIONTYPE_MAX,
	}DIRECTIONTYPE;

	//メンバ関数
	CDirection();	//コンストラクタ
	~CDirection();	//デストラクタ

	//基本処理
	virtual HRESULT Init();		//初期化
	virtual bool TimeUpdate();	//更新

	//生成
	static CDirection* Create(DIRECTIONTYPE type);

	//終了時間
	void SetEndTime(int time);					//設定
	int GetEndTime() { return m_nEndTime; }		//取得

	//カウント
	int GetCount() { return m_nCount; }	//取得

private:

	//メンバ変数
	int m_nEndTime;				//終了時間
	int m_nCount;				//カウント
	CLetterBox* m_pLetterBox;	//レターボックス
};

#endif