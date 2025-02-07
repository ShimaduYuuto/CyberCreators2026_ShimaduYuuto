//================================
//
//state_player_guard.cppに必要な宣言[state_player_guard.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_PLAYER_GUARD_H_ //このマクロ定義がされていなかったら
#define _STATE_PLAYER_GUARD_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "state_player.h"
#include "effect_guard.h"

//ガードステートクラス
class CState_Player_Guard : public CState_Player
{
public:

	//定数
	static constexpr int TIME_STIFFNESS{ 40 };			//ガード時硬直の時間
	static constexpr float VALUE_ATTENUATION{ 0.1f };	//ノックバックの減衰率
	static constexpr float VALUE_KNOCKBACK{ 12.0f };	//ノックバックの値
	static constexpr int TIME_JUSTGUARD{ 1 };			//ジャストガードが発動するフレーム
	static constexpr int TIME_FIRST_STIFFNESS{ 20 };	//ガードの発動時の硬直フレーム

	//メンバ関数
	CState_Player_Guard(CPlayer* player);	//コンストラクタ
	~CState_Player_Guard() override;		//デストラクタ

	void UpdateState(CPlayer* player) override;				//状態の更新
	bool SetDamage(CPlayer* player, int damage, float angle) override;	//ダメージの設定

private:

	//行動の更新
	void UpdateBehavior(CPlayer* player) override;

	//硬直時の更新処理
	void UpdateStiffness(CPlayer* player);	//ガード時の硬直
	void UpdateFirstStiffness();			//発動時の硬直

	D3DXVECTOR3 KnockBackMove;	//ノックバックの移動量
	bool m_bStiffening;			//硬直中か
	int m_nStiffnessCount;		//硬直時のカウント
	int m_nFirstStiffnessCount;	//発動硬直時のカウント
	CEffect_Guard* m_pEffect;	//ガード中のエフェクト
	bool m_bJustGuard;			//ジャストガードをしたか
};

#endif