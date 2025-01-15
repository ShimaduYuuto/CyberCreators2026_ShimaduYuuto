//================================
//
//model.cppに必要な宣言[model.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _MODEL_H_ //このマクロ定義がされていなかったら
#define _MODEL_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "objectX.h"

//モデルクラス
class CModel : public CObjectX
{
public:

	//モデルの種類
	typedef enum
	{
		MODEL_TYPE_NONE = 0,
		MODEL_TYPE_TREE,
		MODEL_TYPE_FENCE,
		MODEL_TYPE_VENUE,
		MODEL_TYPE_MAX
	}MODEL_TYPE;

	//メンバ関数
	CModel(int nPriority = 3) {};												//コンストラクタ
	~CModel() override {};														//デストラクタ
	static CModel* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL_TYPE type);	//モデルの生成
};

#endif