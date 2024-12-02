//================================
//
//behavior_Player.cppに必要な宣言[behavior_Player.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BEHAVIOR_PLAYER_H_ //このマクロ定義がされていなかったら
#define _BEHAVIOR_PLAYER_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "player.h"
#include "enemy.h"
#include "impactrange.h"

//プレイヤーの前方宣言
class CPlayer;

//==========================
//プレイヤーのストラテジー
//==========================
class CPlayerBehavior
{
public:

	//コンストラクタとデストラクタ
	CPlayerBehavior() : m_pNextBehavior(nullptr) {}
	CPlayerBehavior(CPlayer* player) : m_pNextBehavior(nullptr) {}
	virtual ~CPlayerBehavior() 
	{
		//メモリの破棄
		if (m_pNextBehavior != nullptr)
		{
			//delete m_pNextBehavior;
			m_pNextBehavior = nullptr;
		}
	}

	//行動の基底
	virtual void Behavior(CPlayer* player) {}

	//次のアクション
	void SetNextBehavior(CPlayerBehavior* behavior) { m_pNextBehavior = behavior; }
	CPlayerBehavior* GetNextBehavior() { return m_pNextBehavior; }

	//次のアクションを確定する
	virtual void NextAction(CPlayer* player) {}	//基底の関数

private:

	//次の行動
	CPlayerBehavior* m_pNextBehavior;
};

//==========================
//移動
//==========================
class CPlayerBehavior_Move : public CPlayerBehavior
{
public:

	//定数
	static constexpr float MOVE_SPEED{ 2.0f };		//移動量
	static constexpr float GRAVITY_SPEED{ 0.6f };	//重力の強さ
	static constexpr float JUMP_SPEED{ 14 };		//ジャンプの速度

	//メンバ関数
	CPlayerBehavior_Move() {}						//コンストラクタ
	CPlayerBehavior_Move(CPlayer* player);			//コンストラクタ

	//行動
	void Behavior(CPlayer* player) override;

private:

	//メンバ関数
	D3DXVECTOR3 UpdateMove(CPlayer* player, D3DXVECTOR3& Rotgoal);	//移動量の更新
	void Action(CPlayer* player);									//アクション処理
};

//==========================
//ダッシュ
//==========================
class CPlayerBehavior_Dash : public CPlayerBehavior
{
public:

	//定数
	static constexpr float DASH_SPEED{ 14.0f };		//ダッシュの速度
	static constexpr float STOP_LENGYH{ 50.0f };	//止まる距離

	//メンバ関数
	CPlayerBehavior_Dash() {}						//コンストラクタ
	CPlayerBehavior_Dash(CPlayer* player);			//コンストラクタ

	//行動
	void Behavior(CPlayer* player) override;
};

//==========================
//攻撃の基底
//==========================
class CPlayerBehavior_Attack : public CPlayerBehavior
{
public:
	//定数
	static constexpr int END_TIME{ 30 };				//終了までの時間
	static constexpr int START_COLLISION{ 10 };			//コリジョンの判定を始めるカウント
	static constexpr int START_CANCEL{ 15 };			//キャンセルが始める時間
	static constexpr float ATTACK_LENGTH{ 50.0f };		//攻撃の距離
	static const D3DXVECTOR3 POS_OFFSET;				//オフセット位置

	//メンバ関数
	CPlayerBehavior_Attack();						//コンストラクタ
	CPlayerBehavior_Attack(CPlayer* player);		//コンストラクタ
	~CPlayerBehavior_Attack() override
	{
		m_HitEnemy.clear();
	}		//デストラクタ

	//行動
	void Behavior(CPlayer* player) override;
	
	//パラメーターの設定
	void SetCancelTime(int time) { m_nCancelStartTime = time; }			//キャンセル時間の設定
	void SetEndTime(int time) { m_nEndTime = time; }					//終了時間の設定
	void SetCollisionTime(int time) { m_nCollisionlTime = time; }		//当たり判定出現時間
	void SetAttackLength(float length) { m_fAttackLength = length; }	//攻撃の距離の設定
	void SetOffsetPos(D3DXVECTOR3 pos) { m_OffsetPos = pos; }			//オフセット位置

	//キャンセルの処理
	virtual void Cancel(CPlayer* player) {}

	//カウント
	void SetCount(int count) { m_nEndCount = count; }	//設定
	int GetCount() { return m_nEndCount; }				//取得

private:

	//ダメージを与える
	virtual void Damage(CPlayer* player, CEnemy* enemy, int damage);

