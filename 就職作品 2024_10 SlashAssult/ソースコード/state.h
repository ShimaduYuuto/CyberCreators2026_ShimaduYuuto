//================================
//
//state.cppに必要な宣言[state.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_H_ //このマクロ定義がされていなかったら
#define _STATE_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"
#include "game_character.h"

//ステートクラス(ステートパターン)
class CState
{
public:

	//メンバ関数
	CState() : m_fEndTime(0.0f), m_fStateCount(0.0f) {};	//コンストラクタ
	virtual ~CState() {};					//デストラクタ

	//状態ごとの更新
	virtual void Motion(CGame_Character* character);		//モーション
	virtual void UpdateState() {};							//状態の更新

	//終了時間
	void SetEndTime(float time) { m_fEndTime = time; }	//設定
	float GetEndTime() { return m_fEndTime; }			//取得

	//状態カウント
	void SetStateCount(float count) { m_fStateCount = count; }	//設定
	float GetStateCount() { return m_fStateCount; }				//取得

	//ギミックの当たり判定の更新
	virtual void UpdateGimmickCollison(CGame_Character* character);

private:

	float m_fStateCount;	//状態カウント
	float m_fEndTime;		//終了時間
};

#endif