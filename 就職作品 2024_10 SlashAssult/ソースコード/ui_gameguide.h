//================================
//
//ui_gameguide.cppに必要な宣言[ui_gameguide.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _UI_GAMEGUIDE_H_ //このマクロ定義がされていなかったら
#define _UI_GAMEGUIDE_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "object2D.h"
#include "animation.h"

//ゲームのUIクラス
class CUi_GameGuide : public CObject2D
{
public:

	//ガイドUIの種類
	typedef enum
	{
		GUIDE_ATTACK = 0,
		GUIDE_GUARD,
		GUIDE_DASH,
		GUIDE_MAX,
	}GUIDE;

	//コントローラの種類
	typedef enum
	{
		CONTROLLER_KEYBOARDMAUSE = 0,
		CONTROLLER_JOYPAD,
		CONTROLLER_MAX,
	}CONTROLLER;

	//定数
	static const std::string TEXTURE_PATH[CONTROLLER_MAX][GUIDE_MAX];	//テクスチャパス

	//メンバ関数
	CUi_GameGuide(int nPriority = 3);		//コンストラクタ
	~CUi_GameGuide() override;				//デストラクタ
	HRESULT Init() override;				//初期化
	void Uninit() override;					//終了
	void Update() override;					//更新
	void Draw() override;					//描画

	//生成
	static CUi_GameGuide* Create(D3DXVECTOR3 pos, GUIDE type, D3DXVECTOR3 size);

private:

	GUIDE m_GuideType;	//種類
	
};

#endif