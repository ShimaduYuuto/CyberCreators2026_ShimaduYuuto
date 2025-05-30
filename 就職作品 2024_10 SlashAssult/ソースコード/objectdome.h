//================================
//
//objectdome.cppに必要な宣言[objectdome.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _OBJECTDOME_H_ //このマクロ定義がされていなかったら
#define _OBJECTDOME_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "object.h"

//シリンダーオブジェクトクラス
class CObjectDome : public CObject
{
public:

	//定数の宣言
	static const int NUM_CORNER;		//角の数
	static const int NUM_VIRTICAL = 4;	//高さの数
	static const float HEIGHT;			//高さ

	//メンバ関数
	CObjectDome(int nPriority = 3);	//コンストラクタ
	~CObjectDome() override;		//デストラクタ
	HRESULT Init() override;			//初期化
	void Uninit() override;				//終了
	void Update() override;				//更新
	void Draw() override;				//描画
	void Draw(const char* path);		//描画

	static CObjectDome* Create(D3DXVECTOR3 pos, float radius);	//生成

	//ポリゴンに関する情報の設定と取得
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }		//向きを設定
	D3DXVECTOR3& GetRot() { return m_rot; }				//向きを取得
	void SetMtx(D3DXMATRIX mtx) { m_mtxWorld = mtx; }	//マトリックスの設定
	D3DXMATRIX& GetMtx() { return m_mtxWorld; }			//マトリックスの取得
	void SetRate(float rate) { m_fRate = rate; }		//倍率の設定
	void SetRadius(float radius) { m_fRadius = radius; }//半径の設定
	float& GetRadius() { return m_fRadius; }			//半径の取得

private:

	//メンバ変数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	//頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff = NULL;	//インデックスバッファへのポインタ
	D3DXMATRIX m_mtxWorld;						//マトリックス
	D3DXVECTOR3 m_rot;							//向き
	float m_fRadius;							//半径
	D3DXCOLOR m_Color;							//ポリゴンの色
	int m_nIndex;								//頂点番号の数
	int m_nVertex;								//頂点の数
	int m_nPolygon;								//ポリゴンの数(縮退を含む)
	float m_fRate;								//サイズ倍率
};

#endif