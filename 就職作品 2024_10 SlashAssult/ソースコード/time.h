//================================
//
//time.cppに必要な宣言[time.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _TIME_H_ //このマクロ定義がされていなかったら
#define _TIME_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"

//時間のクラス
class CTime
{
public:

	//定数の初期化
	static const float SLOWRATE;	//スロウ時の倍率

	//時間の列挙型
	typedef enum
	{
		TIME_NORMAL = 0,	//通常の状態
		TIME_SLOW,			//遅くなっている状態
		TIME_MAX,			//列挙型の最大
	}TIME;

	//メンバ関数
	CTime();										//コンストラクタ
	~CTime();										//デストラクタ
	HRESULT Init();									//初期化
	void Update();									//更新
	void SetTimeState(TIME state);					//時間の状態を設定
	TIME GetTimeState() { return m_TimeState; }		//時間の状態を取得
	void SetTimer(int time);						//タイマーの設定
	void SetStateTimer(TIME state, int time);		//状態のタイマーを設定
	bool GetEndTimer() { return m_bEndTimer; }		//タイマーの終了判定

	//テンプレート
	template <typename T>T GetValue(const T value)
	{
		//変数に値を代入
		T Value = value;

		//時間がスロー状態なら値を変化
		if (m_TimeState == TIME_SLOW)
		{
			Value = value * SLOWRATE;
		}

		return Value;
	};	//世界の状態に応じて値を返す

private:
	TIME m_TimeState;			//時間の状態
	int m_nTimeCount;			//時間のカウント
	bool m_bEndTimer;			//タイマーの終了判定
};

#endif