//================================
//
//player.cppに必要な宣言[player.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _PLAYER_H_ //このマクロ定義がされていなかったら
#define _PLAYER_H_ //２重インクルード防止のマクロ定義

#include "character.h"
#include "gauge_playerlife.h"
#include "orbit.h"
#include "state_player.h"

//前方宣言
class CState_Player;

//プレイヤークラス
class CPlayer : public CCharacter
{
public:
	//定数
	static const float DAMAGE_IMPULSE;		//ダメージのノックバック量
	static const std::string FILEPATH;		//読み込むファイル
	
	//キーの種類
	typedef enum
	{
		PLAYERMOTION_NORMAL = 0,
		PLAYERMOTION_WALK,
		PLAYERMOTION_ACTION,
		PLAYERMOTION_JUMP,
		PLAYERMOTION_ARIAL000,
		PLAYERMOTION_ARIAL001,
		PLAYERMOTION_ARIAL002,
		PLAYERMOTION_KNOCKBACK,
		PLAYERMOTION_DAMAGE,
		PLAYERMOTION_ACTION001,
		PLAYERMOTION_ACTION002,
		PLAYERMOTION_ATTACKCHARGE,
		PLAYERMOTION_CHARGEATTACK,
		PLAYERMOTION_DASHATTACK000,
		PLAYERMOTION_DASHATTACK001,
		PLAYERMOTION_MAX
	}PLAYERMOTION;

	//メンバ関数
	CPlayer(int nPriority = 2);				//コンストラクタ
	~CPlayer() override;					//デストラクタ
	HRESULT Init() override;				//初期化
	void Uninit() override;					//終了
	void Update() override;					//更新
	void Draw() override;					//描画
	bool SetDamage(int damage) override;	//ダメージを設定
	D3DXVECTOR3 GravityMove(D3DXVECTOR3 move) override;	//重力の処理
	void UpdatePos() override;				//位置の更新

	//設定と取得
	void SetState(CState_Player* state);									//状態の設定
	void SetKnockBack(int time);											//ノックバックの設定
	void SetOrbit(bool set);												//軌跡の設定
	void SetLifeGauge(CGauge_PlayerLife* gauge) { m_pLifeGauge = gauge; }	//体力ゲージの設定
	CGauge_PlayerLife* GetLifeGauge() { return m_pLifeGauge; }				//体力ゲージの取得

	//状態変更
	void ChangeState(CState_Player* state);
	CState_Player* GetState() { if (m_pState != nullptr) { return m_pState; } return nullptr; }

	//静的関数
	static CPlayer* Create();	//Playerの生成
private:

	//メンバ変数
	CGauge_PlayerLife* m_pLifeGauge;//体力ゲージのポインタ
	CState_Player* m_pState;		//状態のインスタンス
};

#endif