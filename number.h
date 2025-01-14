//================================
//
//number.cppに必要な宣言[number.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _NUMBER_H_ //このマクロ定義がされていなかったら
#define _NUMBER_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "object2D.h"

//ナンバーのクラス
class CNumber : public CObject2D
{
public:

	//定数
	static const std::string TEXTUREPATH;	//読み込むファイル

	//メンバ関数
	CNumber(int nPriority = 5);								//コンストラクタ
	~CNumber() override;									//デストラクタ
	HRESULT Init() override;								//初期化
	void Uninit() override;									//終了
	void Update() override;									//更新
	void Draw() override;									//描画
	void SetTexture(int Num);								//テクスチャの設定
	static CNumber* Create(D3DXVECTOR3 pos, int number);	//ナンバーの生成

private:
};

#endif