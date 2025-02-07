//================================
//
//title_logo.cppに必要な宣言[title_logo.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _TITLE_LOGO_H_ //このマクロ定義がされていなかったら
#define _TITLE_LOGO_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "object2D.h"

//titlelogoクラス
class CTitle_Logo : public CObject2D
{
public:

	//定数
	static const std::string TEXTURE_PATH;	//パス
	static constexpr float WIDTH{ 300.0f };	//横幅
	static constexpr float HEIGHT{ 150.0f };//高さ

	//メンバ関数
	CTitle_Logo(int nPriority = 3);	//コンストラクタ
	~CTitle_Logo() override;		//デストラクタ
	HRESULT Init() override;		//初期化
	void Uninit() override;			//終了
	void Update() override;			//更新
	void Draw() override;			//描画
	static CTitle_Logo* Create(D3DXVECTOR3 pos);	//生成
};

#endif