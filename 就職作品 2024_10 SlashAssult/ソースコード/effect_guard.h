//================================
//
//effect_guard.cppに必要な宣言[effect_guard.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _EFFECT_GUARD_H_ //このマクロ定義がされていなかったら
#define _EFFECT_GUARD_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "effect_billboard.h"

//ガードエフェクトクラス
class CEffect_Guard : public CEffect_Billboard
{
public:

	//定数
	static const std::string TEXTURE_PATH;	//テクスチャパス
	static constexpr float RADIUS{ 80.0f };	//サイズ半径
	static constexpr int TIME_INTERPOLATION_RATIO{ 10 };	//倍率を補間する時間

	//テクスチャ情報
	static constexpr int HORIZONTAL{ 13 };	//横の分割数(U座標)
	static constexpr int VERTICAL{ 2 };		//縦の分割数(V座標)
	static constexpr int SPEED_UPDATE{ 2 };	//更新速度
	static constexpr bool LOOP{ true };	//ループ

	//メンバ関数
	CEffect_Guard();			//コンストラクタ
	~CEffect_Guard() override;	//デストラクタ
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画

	//終了の設定
	void SetEnd() { m_bEnd = true; }

	//生成
	static CEffect_Guard* Create(D3DXVECTOR3* pos);

private:

	//関数
	void UpdateSizeRatio();	//サイズ倍率の更新

	//変数
	int m_nRatioInterpolationCount;	//倍率の補間カウント
	bool m_bEnd;					//終了するか
	D3DXVECTOR3* m_pTargetPos;		//対象の位置
	
};

#endif