//================================
//
//behavior_enemy002.cppに必要な宣言[behavior_enemy002.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BEHAVIOR_ENEMY002_H_ //このマクロ定義がされていなかったら
#define _BEHAVIOR_ENEMY002_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "behavior_enemy.h"
#include "enemybullet.h"
#include "effect_chargeshot.h"
#include "enemy002_alterego.h"

//前方宣言
class CEnemy002_AlterEgo;

//==========================
//追いかける
//==========================
class CEnemyAction_Standby : public CEnemyAction
{
public:

	//定数
	static constexpr int COOL_TIME{ 90 };			//クールタイムの時間
	static constexpr int LIFE_FIRST_ATTACK{ 35 };	//１番目の攻撃を行う体力

	//関数
	CEnemyAction_Standby(CEnemy* enemy);	//コンストラクタ
	void Action(CEnemy* enemy) override;	//アクション
	void NextAction(CEnemy* enemy) override;//攻撃アクションを設定

private:

	int m_nCoolTime;	//クールタイム
};

//==========================
//消える
//==========================
class CEnemyAction_Disappear : public CEnemyAction
{
public:

	//定数
	static constexpr int DISAPPEAR_TIME{ 60 };		//消える時間
	static constexpr int LIFE_FIRST_ATTACK{ 35 };	//１番目の攻撃を行う体力

	//関数
	CEnemyAction_Disappear(CEnemy* enemy);	//コンストラクタ
	void Action(CEnemy* enemy) override;	//アクション
	void NextAction(CEnemy* enemy) override;//攻撃アクションを設定

private:

	int m_nDisappearTime;	//消える時間
};

//前方宣言
class CEnemyBullet;

//==========================
//チャージショット
//==========================
class CEnemyAction_ChargeShot : public CEnemyAction
{
public:

	static constexpr int CHARGE_TIME{ 230 };			//チャージ時間
	static constexpr int CREATE_BULLET_TIME{ 50 };		//弾の生成時間
	static constexpr int END_TIME{ 300 };				//アクション終了時間
	static constexpr float ADD_SCALE_VALUE{ 0.03f };	//スケールの加算量
	static constexpr float BULLET_LENGTH{ 20.0f };		//弾の生成する距離
	static constexpr float BULLET_SPEED{ 3.0f };		//弾速
	static constexpr float MAX_RUNDOM_LENGTH{ 400.0f };	//距離の最大ランダム値

	//関数
	CEnemyAction_ChargeShot(CEnemy* enemy);	//コンストラクタ
	~CEnemyAction_ChargeShot();				//デストラクタ
	void Action(CEnemy* enemy) override;	//攻撃
	void NextAction(CEnemy* enemy) override;//待機アクションを設定
	void Erase(CEnemyBullet* bullet);		//弾のポインタを削除

	//弾のポインタ
	void SetBullet(CEnemyBullet* bullet) { m_pBullet = bullet; }	//設定
	CEnemyBullet* GetBullet() { return m_pBullet; }					//取得

	//次の行動に移行するフラグ
	void SetNextFlag(bool flag) { m_bNext = flag; }	//設定

private:
	int m_nChargeCount;				//チャージのカウント
	CEnemyBullet* m_pBullet;		//弾のポインタ
	CEffect_ChargeShot* m_pEffect;	//エフェクトのポインタ
	bool m_bNext;					//次の行動をするか
};

//==========================
//ワープショット
//==========================
class CEnemyAction_WarpShot : public CEnemyAction_ChargeShot
{
public:

	static constexpr float MAX_RUNDOM_LENGTH{ 400.0f };	//距離の最大ランダム値

	//関数
	CEnemyAction_WarpShot(CEnemy* enemy);		//コンストラクタ
	~CEnemyAction_WarpShot() override;			//デストラクタ
	void Action(CEnemy* enemy) override;		//攻撃
	void NextAction(CEnemy* enemy) override;	//待機アクションを設定

private:
	
};

//==========================
//演出
//==========================
class CEnemyAction_Direction : public CEnemyAction
{
public:

	static constexpr int DIRECTION_TIME{ 300 };	//演出の時間

	//関数
	CEnemyAction_Direction(CEnemy* enemy);	//コンストラクタ
	void Action(CEnemy* enemy) override;	//演出
	void NextAction(CEnemy* enemy) override;//スタンバイアクションを設定

private:
	int m_nCount;	//カウント用
};

//==========================
//撃破演出
//==========================
class CEnemyAction_Direction_Destroy : public CEnemyAction
{
public:

	//定数
	static constexpr int DIRECTION_TIME{ 500 };	//演出の時間
	static const D3DXVECTOR3 CAMERA_POSV;		//カメラ視点の位置

	//関数
	CEnemyAction_Direction_Destroy(CEnemy* enemy);	//コンストラクタ
	void Action(CEnemy* enemy) override;			//演出

private:
	int m_nCount;	//カウント用
};


//==========================
//分身攻撃
//==========================
class CEnemyAction_AlterEgoAttack : public CEnemyAction_ChargeShot
{
public:

	//分身
	static constexpr float TIME_INTERPOLATION_ALPHA{ 10 };	//アルファ値を変化させる時間
	static constexpr int TIME_START_APPEAR{ 60 };			//出現を始める時間
	static constexpr int TIME_END_ACTION{ 90 };				//アクションの終わる時間
	static constexpr int NUM_ALTEREGO{ 3 };					//分身の数

	//弾
	//static constexpr int CHARGE_TIME{ 230 };				//チャージ時間
	//static constexpr int CREATE_BULLET_TIME{ 50 };			//弾の生成時間
	//static constexpr int END_TIME{ 300 };					//アクション終了時間
	//static constexpr float ADD_SCALE_VALUE{ 0.03f };		//スケールの加算量
	
	//関数
	CEnemyAction_AlterEgoAttack(CEnemy* enemy);	//コンストラクタ
	~CEnemyAction_AlterEgoAttack();				//デストラクタ
	void Action(CEnemy* enemy) override;		//分身後に射撃
	void NextAction(CEnemy* enemy) override;	//待機アクションを設定
	void Erase(CEnemy002_AlterEgo* enemy);		//分身のポインタを削除

private:

	//分身用
	bool m_bCreateAlterEgo;							//分身を生成したか
	CEnemyAction_ChargeShot* m_pShotAction;			//ショットのポインタ
	CEnemy002_AlterEgo* m_pAlterEgo[NUM_ALTEREGO];	//分身のポインタ

	//弾用
	//int m_nChargeCount;				//チャージのカウント
	//CEnemyBullet* m_pBullet;		//弾のポインタ
	//CEffect_ChargeShot* m_pEffect;	//エフェクトのポインタ
};

#endif