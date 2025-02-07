//================================
//
//effect_hitattack.cppに必要な宣言[effect_hitattack.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _EFFECT_HITATTACK_H_ //このマクロ定義がされていなかったら
#define _EFFECT_HITATTACK_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "objectbillboard.h"
#include "animation.h"

//ヒットアタックエフェクトクラス
class CEffect_HitAttack : public CObjectBillboard
{
public:

	//定数
	static const std::string TEXTURE_PATH;	//テクスチャパス
	static constexpr float RADIUS = 150.0f;	//サイズ半径

	//テクスチャ情報
	static constexpr int HORIZONTAL{ 10 };	//横の分割数(U座標)
	static constexpr int VERTICAL{ 1 };		//縦の分割数(V座標)
	static constexpr int SPEED_UPDATE{ 2 };	//更新速度
	static constexpr bool LOOP{ false };	//ループ
	

	//メンバ関数
	CEffect_HitAttack();			//コンストラクタ
	~CEffect_HitAttack() override;	//デストラクタ
	HRESULT Init() override;		//初期化
	void Uninit() override;			//終了
	void Update() override;			//更新
	void Draw() override;			//描画

	//生成
	static CEffect_HitAttack* Create(D3DXVECTOR3 pos);

private:
	CAnimation m_Anim;	//アニメーション用の情報
};

#endif