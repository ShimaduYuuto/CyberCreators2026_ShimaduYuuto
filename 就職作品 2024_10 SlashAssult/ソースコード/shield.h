//================================
//
//shield.cppに必要な宣言[shield.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _SHIELD_H_ //このマクロ定義がされていなかったら
#define _SHIELD_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "modelparts.h"

//シールドクラス
class CShield : public CModelparts
{
public:

	//メンバ関数
	CShield(int nPriority = 3);														//コンストラクタ
	~CShield() override;															//デストラクタ
	HRESULT Init() override;														//初期化
	void Uninit() override;															//終了
	void Update() override;															//更新
	void Draw() override;															//描画
	static CShield* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);						//盾の生成

private:
};

#endif