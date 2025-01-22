//================================
//
//objectbillboard.cppに必要な宣言[objectbillboard.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _OBJECTBILLBOARD_H_ //このマクロ定義がされていなかったら
#define _OBJECTBILLBOARD_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "object.h"

//ビルボードオブジェクトクラス
class CObjectBillboard : public CObject
{
public:
	//ポリゴンの構造体
	typedef struct
	{
		D3DXVECTOR3 move;	//移動量
		D3DXVECTOR3 size;	//サイズ
		float ratio;		//倍率
	}Polygon;

	//メンバ関数
	CObjectBillboard(int nPriority = 3);						//コンストラクタ
	~CObjectBillboard() override;								//デストラクタ
	HRESULT Init() override;									//初期化
	void Uninit() override;										//終了
	void Update() override;										//更新
	void Draw() override;										//描画
	virtual void Draw(const char* texturepath);					//引数のテクスチャで描画
	static CObjectBillboard* Create();							//ObjectBillboardの生成
	
	//パラメータ関連
	void SetSize(D3DXVECTOR3 size);								//サイズの設定
	D3DXVECTOR3& GetSize() { return m_polygon.size; }			//サイズの取得
	void SetMove(D3DXVECTOR3 move) { m_polygon.move = move; }	//移動量の設定
	D3DXVECTOR3& GetMove() { return m_polygon.move; }			//移動量の取得
	void SetRatio(float ratio);									//倍率の設定
	float& GetRatio() { return m_polygon.ratio; }				//倍率の取得
	void SetColor(D3DXCOLOR color);								//頂点の色を設定
	void SetTextureUV(float u1, float u2, float v1, float v2);	//テクスチャの座標設定

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファ
	Polygon m_polygon;							//ポリゴンの情報の構造体
	D3DXMATRIX m_mtxWorld;						//マトリックス
};

#endif