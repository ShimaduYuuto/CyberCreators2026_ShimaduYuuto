//================================
//
//dot.cppに必要な宣言[dot.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _DOT_H_ //このマクロ定義がされていなかったら
#define _DOT_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "object2D.h"

//ゲージクラス
class CDot : public CObject2D
{
public:

	//定数
	static const std::string TEXTURE_PATH;	//テクスチャパス

	//メンバ関数
	CDot(int nPriority = 3);	//コンストラクタ
	~CDot() override;			//デストラクタ
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画
	static CDot* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//ゲージの生成
};

#endif