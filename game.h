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

class CPlayer;

//ゲームクラス
class CGame : public CScene
{
public:

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
	void SetClear(bool crear) { m_bClear = crear; }	//設定

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

	
	bool m_bClear;			//クリア判定
	bool m_bDirectioning;	//演出中か
};

#endif