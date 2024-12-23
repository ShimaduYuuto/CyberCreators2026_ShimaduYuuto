//================================
//
//object2D.cppに必要な宣言[object2D.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _OBJECT2D_H_ //このマクロ定義がされていなかったら
#define _OBJECT2D_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "object.h"

//2Dオブジェクトクラス
class CObject2D : public CObject
{
public:
	//ポリゴンの構造体
	typedef struct
	{
		D3DXVECTOR3 move;	//移動量
		D3DXVECTOR3 rot;	//向き
		D3DXVECTOR3 size;	//サイズ
	}Polygon;

	//メンバ関数
	CObject2D(int nPriority = 3);			//コンストラクタ
	~CObject2D() override;					//デストラクタ
	HRESULT Init() override;				//初期化
	void Uninit() override;					//終了
	void Update() override;					//更新
	void Update(float max, float value);	//割合で更新
	virtual void Draw() override;			//描画
	void Draw(const char* texturepath);		//引数のテクスチャで描画
	static CObject2D* Create();				//Object2Dの生成

	//パラメータ関連
	void SetPos(D3DXVECTOR3 pos) override;						//位置の設定
	void SetRot(D3DXVECTOR3 rot);								//向きを設定
	D3DXVECTOR3& GetRot() { return m_polygon.rot; }				//向きを取得
	void SetSize(D3DXVECTOR3 size);								//サイズの設定
	D3DXVECTOR3& GetSize() { return m_polygon.size; }			//サイズの取得
	void SetMove(D3DXVECTOR3 move) { m_polygon.move = move; }	//移動量の設定
	D3DXVECTOR3& GetMove() { return m_polygon.move; }			//移動量の取得
	void SetColor(D3DXCOLOR color);								//頂点の色を設定
	void SetTextureUV(float u1, float u2, float v1, float v2);	//テクスチャの座標設定

private:

	void UpdateVertex();	//頂点情報に反映する

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファ
	Polygon m_polygon;							//ポリゴンの情報の構造体
};

#endif