//================================
//
//enemy003.cppに必要な宣言[enemy003.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _ENEMY003_H_ //このマクロ定義がされていなかったら
#define _ENEMY003_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "enemy.h"
#include "state_enemy003.h"

//エネミークラス
class CEnemy003 : public CEnemy
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
		ENEMY003MOTION_NORMAL = 0,	//ニュートラル
		ENEMY003MOTION_WALK,		//移動
		ENEMY003MOTION_ACTION,		//アクション
		ENEMY003MOTION_DAMAGE,		//ダメージ
		ENEMY003MOTION_MAX			//最大
	}ENEMY003MOTION;

	//メンバ関数
	CEnemy003();						//コンストラクタ
	~CEnemy003() override;				//デストラクタ
	HRESULT Init() override;			//初期化
	void Uninit() override;				//終了
	void Update() override;				//更新
	void Draw() override;				//描画

	//ダメージの設定
	bool SetDamage(int damage, float angle) override;	//ダメージの設定

	//状態のリセット
	void StateReset() override;

	//貼り付け状態に変更
	void ChangeStickState() override;

	//スタン状態に変更
	void ChangeStanState() override;

	//攻撃中か
	void SetAttacking(bool attacking) { m_bAttacking = attacking; }	//設定
	bool GetAttacking() { return m_bAttacking; }					//取得

private:

	//変数
	bool m_bAttacking;	//攻撃中か
};

#endif