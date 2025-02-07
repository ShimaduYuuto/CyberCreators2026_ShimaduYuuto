//================================
//
//orbit.cppに必要な宣言[orbit.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _ORBIT_H_ //このマクロ定義がされていなかったら
#define _ORBIT_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "objectmesh.h"

//軌跡クラス
class COrbit : public CObjectMesh
{
public:

	//定数の宣言
	static const std::string TEXTUREPATH;		//テクスチャパス
	static const D3DXVECTOR3 BLOCK;				//ブロック数
	static const D3DXVECTOR3 SIZE;				//サイズ
	static const int NUM_ORBIT = 6;				//軌跡の数
	static const int NUM_VTX = NUM_ORBIT * 2;	//頂点の数

	//メンバ関数
	COrbit(int nPriority = 4);	//コンストラクタ
	~COrbit() override;			//デストラクタ
	HRESULT Init() override;		//初期化
	void Uninit() override;			//終了
	void Update() override;			//更新
	void Draw() override;			//描画

	//軌跡の設定
	void SetOrbit(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1);	//軌跡の位置を設定(原点, オフセット)

	static COrbit* Create();	//生成

private:
	//メンバ変数
	VERTEX_3D m_SaveVtx[NUM_VTX];	//頂点情報を保存する変数[頂点数]
	bool m_bFirstSet;				//初めての設定
};

#endif