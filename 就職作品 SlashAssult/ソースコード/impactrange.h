//================================
//
//impactrange.cppに必要な宣言[impactrange.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _IMPACTRANGE_H_ //このマクロ定義がされていなかったら
#define _IMPACTRANGE_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "object3D.h"
#include "impactmesh.h"

//インパクトの範囲クラス
class CImpactRange : public CObject3D
{
public:

	//定数
	static const float MAX_SIZERATE;		//サイズ倍率の最大
	
	//メンバ関数
	CImpactRange(int nPriority = 3);				//コンストラクタ
	~CImpactRange() override;						//デストラクタ
	HRESULT Init() override;						//初期化
	void Uninit() override;							//終了
	void Update() override;							//更新
	void Draw() override;							//描画
	void Draw(const char* texturepath);				//引数のテクスチャで描画
	static CImpactRange* Create(D3DXVECTOR3 pos);	//衝撃の範囲の生成

private:
	CImpactMesh* m_pImpactMesh;	//インパクトメッシュのポインタ
};

#endif