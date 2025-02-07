//================================
//
//collision_view.cppに必要な宣言[collision_view.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _COLLISION_VIEW_H_ //このマクロ定義がされていなかったら
#define _COLLISION_VIEW_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"
#include "objectbillboard.h"

//コリジョンビュークラス
class CCollision_View  : public CObjectBillboard
{
public:

	//定数
	static const std::string TEXTURE_PATH;	//テクスチャパス

	//メンバ関数
	CCollision_View();				//コンストラクタ
	~CCollision_View()  override;	//デストラクタ
	HRESULT Init() override;		//初期化
	void Uninit() override;			//終了処理
	void Update() override;			//更新処理
	void Draw() override;			//描画処理

	//生成
	static CCollision_View* Create(float radius, D3DXVECTOR3* pos);	//コリジョンビューの生成

private:
	float m_fRadius;			//半径
	D3DXVECTOR3* m_Pos;			//位置
};

#endif