//================================
//
//game.cppに必要な宣言[game.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _GAME_H_ //このマクロ定義がされていなかったら
#define _GAME_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "scene.h"
#include "player.h"
#include "field.h"
#include "time.h"
#include "enemymanager.h"
#include "gimmickmanager.h"
#include "explosionmanager.h"
#include "enemybulletmanager.h"
#include "barriermanager.h"
#include "lockon.h"
#include "direction.h"

class CPlayer;

//ゲームクラス
class CGame : public CScene
{
public:

	//定数
	static const D3DXVECTOR3 TIME_POS;	//時間の位置

	//メンバ関数
	CGame();						//コンストラクタ
	~CGame() override;				//デストラクタ
	HRESULT Init() override;		//初期化
	void Uninit() override;			//終了
	void Update() override;			//更新
	void Draw() override;			//描画
	void Load() override;			//読み込み

	//ポインタの取得
	CPlayer* GetGamePlayer() { if (m_pPlayer == nullptr) { return nullptr; } return m_pPlayer; }								//プレイヤーの取得
	CField* GetGameField() { if (m_pField == nullptr) { return nullptr; } return m_pField; }									//フィールドの取得
	CTime* GetTime() { if (m_pTime == nullptr) { return nullptr; } return m_pTime; }											//時間の取得
	CEnemyManager* GetEnemyManager() { if (m_pEnemyManager == nullptr) { return nullptr; } return m_pEnemyManager; }			//エネミーマネージャーの取得
	CGimmickManager* GetGimmickManager() { if (m_pGimmickManager == nullptr) { return nullptr; } return m_pGimmickManager; }	//ギミックマネージャーの取得
	CExplosionManager* GetExplosionManager() { if (m_pExplosionManager == nullptr) { return nullptr; } return m_pExplosionManager; }	//爆発マネージャーの取得
	CEnemyBulletManager* GetEnemyBulletManager() { if (m_pEnemyBulletManager == nullptr)  { return nullptr; } return m_pEnemyBulletManager;}	//エネミー弾の取得
	CBarrierManager* GetBarrierManager() { if (m_pBarrierManager == nullptr) { return nullptr; } return m_pBarrierManager; }			//結界マネージャー
	CLockon* GetLockon() { if (m_pLockon == nullptr) { return nullptr; } return m_pLockon; }									//ロックオンの取得
	void SetLockon(bool lockon);																								//ロックオンの設定

	//クリア判定
	void SetClear(bool clear) { m_bClear = clear; }	//設定

	//戦闘判定
	void SetBattle(bool battle) { m_bBattle = battle; }	//設定

	//ゲームオーバー判定
	void SetGameOver(bool gameover) { m_bGameOver = gameover; }	//設定

	//演出
	void SetDirection(CDirection::DIRECTIONTYPE type);	//演出の種類を設定
	bool GetDirectioning() { return m_bDirectioning; }	//取得

private:

	void ModelLoad();	//モデルの読み込み

	CPlayer* m_pPlayer;					//プレイヤー
	CField* m_pField;					//フィールド
	CTime* m_pTime;						//タイムクラス
	CEnemyManager* m_pEnemyManager;		//エネミーマネージャー
	CGimmickManager* m_pGimmickManager;	//ギミックマネージャー
	CExplosionManager* m_pExplosionManager;	//爆発マネージャー
	CLockon* m_pLockon;						//ロックオン
	CEnemyBulletManager* m_pEnemyBulletManager;	//エネミー弾マネージャー
	CBarrierManager* m_pBarrierManager;		//結界マネージャー

	//判定
	bool m_bClear;			//クリア判定
	bool m_bBattle;			//戦闘中か
	bool m_bGameOver;		//ゲームオーバー判定

	//演出
	bool m_bDirectioning;		//演出中か
	CDirection* m_pDirection;	//演出のポインタ
};

#endif