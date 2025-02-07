//================================
//
//oldpaper.cppに必要な宣言[oldpaper.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _OLDPAPER_H_ //このマクロ定義がされていなかったら
#define _OLDPAPER_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "object2D.h"

//古い紙のUIクラス
class COldPaper : public CObject2D
{
public:

	//定数
	static const std::string TEXTUREPATH;	//読み込むパス
	static const D3DXVECTOR3 POS;			//位置
	static const D3DXVECTOR3 SIZE;			//サイズ

	//メンバ関数
	COldPaper(int nPriority = 3);	//コンストラクタ
	~COldPaper() override;			//デストラクタ
	HRESULT Init() override;		//初期化
	void Uninit() override;			//終了
	void Update() override;			//更新
	void Draw() override;			//描画
	static COldPaper* Create();		//古い紙のUIを生成

private:
	
};

#endif