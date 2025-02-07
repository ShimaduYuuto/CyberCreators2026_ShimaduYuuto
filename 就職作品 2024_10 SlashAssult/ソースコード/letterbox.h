//================================
//
//letterbox.cppに必要な宣言[letterbox.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _LETTERBOX_H_ //このマクロ定義がされていなかったら
#define _LETTERBOX_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"
#include "object2D.h"

//レターボックスクラス
class CLetterBox : public CObject
{
public:

	//定数
	static constexpr int NUM_LETTERBOX{ 2 };			//レターボックスの数
	static constexpr int TIME_INTERPOLATION{ 30 };		//補間の時間
	static constexpr float HEIGHT_LETTERBOX{ 100.0f };	//2Dオブジェクトの高さ

	//メンバ関数
	CLetterBox();					//コンストラクタ
	~CLetterBox();					//デストラクタ
	HRESULT Init() override;		//初期化
	void Uninit() override;			//終了
	void Update() override;			//更新
	void Draw() override;			//描画
	static CLetterBox* Create(int time);	//レターボックスの生成

private:

	//上下のレターボックス
	CObject2D* m_pLetterBox[NUM_LETTERBOX];	//2Dオブジェクト
	int m_nTime;							//寿命時間
	int m_nCurrentTime;						//現在の時間
};

#endif