//================================
//
//cleartime.cppに必要な宣言[cleartime.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _CLEARTIME_H_ //このマクロ定義がされていなかったら
#define _CLEARTIME_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"
#include "number.h"

//クリアタイムのクラス
class CClearTime
{

private:
	//メンバ関数
	CClearTime();								//コンストラクタ

public:

	//定数
	static constexpr int TIME_NUM{6};			//タイムの桁数
	static constexpr float NUM_SPACE{50.0f};		//数字の隙間

	//インスタンスの生成
	static CClearTime* GetInstance()
	{
		static CClearTime instance;	//静的インスタンス
		return &instance;
	}

	~CClearTime();								//デストラクタ
	HRESULT Init();								//初期化
	void Uninit();								//終了
	void AddTime(float value);					//タイムの加算
	float GetTime() { return m_fTime; }			//タイムの取得
	void SetTime();								//タイムの設定
	void ResetTime();							//タイムの消去

	//位置
	void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; }	//設定

private:
	CNumber* m_pNumber[TIME_NUM];			//タイムの桁数だけ確保
	float m_fTime;							//現在のタイム
	D3DXVECTOR3 m_Pos;						//位置
};

#endif