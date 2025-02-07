//================================
//
//gimmick.cppに必要な宣言[gimmick.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _GIMMICK_H_ //このマクロ定義がされていなかったら
#define _GIMMICK_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "objectX.h"
#include "collision.h"

//ギミッククラス
class CGimmick : public CObjectX
{
public:

	//ギミックの種類
	enum TYPE
	{
		TYPE_EXPLODINGBARREL = 0,
		TYPE_MAX
	};

	//定数
	static const std::string FILEPATH;
	static constexpr float COLLISION_RADIUS{ 20.0f };	//コリジョンの半径
	static const D3DXVECTOR3 COLLISION_POS;				//コリジョンの位置

	//メンバ関数
	CGimmick(int nPriority = 3);	//コンストラクタ
	~CGimmick() override;			//デストラクタ
	HRESULT Init() override;		//初期化
	void Uninit() override;			//終了
	void Update() override;			//更新
	static CGimmick* Create(D3DXVECTOR3 pos, TYPE type);

	//コリジョンインスタンス
	void SetCollision(CCollision* colision) { m_Collision = colision; }
	CCollision* GetCollision() { return m_Collision; }

	//ヒット時の処理
	virtual void GimmickActivation() {}

private:

	//メンバ変数
	CCollision* m_Collision;
};

#endif