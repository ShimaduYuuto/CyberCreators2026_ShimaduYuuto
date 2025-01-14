//================================
//
//result_txtui.cppに必要な宣言[result_txtui.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _RESULT_TEXTUI_H_ //このマクロ定義がされていなかったら
#define _RESULT_TEXTUI_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "object2D.h"

//ゲージクラス
class CResult_Txtui : public CObject2D
{
public:

	//定数
	static const std::string TEXTUREPATH;	//読み込むパス
	static const D3DXVECTOR3 POS;			//位置
	static const D3DXVECTOR3 SIZE;			//サイズ

	//メンバ関数
	CResult_Txtui(int nPriority = 3);	//コンストラクタ
	~CResult_Txtui() override;		//デストラクタ
	HRESULT Init() override;		//初期化
	void Uninit() override;			//終了
	void Update() override;			//更新
	void Draw() override;			//描画
	static CResult_Txtui* Create();	//生成
};

#endif