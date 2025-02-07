//================================
//
//enemy000.cppに必要な宣言[enemy000.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _ENEMY000_H_ //このマクロ定義がされていなかったら
#define _ENEMY000_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "enemy.h"
#include "state_enemy000.h"

//エネミークラス
class CEnemy000 : public CEnemy
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
		ENEMY000MOTION_NORMAL = 0,	//ニュートラル
		ENEMY000MOTION_WALK,		//移動
		ENEMY000MOTION_ACTION,		//アクション
		ENEMY000MOTION_BRUW,		//吹き飛び
		ENEMY000MOTION_STANDUP,		//立ち上がる
		ENEMY000MOTION_DAMAGE,		//ダメージ
		ENEMY000MOTION_STICK,		//張り付き
		ENEMY000MOTION_MAX			//最大
	}ENEMY000MOTION;

	//メンバ関数
	CEnemy000();						//コンストラクタ
	~CEnemy000() override;				//デストラクタ
	HRESULT Init() override;			//初期化
	void Uninit() override;				//終了
	void Update() override;				//更新
	void Draw() override;				//描画

	//ダメージの設定
	bool SetDamage(int damage, float angle) override;	//ダメージの設定

	//状態のリセット
	void StateReset() override
	{
		//通常の状態に戻す
		ChangeState(new CState_Enemy000_Normal(this));
		SetEnableGravity(true);
	}

	//貼り付け状態に変更
	void ChangeStickState() override
	{
		ChangeState(new CState_Enemy000_Stick(this));
	}

	//スタン状態に変更
	void ChangeStanState() override
	{
		ChangeState(new CState_Enemy000_Stan(this));
	}
};

#endif