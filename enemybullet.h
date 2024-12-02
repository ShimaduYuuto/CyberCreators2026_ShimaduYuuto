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

//ボスの弾クラス
class CEnemyBullet : public CObjectX
{
public:

	//定数
	static const std::string FILEPATH;				//パス
	static constexpr float COLLISION_RADIUS{10.0f};	//当たり判定の半径

	//メンバ関数
	CEnemyBullet(int nPriority = 3);				//コンストラクタ
	~CEnemyBullet() override;						//デストラクタ
	HRESULT Init() override;						//初期化
	void Uninit() override;							//終了
	void Update() override;							//更新
	void Draw() override;							//描画
	static CEnemyBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);	//生成

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
	void Reflection();	//反射処理

	//撃たれたか
	void SetShooting(bool shooting) { m_bShooting = shooting; }	//設定
	bool GetShooting() { return m_bShooting; }					//取得

	//当たり判定
	CCollision* GetCollision() { return m_Collision; }		//取得

private:

	//メンバ変数
	D3DXVECTOR3 m_Move;			//移動量
	float m_fSizeRate;			///サイズ倍率
	bool m_bReflection;			//反射したか
	bool m_bShooting;			//撃たれたか
	CCollision* m_Collision;	//当たり判定
};

#endif