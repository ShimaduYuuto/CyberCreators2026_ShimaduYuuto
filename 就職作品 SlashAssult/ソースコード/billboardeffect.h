//================================
//
//billboardeffect.cppに必要な宣言[billboardeffect.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BILLBOARDEFFECT_H_ //このマクロ定義がされていなかったら
#define _BILLBOARDEFFECT_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "objectbillboard.h"
#include "animation.h"

//ビルボードエフェクトクラス
class CBillboardEffect : public CObjectBillboard
{
public:
	//メンバ関数
	CBillboardEffect();				//コンストラクタ
	~CBillboardEffect()  override;	//デストラクタ
	HRESULT Init() override;		//初期化
	void Uninit() override;			//終了処理
	void Update() override;			//更新処理
	void Draw() override;			//描画処理

	
private:
	CAnimation m_Anim;
};

#endif