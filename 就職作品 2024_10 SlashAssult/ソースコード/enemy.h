//================================
//
//enemy.cppに必要な宣言[enemy.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _ENEMY_H_ //このマクロ定義がされていなかったら
#define _ENEMY_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "game_character.h"
#include "collision.h"
#include "state_enemy.h"

//前方宣言
class CState_Enemy;
class CPlayer;

//エネミークラス
class CEnemy : public CGame_Character
{
public:

	//定数
	static constexpr float VALUE_KNOCKBACK = 10.0f;	//ノックバック値
	static constexpr float VALUE_BLOWOFF = 5.0f;	//吹き飛ぶ量

	//エネミーの種類の列挙型
	typedef enum
	{
		ENEMYTYPE_ENEMY000 = 0,	//通常のエネミー
		ENEMYTYPE_ENEMY001,		//盾持ちのエネミー
		ENEMYTYPE_ENEMY002,		//ボスのエネミー
		ENEMYTYPE_ENEMY003,		//突進のエネミー
		ENEMYTYPE_MAX,			//最大値
	}ENEMYTYPE;

	//メンバ関数
	CEnemy(int nPriority = 3);	//コンストラクタ
	virtual ~CEnemy() override;										//デストラクタ
	virtual HRESULT Init() override;								//初期化
	virtual void Uninit() override;									//終了
	virtual void Update() override;									//更新
	virtual void Draw() override;									//描画
	static CEnemy* Create(D3DXVECTOR3 pos, ENEMYTYPE type);			//エネミーの生成
	ENEMYTYPE& GetType() { return m_EnemyType; }					//エネミーの種類を返す

	//状態処理の関数
	virtual bool SetBlowOff();

	//ダメージの設定
	bool SetDamage(int damage, float angle) override;				//ダメージの設定
	//virtual bool SetDamage(int damage, float rotY);					//ダメージの設定
	virtual bool SetBlowDamage(int damage, float rotY);				//吹き飛ばしてダメージを与える
	virtual bool SetBlowDamage(int damage, float rotY, float value);//吹き飛ばしてダメージを与える

	//状態変更
	void ChangeState(CState_Enemy* state);
	CState_Enemy* GetState() { if (m_pState != nullptr) { return m_pState; } return nullptr; }

	//最初の位置
	D3DXVECTOR3 GetStartPos() { return m_StartPos; }	//取得

	//ダメージを与えた際に与える影響
	virtual void DamageEffect(CPlayer* player) {}

	//状態のリセット
	virtual void StateReset()
	{
		
	}

	//貼り付け状態に変更
	virtual void ChangeStickState()
	{

	}

	//スタン状態に変更
	virtual void ChangeStanState()
	{

	}

	//コリジョン処理
	void SetCollisionProcess(bool process) { m_bCollisionProcess = process; }	//設定
	bool GetCollisionProcess() { return m_bCollisionProcess; }					//取得

	//死亡時の処理
	void SetCharacterDeath() override;

private:

	//メンバ変数
	ENEMYTYPE m_EnemyType;
	CState_Enemy* m_pState;
	D3DXVECTOR3 m_StartPos;		//最初の位置
	bool m_bCollisionProcess;	//コリジョン処理をするか
};

#endif