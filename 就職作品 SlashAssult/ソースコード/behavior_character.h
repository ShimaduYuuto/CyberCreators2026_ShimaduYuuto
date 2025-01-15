//================================
//
//behavior_character.cppに必要な宣言[behavior_character.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BEHAVIOR_CHARACTER_H_ //このマクロ定義がされていなかったら
#define _BEHAVIOR_CHARACTER_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"
#include "character.h"

//==========================
//アクションストラテジー
//==========================
class CBaseAction
{
public:

	//コンストラクタとデストラクタ
	CBaseAction() : m_bEndAction(false), m_fActionCount(0.0f), m_fEndTime(0.0f) {}
	~CBaseAction() {}

	//アクション処理の基底
	virtual void Action(CCharacter* character) {};	

	//アクションの終了判定
	bool GetEndAction() { return m_bEndAction; }		//取得
	void SetEndAction(bool end) { m_bEndAction = end; }	//設定

	//カウント
	float GetActionCount() { return m_fActionCount; }			//取得
	void SetActionCount(float count) { m_fActionCount = count; }//設定

	//終了時間
	void SetEndTime(float time) { m_fEndTime = time; }	//設定
	float GetEndTime() { return m_fEndTime; }			//取得

	//パラメータの設定
	virtual void SetParam() {};

private:
	bool m_bEndAction;		//終了判定
	float m_fActionCount;	//カウント
	float m_fEndTime;		//終了時間
};

//==========================
//アタックストラテジー
//==========================
class CAttack : public CBaseAction
{
public:

	//コンストラクタ
	CAttack() : m_bHit(false), m_fCollisionTime(0.0f), m_fDamageValue(0) {}

	//攻撃処理
	void Action(CCharacter* character) override {};

	//判定の取得と設定
	void SetHit(bool hit) { m_bHit = hit; }	//設定
	bool GetHit() { return m_bHit; }		//取得

	//当たり判定発生時間の設定
	void SetCollisionTime(float time) { m_fCollisionTime = time; }	//設定
	float GetCollisionTime() { return m_fCollisionTime; }			//取得

	//与えるダメージ
	void SetDamageValue(int value) { m_fDamageValue = value; }		//設定
	int GetDamageValue() { return m_fDamageValue; }					//取得

private:
	bool m_bHit;			//当たったかの判定
	float m_fCollisionTime;	//当たり判定が発生する時間
	int m_fDamageValue;		//与えるダメージ
};

#endif