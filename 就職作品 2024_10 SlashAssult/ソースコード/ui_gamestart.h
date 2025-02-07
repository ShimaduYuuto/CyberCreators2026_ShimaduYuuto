//================================
//
//ui_gamestart.cppに必要な宣言[ui_gamestart.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _UI_GAMESTART_H_ //このマクロ定義がされていなかったら
#define _UI_GAMESTART_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "object2D.h"

//gamestartのUIクラス
class CUi_GameStart : public CObject2D
{
public:

	//定数
	static constexpr float ADD_ALPHA{ 0.025f };	//一度に加える値

	//定数
	static const std::string TEXTURE_PATH;	//パス
	static constexpr float WIDTH{ 400.0f };	//横幅
	static constexpr float HEIGHT{ 50.0f };//高さ
	static const D3DXVECTOR3 POS;			//位置

	//メンバ関数
	CUi_GameStart(int nPriority = 3);	//コンストラクタ
	~CUi_GameStart() override;		//デストラクタ
	HRESULT Init() override;		//初期化
	void Uninit() override;			//終了
	void Update() override;			//更新
	void Draw() override;			//描画
	static CUi_GameStart* Create();	//生成

private:
	float m_fCurrentAlpha;
	float m_fAddAlpha;
};

#endif