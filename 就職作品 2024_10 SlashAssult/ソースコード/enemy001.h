//================================
//
//enemy001.cppに必要な宣言[enemy001.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _ENEMY001_H_ //このマクロ定義がされていなかったら
#define _ENEMY001_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "enemy.h"
#include "state_enemy001.h"
#include "shield.h"

//エネミークラス
class CEnemy001 : public CEnemy
{
public:

	//定数
	static const std::string FILEPATH;		//読み込むファイル
	static const float MOVE_VALUE;			//移動量
	static const float STARTATTACK_RANGE;	//攻撃を始める範囲
	static constexpr int LIFE{ 10 };		//体力

	//敵のモーション
	typedef enum
	{
		ENEMY001MOTION_NORMAL = 0,	//ニュートラル
		ENEMY001MOTION_WALK,		//移動
		ENEMY001MOTION_SHIELD_SPAWN,//シールドのスポーン
		ENEMY001MOTION_AIR,			//空中
		ENEMY001MOTION_DAMAGE,		//ダメージ
		ENEMY001MOTION_ATTACK,		//攻撃
		ENEMY001MOTION_MAX			//最大
	}ENEMY001MOTION;

	//メンバ関数
	CEnemy001();						//コンストラクタ
	~CEnemy001() override;				//デストラクタ
	HRESULT Init() override;			//初期化
	void Uninit() override;				//終了
	void Update() override;				//更新
	void Draw() override;				//描画

	//パラメータ関数
	bool SetDamage(int damage, float angle) override;	//ダメージの設定

	//状態処理の関数
	bool SetBlowOff() override;

	//ダメージの設定
	//bool SetDamage(int damage, float rotY) override;

	//状態のリセット
	void StateReset() override
	{
		//通常の状態に戻す
		ChangeState(new CState_Enemy001_Normal(this));
		SetEnableGravity(true);
	}

	//貼り付け状態に変更
	void ChangeStickState() override
	{
		ChangeState(new CState_Enemy001_Stick(this));
	}

	//ダメージを与えた際に与える影響
	void DamageEffect(CPlayer* player) override;

	//ダメージ判定
	void SetDamageJudge(bool judge) { 
		if (m_bDamageJudge && m_pShield == nullptr) { return; }
		m_bDamageJudge = judge; 
	}	//設定
	bool GetDamageJudge() { return m_bDamageJudge; }			//取得

	//盾を落とす
	void DropShield()
	{
		//盾を持っていたら
		if (m_pShield != nullptr)
		{
			m_pShield->Uninit();
			m_pShield = nullptr;
		}
	}

	//スタン状態に変更
	void ChangeStanState() override
	{
		ChangeState(new CState_Enemy001_Stan(this));
	}

private:

	CShield* m_pShield;	//盾のインスタンス
	bool m_bDamageJudge;//ダメージを受けるかの判定
};

#endif