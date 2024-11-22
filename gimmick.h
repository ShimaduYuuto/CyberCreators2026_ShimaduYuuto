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

	//定数
	static const std::string FILEPATH;

	//メンバ関数
	CGimmick(int nPriority = 3);	//コンストラクタ
	~CGimmick() override;			//デストラクタ
	HRESULT Init() override;		//初期化
	void Uninit() override;			//終了
	void Update() override;			//更新

	//コリジョンインスタンス
	void SetCollision(CCollision* colision) { m_Collision = colision; }
	CCollision* GetCollision() { return m_Collision; }

private:

	//メンバ変数
	CCollision* m_Collision;
};

#endif