//================================
//
//object3D.cppに必要な宣言[object3D.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _OBJECT3D_H_ //このマクロ定義がされていなかったら
#define _OBJECT3D_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "object.h"

//3Dオブジェクトクラス
class CObject3D : public CObject
{
public:

	//ポリゴンの種類
	typedef enum
	{
		TYPE_FLOOR = 0,	//床
		TYPE_WALL,		//壁
		TYPE_MAX,		//列挙の最大
	}TYPE;

	//ポリゴンの構造体
	typedef struct
	{
		D3DXVECTOR3 move;	//移動量
		D3DXVECTOR3 rot;	//向き
		D3DXVECTOR3 size;	//サイズ
		float fRate;		//サイズ倍率
	}Polygon;

	//メンバ関数
	CObject3D(int nPriority = 3);				//コンストラクタ
	~CObject3D() override;						//デストラクタ
	HRESULT Init() override;					//初期化
	void Uninit() override;						//終了
	void Update() override;						//更新
	void Draw() override;						//描画
	void Draw(const char* texturepath);			//引数のテクスチャを描画
	static CObject3D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);		//生成

	//パラメータ関連
	void SetRot(D3DXVECTOR3 rot) { m_polygon.rot = rot; }		//向きを設定
	D3DXVECTOR3& GetRot() { return m_polygon.rot; }				//向きを取得
	void SetSize(D3DXVECTOR3 size) { m_polygon.size = size; }	//サイズの設定
	void SetSize(D3DXVECTOR3 size, TYPE type);					//サイズの設定
	D3DXVECTOR3& GetSize() { return m_polygon.size; }			//サイズの取得
	void SetRate(float rate) { m_polygon.fRate = rate; }		//サイズ倍率の設定
	float& GetRate() { return m_polygon.fRate; }				//サイズ倍率の取得
	void SetMove(D3DXVECTOR3 move) { m_polygon.move = move; }	//移動量の設定
	D3DXVECTOR3& GetMove() { return m_polygon.move; }			//移動量の取得
	void SetMtx(D3DXMATRIX mtx) { m_mtxWorld = mtx; }			//マトリックスの設定
	D3DXMATRIX& GetMtx() { return m_mtxWorld; }					//マトリックスの取得
	void SetColor(D3DXCOLOR color);								//頂点の色を設定
	void SetTextureUV(float u1, float u2, float v1, float v2);	//テクスチャの座標設定

	//種類に応じて計算を変更
	void Calculation(D3DXVECTOR3 rot, TYPE type);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファ
	Polygon m_polygon;							//ポリゴンの情報の構造体
	D3DXMATRIX m_mtxWorld;						//マトリックス
};

#endif