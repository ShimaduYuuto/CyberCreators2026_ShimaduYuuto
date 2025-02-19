//================================
//
//effect_justguard.cppに必要な宣言[effect_justguard.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _EFFECT_JUSTGUARD_H_ //このマクロ定義がされていなかったら
#define _EFFECT_JUSTGUARD_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "effect_billboard.h"

//ジャストガードエフェクトクラス
class CEffect_JustGuard : public CEffect_Billboard
{
public:

	//定数
	static const std::string TEXTURE_PATH;	//テクスチャパス
	static constexpr float RADIUS = 100.0f;	//サイズ半径

	//テクスチャ情報
	static constexpr int HORIZONTAL{ 10 };	//横の分割数(U座標)
	static constexpr int VERTICAL{ 2 };		//縦の分割数(V座標)
	static constexpr int SPEED_UPDATE{ 1 };	//更新速度
	static constexpr bool LOOP{ false };	//ループ


	//メンバ関数
	CEffect_JustGuard();			//コンストラクタ
	~CEffect_JustGuard() override;	//デストラクタ
	HRESULT Init() override;		//初期化
	void Uninit() override;			//終了
	void Update() override;			//更新
	void Draw() override;			//描画

	//生成
	static CEffect_JustGuard* Create(D3DXVECTOR3 pos);
};

#endif