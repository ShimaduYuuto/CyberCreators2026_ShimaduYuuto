//================================
//
//objectX.cppに必要な宣言[objectX.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _OBJECTX_H_ //このマクロ定義がされていなかったら
#define _OBJECTX_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "object.h"

//Xオブジェクトクラス
class CObjectX : public CObject
{
public:

	//定数の宣言
	static const std::string FILEPATH;	//読み込むファイル

	//メンバ関数
	CObjectX(int nPriority = 3);								//コンストラクタ
	~CObjectX() override;										//デストラクタ
	HRESULT Init() override;									//初期化
	void Uninit() override;										//終了
	void Update() override;										//更新
	void Draw() override;										//描画
	virtual void Draw(const char* pfilepath);					//引数のモデルを描画
	static CObjectX* Create(D3DXVECTOR3 pos);					//ObjectXの生成

	//パラメーター関連
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }				//向きを設定
	D3DXVECTOR3& GetRot() { return m_rot; }						//向きを取得
	void SetMtx(D3DXMATRIX mtx) { m_mtxWorld = mtx; }			//マトリックスの設定
	D3DXMATRIX& GetMtx() { return m_mtxWorld; }					//マトリックスの取得
	void SetScale(D3DXVECTOR3 scale) { m_Scale = scale; }		//スケールの設定
	D3DXVECTOR3& GetScale() { return m_Scale; }					//スケールの取得

private:

	//メンバ変数
	D3DXMATRIX m_mtxWorld;			//マトリックス
	D3DXVECTOR3 m_Scale;			//スケール
	D3DXVECTOR3 m_rot;				//向き
};

#endif