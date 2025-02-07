//================================
//
//effect_death_boss.cppに必要な宣言[effect_death_boss.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _EFFECT_DEATH_BOSS_H_ //このマクロ定義がされていなかったら
#define _EFFECT_DEATH_BOSS_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "objectbillboard.h"
#include "animation.h"

//死亡エフェクトクラス
class CEffect_Death_Boss : public CObjectBillboard
{
public:

	//定数
	static const std::string TEXTURE_PATH;	//テクスチャパス
	static constexpr float RADIUS{ 200.0f };	//サイズ半径

	//テクスチャ情報
	static constexpr int HORIZONTAL{ 10 };	//横の分割数(U座標)
	static constexpr int VERTICAL{ 7 };		//縦の分割数(V座標)
	static constexpr int SPEED_UPDATE{ 3 };	//更新速度
	static constexpr bool LOOP{ false };	//ループ

	//メンバ関数
	CEffect_Death_Boss();			//コンストラクタ
	~CEffect_Death_Boss() override;	//デストラクタ
	HRESULT Init() override;		//初期化
	void Uninit() override;			//終了
	void Update() override;			//更新
	void Draw() override;			//描画

	//生成
	static CEffect_Death_Boss* Create(D3DXVECTOR3* pos);

private:

	CAnimation m_Anim;				//アニメーション用の情報
	D3DXVECTOR3* m_TargetPos;		//対象の位置
};

#endif