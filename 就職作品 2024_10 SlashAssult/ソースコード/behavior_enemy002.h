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
class CEnemyBehavior_Standby : public CEnemyBehavior
{
public:

	//関数
	CEnemyBehavior_Standby(CEnemy* enemy);	//コンストラクタ
	void Action(CEnemy* enemy) override;	//アクション
	void NextAction(CEnemy* enemy) override;//攻撃アクションを設定

private:

	//定数
	static constexpr int COOL_TIME{ 90 };			//クールタイムの時間
	static constexpr int LIFE_FIRST_ATTACK{ 35 };	//１番目の攻撃を行う体力

	//変数
	int m_nCoolTime;	//クールタイム
};

//==========================
//消える
//==========================
class CEnemyBehavior_Disappear : public CEnemyBehavior
{
public:

	//関数
	CEnemyBehavior_Disappear(CEnemy* enemy);	//コンストラクタ
	void Action(CEnemy* enemy) override;		//アクション
	void NextAction(CEnemy* enemy) override;	//攻撃アクションを設定

private:

	//定数
	static constexpr int DISAPPEAR_TIME{ 60 };		//消える時間
	static constexpr int LIFE_FIRST_ATTACK{ 35 };	//１番目の攻撃を行う体力

	//変数
	int m_nDisappearTime;	//消える時間
};

//前方宣言
class CEnemyBullet;

//==========================
//チャージショット
//==========================
class CEnemyBehavior_ChargeShot : public CEnemyBehavior
{
public:

	//関数
	CEnemyBehavior_ChargeShot(CEnemy* enemy);	//コンストラクタ
	~CEnemyBehavior_ChargeShot();				//デストラクタ
	void Action(CEnemy* enemy) override;	//攻撃
	void NextAction(CEnemy* enemy) override;//待機アクションを設定
	void Erase(CEnemyBullet* bullet);		//弾のポインタを削除

	//弾のポインタ
	void SetBullet(CEnemyBullet* bullet) { m_pBullet = bullet; }	//設定
	CEnemyBullet* GetBullet() { return m_pBullet; }					//取得

	//次の行動に移行するフラグ
	void SetNextFlag(bool flag) { m_bNext = flag; }	//設定

private:

	//定数
	static constexpr int CHARGE_TIME{ 230 };			//チャージ時間
	static constexpr int CREATE_BULLET_TIME{ 50 };		//弾の生成時間
	static constexpr int END_TIME{ 300 };				//アクション終了時間
	static constexpr float ADD_SCALE_VALUE{ 0.02f };	//スケールの加算量
	static constexpr float BULLET_LENGTH{ 18.0f };		//弾の生成する距離
	static constexpr float BULLET_SPEED{ 3.0f };		//弾速
	static constexpr float MAX_RUNDOM_LENGTH{ 400.0f };	//距離の最大ランダム値

	//関数
	void LookAtPlayer(CEnemy* enemy);	//プレイヤーの方向を向く
	void CreateBullet(CEnemy* enemy);	//弾の生成
	bool CanCreateBullet();				//弾の生成が出来るか
	void UpdateBullet(CEnemy* enemy);	//弾の更新
	void EnlargeBullet(CEnemy* enemy, float angle);	//弾を大きくする
	void ShotBullet(float angle);		//弾を発射する
	bool CheckBulletHit();				//弾が当たっているか確認
	void HitBullet();					//弾がヒット時の処理

	//変数
	int m_nChargeCount;				//チャージのカウント
	CEnemyBullet* m_pBullet;		//弾のポインタ
	CEffect_ChargeShot* m_pEffect;	//エフェクトのポインタ
	bool m_bNext;					//次の行動をするか
};

//==========================
//ワープショット
//==========================
class CEnemyBehavior_WarpShot : public CEnemyBehavior_ChargeShot
{
public:

	//関数
	CEnemyBehavior_WarpShot(CEnemy* enemy);		//コンストラクタ
	~CEnemyBehavior_WarpShot() override;			//デストラクタ
	void Action(CEnemy* enemy) override;		//攻撃
	void NextAction(CEnemy* enemy) override;	//待機アクションを設定

private:

	//定数
	static constexpr float MAX_RUNDOM_LENGTH{ 400.0f };	//距離の最大ランダム値
	
};

//==========================
//演出
//==========================
class CEnemyBehavior_Direction : public CEnemyBehavior
{
public:

	//関数
	CEnemyBehavior_Direction(CEnemy* enemy);	//コンストラクタ
	void Action(CEnemy* enemy) override;	//演出
	void NextAction(CEnemy* enemy) override;//スタンバイアクションを設定

private:

	//定数
	static constexpr int DIRECTION_TIME{ 300 };	//演出の時間

	//変数
	int m_nCount;	//カウント用
};

//==========================
//撃破演出
//==========================
class CEnemyBehavior_Direction_Destroy : public CEnemyBehavior
{
public:

	//関数
	CEnemyBehavior_Direction_Destroy(CEnemy* enemy);	//コンストラクタ
	void Action(CEnemy* enemy) override;			//演出

private:

	//定数
	static constexpr int DIRECTION_TIME{ 500 };	//演出の時間
	static const D3DXVECTOR3 CAMERA_POSV;		//カメラ視点の位置

	//変数
	int m_nCount;	//カウント用
};


//==========================
//分身攻撃
//==========================
class CEnemyBehavior_AlterEgoAttack : public CEnemyBehavior_ChargeShot
{
public:

	
	//関数
	CEnemyBehavior_AlterEgoAttack(CEnemy* enemy);	//コンストラクタ
	~CEnemyBehavior_AlterEgoAttack();				//デストラクタ
	void Action(CEnemy* enemy) override;			//分身後に射撃
	void NextAction(CEnemy* enemy) override;		//待機アクションを設定
	void Erase(CEnemy002_AlterEgo* enemy);			//分身のポインタを削除

private:

	//定数
	static constexpr float TIME_INTERPOLATION_ALPHA{ 10 };	//アルファ値を変化させる時間
	static constexpr int TIME_START_APPEAR{ 60 };			//出現を始める時間
	static constexpr int TIME_END_ACTION{ 90 };				//アクションの終わる時間
	static constexpr int NUM_ALTEREGO{ 3 };					//分身の数
	static constexpr float LENGTH_ENEMY{ 300.0f };			//敵の距離
	static constexpr float ADD_RUNDOM{ 0.03f };			//ランダム値の加算量

	//関数
	void UpdatePos(CEnemy* enemy);	//位置の更新

	//変数
	bool m_bCreateAlterEgo;							//分身を生成したか
	CEnemyBehavior_ChargeShot* m_pShotAction;		//ショットのポインタ
	CEnemy002_AlterEgo* m_pAlterEgo[NUM_ALTEREGO];	//分身のポインタ
	float m_fRundam;								//乱数の保存
};

#endif