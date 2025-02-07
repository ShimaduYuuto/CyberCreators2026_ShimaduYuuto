//================================
//
//guard_knockback.cppに必要な宣言[guard_knockback.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _GUARD_KNOCKBACK_H_ //このマクロ定義がされていなかったら
#define _GUARD_KNOCKBACK_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "player.h"

//ガードノックバッククラス
class CGuard_Knockback
{
public:

	//定数
	static constexpr int TIME_STIFFNESS{ 40 };			//ガード時硬直の時間
	static constexpr float VALUE_ATTENUATION{ 0.1f };	//ノックバックの減衰率
	static constexpr float VALUE_KNOCKBACK{ 12.0f };	//ノックバックの値
	static constexpr int TIME_FIRST_STIFFNESS{ 20 };	//ガードの発動時の硬直フレーム

	//メンバ関数
	CGuard_Knockback(float angle);	//コンストラクタ
	~CGuard_Knockback();			//デストラクタ

	//硬直が終わったかを取得
	bool GetEndStiffness() { return m_bStiffening; }

private:

	//行動の更新
	void Update(CPlayer* player);

	//硬直時の更新処理
	void UpdateStiffness(CPlayer* player);	//ガード時の硬直

	D3DXVECTOR3 KnockBackMove;	//ノックバックの移動量
	bool m_bStiffening;			//硬直中か
	int m_nStiffnessCount;		//硬直時のカウント
};

#endif