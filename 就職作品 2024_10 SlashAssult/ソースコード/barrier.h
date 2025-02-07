//================================
//
//barrier.cppに必要な宣言[barrier.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BARRIER_H_ //このマクロ定義がされていなかったら
#define _BARRIER_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "object3D.h"
#include "animation.h"

//結界のクラス
class CBarrier : public CObject3D
{
public:

	//定数
	static const std::string TEXTURE_PATH;	//テクスチャパス

	//テクスチャ情報
	static constexpr int HORIZONTAL{ 10 };	//横の分割数(U座標)
	static constexpr int VERTICAL{ 2 };		//縦の分割数(V座標)
	static constexpr int SPEED_UPDATE{ 3 };	//更新速度
	static constexpr bool LOOP{ true };		//ループ
	static const D3DXVECTOR3 SIZE;			//ポリゴンサイズ

	//メンバ関数
	CBarrier();					//コンストラクタ
	~CBarrier() override;		//デストラクタ
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	void Draw() override;		//描画

	//生成
	static CBarrier* Create(D3DXVECTOR3 pos);

private:
	CAnimation m_Anim;

};

#endif