//================================
//
//direction_boss_destroy.cppに必要な宣言[direction_boss_destroy.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _DIRECTION_BOSS_DESTROY_H_ //このマクロ定義がされていなかったら
#define _DIRECTION_BOSS_DESTROY_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "direction.h"
#include "object2D.h"

//演出クラス
class CDirection_Boss_Destroy : public CDirection
{
public:

	//演出
	static constexpr int END_TIME{ 700 };	//終了時間

	//カメラ
	static const D3DXVECTOR3 CAMERA_POSV;				//カメラ注視点の位置
	static const D3DXVECTOR3 CAMERA_POSR;				//カメラ視点の位置
	static constexpr int START_SHAKE_FRAME{ 250 };		//揺らし始める時間
	static constexpr int SHAKE_FRAME{ END_TIME - START_SHAKE_FRAME };	//揺らす時間
	static constexpr float SHAKE_MAGNITUDE{ 40.0f };	//揺らす値
	static constexpr float PARTICLE_SPEED{ 10.0f };		//パーティクルの速度
	static constexpr float PARTICLE_SIZE{ 100.0f };		//パーティクルサイズ

	//ゲームを終了
	static constexpr int TIME_ENDGAME_FRAME{ 660 };		//ゲームを終える時間

	//演出フェード
	static constexpr int TIME_ENDFADE_FRAME{ START_SHAKE_FRAME + 200 };		//フェードアウトを終える時間

	//メンバ関数
	CDirection_Boss_Destroy();	//コンストラクタ
	~CDirection_Boss_Destroy();	//デストラクタ

	//基本処理
	HRESULT Init() override;	//初期化
	bool TimeUpdate() override;	//更新

private:

	//関数
	void CreateParticle();	//パーティクルの生成

	CObject2D* m_pDirectionFade;	//演出用のフェード
	float m_fFadeAlpfa;				//フェードのα値
};

#endif