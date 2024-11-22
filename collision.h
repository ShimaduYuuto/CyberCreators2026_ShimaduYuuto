//================================
//
//collision.cppに必要な宣言[collision.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _COLLISION_H_ //このマクロ定義がされていなかったら
#define _COLLISION_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"
#include "collision_view.h"

//コリジョンクラス
class CCollision
{
public:

	//メンバ関数
	CCollision();	//コンストラクタ
	~CCollision();	//デストラクタ
	HRESULT Init();	//初期化
	void Uninit();	//終了処理
	void Update(D3DXVECTOR3 offsetpos);	//更新処理

	//生成
	static CCollision* Create(float radius, D3DXVECTOR3 collisionpos);	//コリジョンの生成

	//当たり判定のローカル位置
	void SetCollisionPos(D3DXVECTOR3 pos) { m_CollisionPos = pos; }	//設定
	D3DXVECTOR3& GetCollisionPos() { return m_CollisionPos; }		//取得

	//当たり判定のワールド位置
	D3DXVECTOR3& GetPos() { return m_Pos; }					//取得

	//当たり判定の半径
	void SetRadius(float radius) { m_fRadius = radius; }	//設定
	float GetRadius() { return m_fRadius; }					//取得

private:
	float m_fRadius;			//半径
	D3DXVECTOR3 m_Pos;			//ワールド位置
	D3DXVECTOR3 m_CollisionPos;	//ローカル位置

	//デバッグ用
	CCollision_View* m_pCollisionView;	//当たり判定の可視化
};

#endif