//================================
//
//battlearea.cppに必要な宣言[battlearea.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BATTLEAREA_H_ //このマクロ定義がされていなかったら
#define _BATTLEAREA_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "collision_wall.h"
#include "enemy.h"

//バトルエリアのクラス
class CBattleArea
{
public:

	static constexpr float RADIUS_ENTEREDAREA{ 150.0f };	//エリアに入ったかを感知する半径

	//メンバ関数
	CBattleArea();		//コンストラクタ
	~CBattleArea();		//デストラクタ
	HRESULT Init();		//初期化
	void Uninit();		//終了
	void Update();		//更新

	//生成
	static CBattleArea* Create(D3DXVECTOR3 pos);

	//ステージの壁
	CCollision_Wall* GetWall() { return m_pWall; }	//取得

	//敵の数を減らす
	void DecrementEnemyNum() { if (m_nEnemyNum > 0) { m_nEnemyNum--; } }

	//終了判定
	bool GetEnd() { return m_bEnd; }	//取得

private:

	//メンバ変数
	D3DXVECTOR3 m_StagePos;			//ステージ位置
	float m_fRadius;				//ステージの半径
	CCollision_Wall* m_pWall;		//ステージの壁
	std::list<CEnemy*> m_EnemyList;	//敵のリスト
	bool m_bEnteredArea;			//エリアに入ったか
	int m_nEnemyNum;				//敵の数
	bool m_bEnd;					//終了したか
};

#endif