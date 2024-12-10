//================================
//
//enemy002.cppに必要な宣言[enemy002.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _ENEMY002_H_ //このマクロ定義がされていなかったら
#define _ENEMY002_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "enemy.h"
#include "state_enemy002.h"

//エネミークラス
class CEnemy002 : public CEnemy
{
public:

	//定数
	static const std::string FILEPATH;		//読み込むファイル
	//static const float MOVE_VALUE;			//移動量
	//static const float STARTATTACK_RANGE;	//攻撃を始める範囲

	//敵のモーション
	typedef enum
	{
		ENEMY002MOTION_NORMAL = 0,	//ニュートラル
		ENEMY002MOTION_WALK,		//移動
		ENEMY002MOTION_TAKEOUT,		//取り出し
		ENEMY002MOTION_THROW,		//投げる
		ENEMY002MOTION_CHARGESHOT,	//チャージショット
		ENEMY002MOTION_STAN,		//スタン
		ENEMY002MOTION_DIRECTION,	//演出用
		ENEMY002MOTION_MAX			//最大
	}ENEMY002MOTION;

	//メンバ関数
	CEnemy002();						//コンストラクタ
	~CEnemy002() override;				//デストラクタ
	HRESULT Init() override;			//初期化
	void Uninit() override;				//終了
	void Update() override;				//更新
	void Draw() override;				//描画

	//ダメージの設定
	bool SetDamage(int damage) override;							//ダメージの設定
	bool SetDamage(int damage, float rotY) override;				//ダメージの設定
	bool SetBlowDamage(int damage, float rotY) override;			//吹き飛ばしてダメージを与える
	bool SetBlowDamage(int damage, float rotY, float value) override;//吹き飛ばしてダメージを与える

	//状態のリセット
	void StateReset() override
	{
		//通常の状態に戻す
		ChangeState(new CState_Enemy002_Normal(this));
		SetEnableGravity(true);
		m_bMaterialized = false;
	}

	//貼り付け状態に変更
	void ChangeStickState() override
	{
		ChangeState(new CState_Enemy002_Stick(this));
	}

	//スタン状態に変更
	void ChangeStanState() override
	{
		ChangeState(new CState_Enemy002_Stan(this));
		m_bMaterialized = true;
	}

	//実体化しているか
	void SetMaterialized(bool materialized) { m_bMaterialized = materialized; }	//設定
	bool GetMaterialized() { return m_bMaterialized; }							//取得

private:
	bool m_bMaterialized;	//実体化しているか
};

#endif