	int m_nEndCount;				//終了カウント
	std::list<CEnemy*> m_HitEnemy;	//当たった敵保存用
	int m_nCancelStartTime;			//キャンセル出来るカウント
	int m_nEndTime;					//終了時間
	int m_nCollisionlTime;			//当たり判定が出現する時間
	float m_fAttackLength;			//攻撃の距離
	D3DXVECTOR3 m_OffsetPos;		//オフセットの位置
};

//==========================
//通常攻撃
//==========================
class CPlayerBehavior_NormalAttack : public CPlayerBehavior_Attack
{
public:

	static const int END_TIME{ 40 };			//終了までの時間
	static const int END_MOVE{ 10 };			//移動する時間
	static constexpr float VALUE_MOVE{ 0.8f };	//移動量

	CPlayerBehavior_NormalAttack() {}	
	CPlayerBehavior_NormalAttack(CPlayer* player) 
	{
		SetEndTime(END_TIME);
	}		//コンストラクタ
	~CPlayerBehavior_NormalAttack() override {}				//デストラクタ

	//行動
	void Behavior(CPlayer* player) override;
};

//==========================
//通常攻撃(1段目)
//==========================
class CPlayerBehavior_NormalAttack000 : public CPlayerBehavior_NormalAttack
{
public:
	//メンバ関数
	CPlayerBehavior_NormalAttack000() {};					//コンストラクタ
	CPlayerBehavior_NormalAttack000(CPlayer* player);		//コンストラクタ
	~CPlayerBehavior_NormalAttack000() override {}			//デストラクタ

	//キャンセル時の処理
	void Cancel(CPlayer* player) override;

	//行動
	void Behavior(CPlayer* player) override
	{
		//通常攻撃
		CPlayerBehavior_NormalAttack::Behavior(player);
	};
};

//==========================
//通常攻撃(2段目)
//==========================
class CPlayerBehavior_NormalAttack001 : public CPlayerBehavior_NormalAttack
{
public:
	//メンバ関数
	CPlayerBehavior_NormalAttack001() {}						//コンストラクタ
	CPlayerBehavior_NormalAttack001(CPlayer* player);			//コンストラクタ
	~CPlayerBehavior_NormalAttack001() override {}				//デストラクタ

	//キャンセル時の処理
	void Cancel(CPlayer* player) override;

	//行動
	void Behavior(CPlayer* player) override
	{
		//通常攻撃
		CPlayerBehavior_NormalAttack::Behavior(player);
	};
};

//==========================
//通常攻撃(3段目)
//==========================
class CPlayerBehavior_NormalAttack002 : public CPlayerBehavior_NormalAttack
{
public:

	//定数
	static constexpr float MAX_RATE{ 200.0f };			//最大倍率
	static constexpr int ACCEPT_CANCELTIME{ 10 };		//キャンセルを受け付ける時間
	static constexpr float ACCELERATION_VALUE{ 0.03f };	//1フレームに加速度に加算する値

	//メンバ関数
	CPlayerBehavior_NormalAttack002() {};						//コンストラクタ
	CPlayerBehavior_NormalAttack002(CPlayer* player);			//コンストラクタ

	~CPlayerBehavior_NormalAttack002() override {}				//デストラクタ

	//行動
	void Behavior(CPlayer* player) override;
	
private:

	//ダメージを与える
	void Damage(CPlayer* player, CEnemy* enemy, int damage) override;

	//チャージに使う変数
	bool m_bChargeEnd;				//チャージが終わったか
	float m_fChargeRate;			//チャージの倍率
	int m_nCancelCount;				//キャンセルのカウント
	float m_fChargeAcceleration;	//チャージの加速度
};

//==========================
//空中攻撃
//==========================
class CPlayerBehavior_Arial : public CPlayerBehavior_Attack
{
public:

	//定数
	static constexpr int END_TIME{20};			//終了までの時間
	static constexpr int START_COLLISION{5};	//コリジョンの判定を始めるカウント
	static constexpr int START_CANCELTIME{10};	//キャンセルが始める時間

	CPlayerBehavior_Arial() {}
	CPlayerBehavior_Arial(CPlayer* player) 
	{
		//パラメータの設定
		SetCancelTime(START_CANCELTIME);	//キャンセル
		SetEndTime(END_TIME);				//終了時間
		SetCollisionTime(START_COLLISION);	//当たり判定
	}
	~CPlayerBehavior_Arial() override {}			//デストラクタ

	//行動
	void Behavior(CPlayer* player) override {};
};

//==========================
//空中攻撃(1段目)
//==========================
class CPlayerBehavior_Arial000 : public CPlayerBehavior_Arial
{
public:

