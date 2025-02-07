//================================
//
//lockonmark.cppに必要な宣言[lockonmark.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _LOOKONMARK_H_ //このマクロ定義がされていなかったら
#define _LOOKONMARK_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"
#include "objectbillboard.h"

//ロックオンマーククラス
class CLockonMark : public CObjectBillboard
{
public:

	//定数
	static const std::string TEXTUREPATH;		//テクスチャパス
	static constexpr float SIZE_MARK{ 30.0f };	//マークのサイズ

	//メンバ関数
	CLockonMark();				//コンストラクタ
	~CLockonMark()  override;	//デストラクタ
	HRESULT Init() override;		//初期化
	void Uninit() override;			//終了処理
	void Update() override;			//更新処理
	void Draw() override;			//描画処理

	//生成
	static CLockonMark* Create(float radius, D3DXVECTOR3* pos);	//コリジョンビューの生成

	//ロックオンの位置を取得
	D3DXVECTOR3 GetLockonPos() { return *m_Pos; }

private:
	float m_fRadius;			//半径
	D3DXVECTOR3* m_Pos;			//位置
};

#endif