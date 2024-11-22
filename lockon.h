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

//ロックオンクラス
class CLockon
{
public:

	//メンバ関数
	CLockon();					//コンストラクタ
	~CLockon();					//デストラクタ
	HRESULT Init();				//初期化
	void Uninit();				//終了
	void Update();				//更新
	static CLockon* Create();	//生成

private:
	D3DXVECTOR3 m_TargetPos;	//ターゲットの位置
};

#endif