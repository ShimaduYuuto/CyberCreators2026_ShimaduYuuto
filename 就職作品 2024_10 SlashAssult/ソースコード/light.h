//================================
//
//light.cppに必要な宣言[light.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _LIGHT_H_ //このマクロ定義がされていなかったら
#define _LIGHT_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"

//ライトクラス
class CLight
{
public:

	//定数
	static const int MAX_LIGHT = 3;		//ライトの最大数

	//メンバ関数
	CLight();							//コンストラクタ
	~CLight();							//デストラクタ
	HRESULT Init();						//初期化
	void Uninit();						//終了
	void Update();						//更新
private:

	//メンバ変数
	D3DLIGHT9 m_aLight[MAX_LIGHT];		//ライト構造体
};

#endif