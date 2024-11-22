//================================
//
//enemy001.cppに必要な宣言[enemy001.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _ENEMY001_H_ //このマクロ定義がされていなかったら
#define _ENEMY001_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "enemy.h"
#include "action_enemy001.h"
#include "shield.h"

//エネミークラス
class CEnemy001 : public CEnemy
{
public:

	//定数
	static const std::string FILEPATH;		//読み込むファイル
	static const float MOVE_VALUE;			//移動量
	static const float STARTATTACK_RANGE;	//攻撃を始める範囲

	//敵のモーション
	typedef enum
	{
		ENEMY001MOTION_NORMAL = 0,	//ニュートラル
		ENEMY001MOTION_WALK,		//移動
		ENEMY001MOTION_SHIELD_SPAWN,//シールドのスポーン
		ENEMY001MOTION_AIR,			//空中
		ENEMY001MOTION_GET_UP,		//起き上がり
		ENEMY001MOTION_ATTACK,		//攻撃
		ENEMY001MOTION_MAX			//最大
	}ENEMY001MOTION;

	//メンバ関数
	CEnemy001();						//コンストラクタ
	~CEnemy001() override;				//デストラクタ
	HRESULT Init() override;			//初期化
	void Uninit() override;				//終了
	void Update() override;				//更新
	void Draw() override;				//描画

	//パラメータ関数
	void SetDamage(int damage) override;	//ダメージの設定

	//状態処理の関数
	bool SetBlowOff() override;

private:

	CShield* m_pShield;				//盾のインスタンス
};

#endif