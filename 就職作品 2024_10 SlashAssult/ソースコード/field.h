//================================
//
//field.cppに必要な宣言[field.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _FIELD_H_ //このマクロ定義がされていなかったら
#define _FIELD_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "object.h"

//フィールドクラス
class CField : public CObject
{
public:

	//定数の宣言
	static const std::string TEXTUREPATH;				//読み込むテクスチャ
	static const std::string FILEPATH;					//読み込むファイル
	static const D3DXVECTOR3 BLOCK;						//ブロック数
	static const D3DXVECTOR3 SIZE;						//サイズ
	static constexpr float COLLISION_WIDTH{ 1000.0f };	//当たり判定をする幅

	//メンバ関数
	CField(int nPriority = 0);					//コンストラクタ
	~CField() override;							//デストラクタ
	HRESULT Init() override;					//初期化
	void Uninit() override;						//終了
	void Update() override;						//更新
	void Draw() override;						//描画
	bool MeshCollision(D3DXVECTOR3& pos, D3DXVECTOR3& rot);	//メッシュに沿った当たり判定
	bool MeshCollision(D3DXVECTOR3& pos);					//メッシュの当たり判定
	D3DXVECTOR3 ConvertMeshPos(D3DXVECTOR3 pos);			//メッシュの位置に変換
	D3DXVECTOR3 WidthCollision(D3DXVECTOR3 pos);			//メッシュの横の当たり判定

	static CField* Create(D3DXVECTOR3 pos);		//フィールドの生成

private:

	//メンバ関数
	float MeshIPCluculation(D3DXVECTOR3 vec1, D3DXVECTOR3 vec2);
	void Load();	//読み込み

	//メンバ変数
	std::vector<D3DXVECTOR3> m_SurfaceNorVec;	//面法線ベクトル
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	//頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff = NULL;	//インデックスバッファへのポインタ
	D3DXMATRIX m_mtxWorld;						//マトリックス
	D3DXVECTOR3 m_rot;							//向き
	D3DXVECTOR3 m_block;						//ブロック数
	D3DXVECTOR3 m_size;							//サイズ
	D3DXCOLOR m_Color;							//ポリゴンの色
	int m_nIndex;								//頂点番号の数
	int m_nVertex;								//頂点の数
	int m_nPolygon;								//ポリゴンの数(縮退を含む)
};

#endif