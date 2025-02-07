//================================
//
//direction_boss.cppに必要な宣言[direction_boss.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _DIRECTION_BOSS_H_ //このマクロ定義がされていなかったら
#define _DIRECTION_BOSS_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "direction.h"

//演出クラス
class CDirection_Boss : public CDirection
{
public:

	//演出
	static constexpr int END_TIME{ 300 };	//終了時間

	//カメラ
	static const D3DXVECTOR3 CAMERA_POSV;				//カメラ注視点の位置
	static const D3DXVECTOR3 CAMERA_POSR;				//カメラ視点の位置
	static constexpr int START_SHAKE_FRAME{ 250 };		//揺らし始める時間
	static constexpr int SHAKE_FRAME{ 55 };				//揺らす時間
	static constexpr float SHAKE_MAGNITUDE{ 20.0f };	//揺らす値

	//メンバ関数
	CDirection_Boss();	//コンストラクタ
	~CDirection_Boss();	//デストラクタ

	//基本処理
	HRESULT Init() override;	//初期化
	bool TimeUpdate() override;	//更新

private:

};

#endif