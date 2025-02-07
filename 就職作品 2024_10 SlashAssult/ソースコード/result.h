//================================
//
//result.cppに必要な宣言[result.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _RESULT_H_ //このマクロ定義がされていなかったら
#define _RESULT_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "scene.h"
#include "field.h"

//リザルトクラス
class CResult : public CScene
{
public:

	//定数
	static const D3DXVECTOR3 TIME_POS;	//時間の位置

	//メンバ関数
	CResult();						//コンストラクタ
	~CResult() override;			//デストラクタ
	HRESULT Init() override;		//初期化
	void Uninit() override;			//終了
	void Update() override;			//更新
	void Draw() override;			//描画

	CField* GetField() { if (m_pField == nullptr) { return nullptr; } return m_pField; }						//フィールドの取得

private:
	CField* m_pField;					//フィールド
};

#endif