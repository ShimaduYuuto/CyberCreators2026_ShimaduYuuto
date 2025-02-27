//================================
//
//colon.cppに必要な宣言[colon.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _COLON_H_ //このマクロ定義がされていなかったら
#define _COLON_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "object2D.h"

//コロンクラス
class CColon : public CObject2D
{
public:

	//定数
	static const std::string TEXTURE_PATH;	//テクスチャパス

	//メンバ関数
	CColon(int nPriority = 5);	//コンストラクタ
	~CColon() override;			//デストラクタ
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画
	static CColon* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	//生成
};

#endif