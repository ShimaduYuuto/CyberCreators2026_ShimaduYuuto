//================================
//
//camera_title.cppに必要な宣言[camera_title.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _CAMERA_TITLE_H_ //このマクロ定義がされていなかったら
#define _CAMERA_TITLE_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"
#include "camera.h"

//タイトルカメラクラス
class CCamera_Title : public CCamera
{
public:

	//メンバ関数
	CCamera_Title();			//コンストラクタ
	~CCamera_Title() override;	//デストラクタ
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
	//void SetCamera() override;//カメラの設定


};

#endif