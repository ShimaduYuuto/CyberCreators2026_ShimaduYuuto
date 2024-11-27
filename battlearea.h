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

	//バトルステージ情報
	struct BattleInfo
	{
		D3DXVECTOR3 StagePos;			//ステージ位置
		float fRadius;					//ステージの半径
		CCollision_Wall* pWall;			//ステージの壁
		std::list<CEnemy*> EnemyList;	//敵のリスト
	};

	//メンバ関数
	CBattleArea();		//コンストラクタ
	~CBattleArea();		//デストラクタ
	HRESULT Init();		//初期化
	void Uninit();		//終了

private:

	//メンバ変数
	std::list<BattleInfo*> m_apArea;	//エリアを管理
};

#endif