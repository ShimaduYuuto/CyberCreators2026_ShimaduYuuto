//================================
//
//sky.cppに必要な宣言[sky.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _SKY_H_ //このマクロ定義がされていなかったら
#define _SKY_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "objectdome.h"

//空クラス
class CSky : public CObjectDome
{
public:

	//定数
	static const std::string FILEPATH;
	static const D3DXVECTOR3 POS;			//位置
	static constexpr float RATE{ 50.0f };	//倍率
	static constexpr float RADIUS{ 100.0f };//半径

	//メンバ関数
	CSky(int nPriority = 3);			//コンストラクタ
	~CSky() override;					//デストラクタ
	HRESULT Init() override;				//初期化
	void Uninit() override;					//終了
	void Update() override;					//更新
	void Draw() override;					//描画
	static CSky* Create();					//空の生成

};

#endif