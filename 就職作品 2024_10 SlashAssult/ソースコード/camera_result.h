//================================
//
//camera_game.cppに必要な宣言[camera_game.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _CAMERA_RESULT_H_ //このマクロ定義がされていなかったら
#define _CAMERA_RESULT_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"
#include "camera.h"

//リザルトカメラクラス
class CCamera_Result : public CCamera
{
public:

	//定数
	static const D3DXVECTOR3 POSV;	//視点
	static const D3DXVECTOR3 POSR;	//注視点

	//メンバ関数
	CCamera_Result();			//コンストラクタ
	~CCamera_Result() override;	//デストラクタ
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
};

#endif