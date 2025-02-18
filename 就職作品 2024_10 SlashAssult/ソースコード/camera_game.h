//================================
//
//camera_game.cppに必要な宣言[camera_game.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _CAMERA_GAME_H_ //このマクロ定義がされていなかったら
#define _CAMERA_GAME_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"
#include "camera.h"

//ゲームカメラクラス
class CCamera_Game : public CCamera
{
public:

	//定数
	static constexpr float MOVE_RATE{ 0.1f };		//目的の注視点まで移動する距離の割合
	static constexpr float LENGTH_RATE{ 0.05f };		//距離を変化させる割合
	static constexpr float MOUSE_RATE{ 0.004f };	//マウスの移動量の反映倍率
	static constexpr float STICK_RATE{ 0.04f };		//スティックでの移動量の反映倍率

	//メンバ関数
	CCamera_Game();					//コンストラクタ
	~CCamera_Game() override;		//デストラクタ
	HRESULT Init() override;		//初期化
	void Uninit() override;			//終了
	void Update() override;			//更新
	//void SetCamera() override;	//カメラの設定

private:
	D3DXVECTOR3 m_GoalPosR;	//目的の注視点位置
};

#endif