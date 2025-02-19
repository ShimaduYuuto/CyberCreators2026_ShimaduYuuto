//================================
//
//effect_billboard.cppに必要な宣言[effect_billboard.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _EFFECT_BILLBOARD_H_ //このマクロ定義がされていなかったら
#define _EFFECT_BILLBOARD_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "objectbillboard.h"
#include "animation.h"

//ビルボードエフェクトクラス
class CEffect_Billboard : public CObjectBillboard
{
public:

	//メンバ関数
	CEffect_Billboard();			//コンストラクタ
	~CEffect_Billboard() override;	//デストラクタ
	void Update() override;			//更新

	//アニメクラス
	CAnimation& GetAnim() { return m_Anim; }	//取得

private:

	//変数
	CAnimation m_Anim;	//アニメーション用の情報
};

#endif