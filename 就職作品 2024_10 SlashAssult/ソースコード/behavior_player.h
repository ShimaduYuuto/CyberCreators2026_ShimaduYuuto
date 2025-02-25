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
#include "effect_charge.h"
#include "orbit.h"

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

	//予め決めた次の行動
	virtual void NextBehavior(CPlayer* player) {}

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
	~CPlayerBehavior_Move() {}						//デストラクタ

	//行動
	void Behavior(CPlayer* player) override;

private:

	//メンバ関数
	D3DXVECTOR3 UpdateMove(CPlayer* player, D3DXVECTOR3& Rotgoal);	//移動量の更新
	void Action(CPlayer* player);									//アクション処理

	bool CheckUpdateKeyboard(CPlayer* player, D3DXVECTOR3& Rotgoal, D3DXVECTOR3* move);	//キーボードで更新されたかを確認
	bool CheckUpdateStick(bool pressed);												//スティックで更新されたかを確認
	void UpdateStickMove(D3DXVECTOR3& Rotgoal, D3DXVECTOR3* move);						//スティック移動での更新
	void ChangeMotion();
};

//==========================
//ダッシュ
//==========================
class CPlayerBehavior_Dash : public CPlayerBehavior
{
public:

	//定数
	static constexpr float DASH_SPEED{ 14.0f };		//ダッシュの速度
	static constexpr float STOP_LENGYH{ 70.0f };	//止まる距離
	static constexpr float RATIO_LINEAR_INTERPOLATION{ 0.08f };	//線形補間の割合

	//メンバ関数
	CPlayerBehavior_Dash() {}						//コンストラクタ
	CPlayerBehavior_Dash(CPlayer* player);			//コンストラクタ

	//行動
	void Behavior(CPlayer* player) override;

private:
	D3DXVECTOR3 m_DashSpeed;	//ダッシュの速度
	bool m_bFirst;				//初めて通ったか
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
	static constexpr int TYPE_AHEAD{ 30 };				//先行入力の受付時間
	static constexpr float ATTACK_LENGTH{ 50.0f };		//攻撃の距離
	static const D3DXVECTOR3 POS_OFFSET;				//オフセット位置
	static constexpr float ORBIT_OFFSET_LENGTH{ 50.0f };//軌跡のオフセットの距離

	//関数
	CPlayerBehavior_Attack();						//コンストラクタ
	CPlayerBehavior_Attack(CPlayer* player);		//コンストラクタ
	~CPlayerBehavior_Attack() override;				//デストラクタ

	//行動
	void Behavior(CPlayer* player) override;
	
	//パラメーターの設定
	void SetCancelTime(int time) { m_nCancelStartTime = time; }			//キャンセル時間の設定
	void SetEndTime(int time) { m_nEndTime = time; }					//終了時間の設定
	void SetCollisionTime(int time) { m_nCollisionlTime = time; }		//当たり判定出現時間
	void SetAttackLength(float length) { m_fAttackLength = length; }	//攻撃の距離の設定
	void SetOffsetPos(D3DXVECTOR3 pos) { m_OffsetPos = pos; }			//オフセット位置

	//キャンセルの処理
	virtual void Cancel(CPlayer* player) {}	//キャンセル時の処理
	void CancelInput();						//キャンセル入力の処理

	//カウント
	void SetCount(int count) { m_nEndCount = count; }	//設定
	int GetCount() { return m_nEndCount; }				//取得

	//次の行動
	void NextBehavior(CPlayer* player) override;

	//攻撃のキー判定
	bool TriggerAttack();

	//敵の方向を向く
	void LookAtEnemy(CPlayer* player);	

private:

	//関数
	bool IsHitProcess();												//当たり判定の処理を行うか
	void HitEnemyProcess(CPlayer* player, D3DXVECTOR3 pos);				//敵との当たり判定を確認
	void HitBulletProcess(CPlayer* player, D3DXVECTOR3 pos);			//弾との当たり判定を確認
	virtual void Damage(CPlayer* player, CEnemy* enemy, int damage);	//ダメージを与える
	bool CheckEnemyInFront(CPlayer* player, float targetangle, float radian);			//自分の前に敵がいるかを確認
	void Effect(CPlayer* player);										//エフェクトの処理

	//変数
	int m_nEndCount;				//終了カウント
	std::list<CEnemy*> m_HitEnemy;	//当たった敵保存用
	int m_nCancelStartTime;			//キャンセル出来るカウント
	int m_nEndTime;					//終了時間
	int m_nCollisionlTime;			//当たり判定が出現する時間
	float m_fAttackLength;			//攻撃の距離
	D3DXVECTOR3 m_OffsetPos;		//オフセットの位置
	bool m_bCancel;					//キャンセルするか
};

//==========================
//通常攻撃
//==========================
class CPlayerBehavior_NormalAttack : public CPlayerBehavior_Attack
{
public:

	static const int END_TIME{ 40 };			//終了までの時間
	static const int END_MOVE{ 10 };			//移動する時間
	static constexpr float VALUE_MOVE{ 0.5f };	//移動量

	CPlayerBehavior_NormalAttack() {}	
	CPlayerBehavior_NormalAttack(CPlayer* player) : CPlayerBehavior_Attack(player)
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
	static constexpr float MAX_RATE{ 100.0f };			//最大倍率
	static constexpr int ACCEPT_CANCELTIME{ 10 };		//キャンセルを受け付ける時間
	static constexpr float ACCELERATION_VALUE{ 0.1f };	//1フレームに加速度に加算する値
	static const int END_TIME{ 20 };					//終了までの時間

	//メンバ関数
	CPlayerBehavior_NormalAttack002(CPlayer* player);			//コンストラクタ

	~CPlayerBehavior_NormalAttack002() override;				//デストラクタ

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
	CEffect_Charge* m_pEffect;		//チャージエフェクトのポインタ
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
	~CPlayerBehavior_Arial() override {}	//デストラクタ

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
//ダッシュ攻撃
//==========================
class CPlayerBehavior_DashAttack : public CPlayerBehavior_Attack
{
public:

	//定数
	static constexpr int END_TIME{ 20 };				//終了までの時間
	static constexpr int START_COLLISION{ 4 };			//コリジョンの判定を始めるカウント
	static constexpr int START_CANCELTIME{ 10 };		//キャンセルが始める時間
	static constexpr float ATTACK_LENGTH{ 75.0f };		//攻撃の距離

	CPlayerBehavior_DashAttack() {}
	CPlayerBehavior_DashAttack(CPlayer* player);	//コンストラクタ
	~CPlayerBehavior_DashAttack() override;			//デストラクタ
	void Behavior(CPlayer* player) override;		//行動

	//ラッシュを続けるか
	void SetRushContinue(bool set) { m_RushContinue = set; }	//設定
	bool GetRushContinue() { return m_RushContinue; }			//取得

private:

	bool m_RushContinue;	//ラッシュを続けるか
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

//==========================
//ガード
//==========================
class CPlayerBehavior_Guard : public CPlayerBehavior
{
public:

	//定数
	static constexpr int TIME_JUSTGUARD{ 10 };			//ジャストガードが発動するフレーム
	static constexpr int TIME_FIRST_STIFFNESS{ 20 };	//ガードの発動時の硬直フレーム

	//メンバ関数
	CPlayerBehavior_Guard(CPlayer* player);			//コンストラクタ

	//行動
	void Behavior(CPlayer* player) override;

private:
	int m_nStiffnessCount;		//発動硬直時のカウント
	bool m_bJustGuard;			//ジャストガードをしたか
	bool m_bStiffening;			//硬直中か
};

#endif