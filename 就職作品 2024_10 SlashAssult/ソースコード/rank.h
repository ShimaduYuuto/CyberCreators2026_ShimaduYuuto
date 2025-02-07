//================================
//
//rank.cppに必要な宣言[rank.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _RANK_H_ //このマクロ定義がされていなかったら
#define _RANK_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "object2D.h"

//ランクのUIクラス
class CRank : public CObject2D
{
public:

	//定数
	static const std::string TEXTUREPATH;			//読み込むパス
	static const D3DXVECTOR3 POS;					//位置
	static const D3DXVECTOR3 SIZE;					//サイズ
	static constexpr float TIME_RANKS{ 90.0f };		//Sランクの時間
	static constexpr float TIME_CARRYUP{ 20.0f };	//ランクが繰り上がる時間
	static constexpr int NUM_RANK{ 6 };				//ランクの数

	//メンバ関数
	CRank(int nPriority = 3);	//コンストラクタ
	~CRank() override;			//デストラクタ
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画
	static CRank* Create();		//ランクのUIを生成

private:

};

#endif