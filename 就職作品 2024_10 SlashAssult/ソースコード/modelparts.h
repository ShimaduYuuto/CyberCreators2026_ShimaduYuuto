//================================
//
//modelparts.cppに必要な宣言[modelparts.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _MODELPARTS_H_ //このマクロ定義がされていなかったら
#define _MODELPARTS_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "objectX.h"

//モデルパーツクラス
class CModelparts : public CObjectX
{
public:

	//メンバ関数
	CModelparts(int nPriority = 3);															//コンストラクタ
	virtual ~CModelparts() override;														//デストラクタ
	virtual HRESULT Init() override;														//初期化
	virtual void Uninit() override;															//終了
	virtual void Update() override;															//更新
	void Draw() override;																	//描画
	void Draw(int damagestate, int damagecount);											//ダメージ状態に応じて描画
	void SetParent(CModelparts* parent) { m_pParent = parent; }								//親の設定
	void SetFilePath(const char* filepath) { m_ModelPartsName = filepath; }					//ファイルパスの設定
	static CModelparts* Create(const char* filename, D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//モデルパーツの生成

	//ワールド座標の位置を取得
	D3DXVECTOR3 GetWorldPos();

	void SetAlpha(float alpha) { m_fAlpha = alpha; }	//設定
	float GetAlpha() { return m_fAlpha; }				//アルファ値

private:

	//メンバ変数
	CModelparts* m_pParent = nullptr;		//親モデルパーツへのポインタ
	std::string m_ModelPartsName;			//モデルのファイル名
	float m_fAlpha;							//透明度
};

#endif