//================================
//
//enemybullet.cppに必要な宣言[enemybullet.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _ENEMYBULLET_H_ //このマクロ定義がされていなかったら
#define _ENEMYBULLET_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "objectX.h"
#include "collision.h"
#include "behavior_enemy002.h"
#include "state_bullet.h"

//前方宣言
class CEnemyBehavior_ChargeShot;
class CState_Bullet;

//ボスの弾クラス
class CEnemyBullet : public CObjectX
{
public:

	//定数
	static const std::string FILEPATH;					//パス
	static constexpr float COLLISION_RADIUS{10.0f};		//当たり判定の半径
	static constexpr float CAMERA_SHAKE_FRAME{ 20.0f };	//カメラが揺れる時間
	static constexpr float CAMERA_SHAKE_VALUE{ 30.0f };	//カメラの揺れる強さ
	static constexpr float ENEMY_BROW_VALUE{ 80.0f };	//敵が吹き飛ぶ値
	static constexpr int ENEMY_DAMAGE_VALUE{ 3 };		//敵が与えるダメージ値
	static constexpr float REFLECTION_SPEED{ 5.0f };	//反射時のスピード

	//メンバ関数
	CEnemyBullet(int nPriority = 2);				//コンストラクタ
	~CEnemyBullet() override;						//デストラクタ
	HRESULT Init() override;						//初期化
	void Uninit() override;							//終了
	void Update() override;							//更新
	void Draw() override;							//描画
	static CEnemyBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, CEnemyBehavior_ChargeShot* action, CEnemy* enemy);	//生成
	void HitProcess();								//ヒット時の処理

	//移動量
	void SetMove(D3DXVECTOR3 move) { m_Move = move; }	//設定
	D3DXVECTOR3& GetMove() { return m_Move; }			//取得

	//サイズ倍率
	void SetSizeRate(float rate) { m_fSizeRate = rate; }	//設定
	float& GetSizeRate() { return m_fSizeRate; }			//取得
	void AddSizeRate(float rate) { m_fSizeRate += rate; }	//加算

	//反射したか
	void SetReflection(bool reflection) { m_bReflection = reflection; }	//設定
	bool GetReflection() { return m_bReflection; }						//取得

	//反射させる処理
	void Reflection(float angle);	//反射処理

	//撃たれたか
	void SetShooting(bool shooting) { m_bShooting = shooting; }	//設定
	bool GetShooting() { return m_bShooting; }					//取得

	//当たり判定
	CCollision* GetCollision() { return m_Collision; }		//取得

	//判定
	bool IsHitWall();	//壁に当たったか

private:

	//関数
	void UpdatePos();		//位置の更新
	void UpdateCollision();	//当たり判定の更新

	//メンバ変数
	D3DXVECTOR3 m_Move;							//移動量
	float m_fSizeRate;							///サイズ倍率
	bool m_bReflection;							//反射したか
	bool m_bShooting;							//撃たれたか
	CCollision* m_Collision;					//当たり判定
	CEnemyBehavior_ChargeShot* m_pParentAction;	//親のアクションのポインタ
	CEnemy* m_pParentEnemy;						//親の敵
	CState_Bullet* m_pState;					//状態
};

#endif