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

	//定数
	static const D3DXVECTOR3 POSV;	//視点
	static const D3DXVECTOR3 POSR;	//注視点

	//メンバ関数
	CCamera_Title();			//コンストラクタ
	~CCamera_Title() override;	//デストラクタ
	HRESULT Init() override;	//初期化
	void Uninit() override;		//終了
	void Update() override;		//更新
};

#endif