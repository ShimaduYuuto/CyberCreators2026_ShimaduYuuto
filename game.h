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
#include "collision_wall.h"
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

	//インスタンスの取得
	CPlayer* GetGamePlayer() { if (m_pPlayer == nullptr) { return nullptr; } return m_pPlayer; }						//プレイヤーの取得
	CField* GetGameField() { if (m_pField == nullptr) { return nullptr; } return m_pField; }							//フィールドの取得
	CTime* GetTime() { if (m_pTime == nullptr) { return nullptr; } return m_pTime; }									//時間の取得
	CEnemyManager* GetEnemyManager() { if (m_pEnemyManager == nullptr) { return nullptr; } return m_pEnemyManager; }	//エネミーマネージャーの取得
	CCollision_Wall* GetWall() { if (m_pWall == nullptr) { return nullptr; } return m_pWall; }							//壁の取得
	void SetLockon(bool lockon);	//ロックオンの設定

private:
	CPlayer* m_pPlayer;				//プレイヤー
	CField* m_pField;				//フィールド
	CTime* m_pTime;					//タイムクラス
	CEnemyManager* m_pEnemyManager; //エネミーマネージャー
	CLockon* m_pLockon;				//ロックオン
	CCollision_Wall* m_pWall;		//壁
};

#endif