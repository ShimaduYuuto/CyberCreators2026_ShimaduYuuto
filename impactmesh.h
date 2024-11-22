//================================
//
//objectmesh.cppに必要な宣言[objectmesh.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _IMPACTMASH_H_ //このマクロ定義がされていなかったら
#define _IMPACTMASH_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "objectcylinder.h"

//インパクトメッシュクラス
class CImpactMesh : public CObjectCylinder
{
public:

	//定数の宣言
	static const std::string FILEPATH;	//読み込むファイル
	static const int NUM_CORNER;		//円柱の数
	static const float HEIGHT;			//高さ

	//メンバ関数
	CImpactMesh(int nPriority = 3);		//コンストラクタ
	~CImpactMesh() override;			//デストラクタ
	HRESULT Init() override;			//初期化
	void Uninit() override;				//終了
	void Update() override;				//更新
	void Draw() override;				//描画

	//生成
	static CImpactMesh* Create(D3DXVECTOR3 pos, float radius);	
};

#endif