//================================
//
//objectmesh.cppに必要な宣言[objectmesh.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _OBJECTMESH_H_ //このマクロ定義がされていなかったら
#define _OBJECTMESH_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "object.h"

//メッシュオブジェクトクラス
class CObjectMesh : public CObject
{
public:

	//定数の宣言
	static const std::string FILEPATH;	//読み込むファイル
	static const D3DXVECTOR3 BLOCK;		//ブロック数
	static const D3DXVECTOR3 SIZE;		//サイズ

	//メッシュの種類
	typedef enum
	{
		MESHTYPE_FIELD = 0,		//フィールド
		MESHTYPE_WALL,			//壁
		MESHTYPE_MAX,			//列挙の最大
	}MESHTYPE;

	//メンバ関数
	CObjectMesh(int nPriority = 3);						//コンストラクタ
	virtual ~CObjectMesh() override;					//デストラクタ
	virtual HRESULT Init() override;					//初期化
	HRESULT Init(int widthblock, int heightblock, float widthsize, float heightsize, MESHTYPE meshtype);	//引数付きの初期化
	virtual void Uninit() override;						//終了
	virtual void Update() override;						//更新
	virtual void Draw() override;						//描画
	virtual void Draw(const char* pfilepath);			//引数のテクスチャを描画
	
	static CObjectMesh* Create(D3DXVECTOR3 pos);		//Objectの生成

	//ポリゴンに関する情報の設定と取得
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }		//向きを設定
	D3DXVECTOR3& GetRot() { return m_rot; }				//向きを取得
	void SetMtx(D3DXMATRIX mtx) { m_mtxWorld = mtx; }	//マトリックスの設定
	D3DXMATRIX& GetMtx() { return m_mtxWorld; }			//マトリックスの取得

	//頂点に関する情報の設定
	void SetVtxPos(int index, D3DXVECTOR3 pos);		//頂点の位置設定
	void SetVtxColor(int index, D3DXCOLOR color);	//頂点の色設定
	void SetVtxTex(int index, D3DXVECTOR2 tex);		//頂点のUV設定
	void SetColor(D3DXCOLOR color);					//ポリゴンの色を設定

private:

	//メンバ関数
	void VtxPosCluculation(MESHTYPE meshtype);	//種類に応じて位置の計算結果を返す

	//メンバ変数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	//頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff = NULL;	//インデックスバッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture;				//テクスチャのポインタ
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