//================================
//
//collision_wall.cppに必要な宣言[collision_wall.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _COLLISION_WALL_H_ //このマクロ定義がされていなかったら
#define _COLLISION_WALL_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "objectcylinder.h"

//コリジョンウォールクラス
class CCollision_Wall : public CObjectCylinder
{
public:

	//定数の宣言
	static const std::string FILEPATH;	//読み込むファイル
	static const int NUM_CORNER;		//円柱の数
	static const float HEIGHT;			//高さ
	static constexpr float ADD_ALPHA{ 0.03f };	//加算するα値

	//メンバ関数
	CCollision_Wall(int nPriority = 3);		//コンストラクタ
	~CCollision_Wall() override;			//デストラクタ
	HRESULT Init() override;				//初期化
	void Uninit() override;					//終了
	void Update() override;					//更新
	void Draw() override;					//描画

	//当たり判定を返す
	bool GetHit(D3DXVECTOR3& pos, float radius);

	//終了判定
	void SetEnd(bool end) { m_bEnd = end; }	//設定

	//生成
	static CCollision_Wall* Create(D3DXVECTOR3 pos, float radius);

private:
	float m_fAlpha;	//α値
	bool m_bEnd;	//終了か
};

#endif