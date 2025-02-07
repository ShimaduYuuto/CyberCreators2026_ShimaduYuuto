//================================
//
//ui_rushchance.cppに必要な宣言[ui_rushchance.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _UI_RUSHCHANCE_H_ //このマクロ定義がされていなかったら
#define _UI_RUSHCHANCE_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "objectbillboard.h"
#include "animation.h"

//ラッシュチャンスのUIクラス
class CUi_RushChance : public CObjectBillboard
{
public:

	//定数
	static const std::string TEXTURE_PATH;		//テクスチャパス
	static constexpr float RADIUS{ 70.0f };	//サイズ半径

	//テクスチャ情報
	static constexpr int HORIZONTAL{ 2 };	//横の分割数(U座標)
	static constexpr int VERTICAL{ 1 };		//縦の分割数(V座標)
	static constexpr int SPEED_UPDATE{ 20 };	//更新速度
	static constexpr bool LOOP{ true };	//ループ


	//メンバ関数
	CUi_RushChance(int nPriority = 4);			//コンストラクタ
	~CUi_RushChance() override;	//デストラクタ
	HRESULT Init() override;		//初期化
	void Uninit() override;			//終了
	void Update() override;			//更新
	void Draw() override;			//描画

	//生成
	static CUi_RushChance* Create(D3DXVECTOR3* pos);

private:
	CAnimation m_Anim;			//アニメーション用の情報
	D3DXVECTOR3* m_TargetPos;	//ターゲットの位置
};

#endif