	CPlayerBehavior_Arial000() {}
	CPlayerBehavior_Arial000(CPlayer* player);		//コンストラクタ
	~CPlayerBehavior_Arial000() override {}			//デストラクタ

	//行動
	void Behavior(CPlayer* player) override;

	//キャンセル時の処理
	void Cancel(CPlayer* player) override;
};

//==========================
//空中攻撃(2段目)
//==========================
class CPlayerBehavior_Arial001 : public CPlayerBehavior_Arial
{
public:

	CPlayerBehavior_Arial001() {}
	CPlayerBehavior_Arial001(CPlayer* player);		//コンストラクタ
	~CPlayerBehavior_Arial001() override {}			//デストラクタ

	//行動
	void Behavior(CPlayer* player) override;

	//キャンセル時の処理
	void Cancel(CPlayer* player) override;
};

//==========================
//空中攻撃(3段目)
//==========================
class CPlayerBehavior_Arial002 : public CPlayerBehavior_Arial
{
public:

	CPlayerBehavior_Arial002() {}
	CPlayerBehavior_Arial002(CPlayer* player);		//コンストラクタ
	~CPlayerBehavior_Arial002() override {}			//デストラクタ

	//行動
	void Behavior(CPlayer* player) override;
};

//==========================
//打ち上げ攻撃
//==========================
class CPlayerBehavior_Smash : public CPlayerBehavior
{
public:
	//定数
	static constexpr int DELAY_TIME{ 20 };		//遅延の時間
	static constexpr int ADD_SLOWTIME{ 60 };	//追加のスロー時間

	//メンバ関数
	CPlayerBehavior_Smash() :
		m_pImpact(nullptr),
		m_bAttack(false),
		m_bHit(false),
		m_nDelayCount(0),
		m_nSlowTime(0)
	{}						//コンストラクタ
	CPlayerBehavior_Smash(CPlayer* player);	//コンストラクタ
	~CPlayerBehavior_Smash()  override
	{
		//メモリの破棄
		if (m_pImpact != nullptr)
		{
			delete m_pImpact;
			m_pImpact = nullptr;
		}
	}			//デストラクタ

	//打ち上げ攻撃の行動
	void Behavior(CPlayer* player) override;
	
	//取得用
	bool GetHit() { return m_bHit; }//当たり判定

private:
	CImpactRange* m_pImpact;	//スマッシュの範囲
	bool m_bAttack;				//攻撃をしたか
	bool m_bHit;				//攻撃が当たったか
	int m_nDelayCount;			//遅らせる時間
	int m_nSlowTime;			//スロウの時間
};

//==========================
//ダッシュ攻撃
//==========================
class CPlayerBehavior_DashAttack : public CPlayerBehavior_Attack
{
public:

	//定数
	static constexpr int END_TIME{ 20 };			//終了までの時間
	static constexpr int START_COLLISION{ 4 };	//コリジョンの判定を始めるカウント
	static constexpr int START_CANCELTIME{ 10 };	//キャンセルが始める時間
	static constexpr float ATTACK_LENGTH{ 75.0f };		//攻撃の距離

	CPlayerBehavior_DashAttack() {}
	CPlayerBehavior_DashAttack(CPlayer* player)
	{
		//パラメータの設定
		SetCancelTime(START_CANCELTIME);	//キャンセル
		SetEndTime(END_TIME);				//終了時間
		SetCollisionTime(START_COLLISION);	//当たり判定
		SetAttackLength(ATTACK_LENGTH);		//攻撃の距離
	}
	~CPlayerBehavior_DashAttack() override {}			//デストラクタ

	//行動
	void Behavior(CPlayer* player) override {};
};

//==========================
//ダッシュ攻撃(1段目)
//==========================
class CPlayerBehavior_DashAttack000 : public CPlayerBehavior_DashAttack
{
public:

	CPlayerBehavior_DashAttack000() {}
	CPlayerBehavior_DashAttack000(CPlayer* player);		//コンストラクタ
	~CPlayerBehavior_DashAttack000() override {}			//デストラクタ

	//行動
	void Behavior(CPlayer* player) override;

	//キャンセル時の処理
	void Cancel(CPlayer* player) override;
};

//==========================
//ダッシュ攻撃(2段目)
//==========================
class CPlayerBehavior_DashAttack001 : public CPlayerBehavior_DashAttack
{
public:

	CPlayerBehavior_DashAttack001() {}
	CPlayerBehavior_DashAttack001(CPlayer* player);		//コンストラクタ
	~CPlayerBehavior_DashAttack001() override {}			//デストラクタ

	//行動
	void Behavior(CPlayer* player) override;

	//キャンセル時の処理
	void Cancel(CPlayer* player) override;
};


#endif