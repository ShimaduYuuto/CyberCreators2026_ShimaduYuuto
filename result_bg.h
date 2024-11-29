//================================
//
//result_bg.cppに必要な宣言[result_bg.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _RESULT_BG_H_ //このマクロ定義がされていなかったら
#define _RESULT_BG_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "object2D.h"

//ゲージクラス
class CResult_Bg : public CObject2D
{
public:

	//定数
	static const std::string TEXTURE_PATH;	//パス
	static constexpr float WIDTH{ 1280.0f };//横幅
	static constexpr float HEIGHT{ 720.0f };//高さ

	//メンバ関数
	CResult_Bg(int nPriority = 3);	//コンストラクタ
	~CResult_Bg() override;		//デストラクタ
	HRESULT Init() override;		//初期化
	void Uninit() override;			//終了
	void Update() override;			//更新
	void Draw() override;			//描画
	static CResult_Bg* Create();	//生成
};

#endif