//================================
//
//animation.cppに必要な宣言[animation.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _FOG_H_ //このマクロ定義がされていなかったら
#define _FOG_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"

//フォグクラス
class CFog
{
private:

	//メンバ関数
	CFog();		//コンストラクタ

public:

	//メンバ関数
	~CFog();		//デストラクタ

	//インスタンスの生成
	static CFog* GetInstance()
	{
		static CFog instance;	//静的インスタンス
		return &instance;
	}

	//フォグの設定
	void SetFog();		//フォグを設定
	void ClearFog();	//フォグを解除
	void SetColor(D3DXCOLOR color) { m_Color = color; }			//フォグの色を設定
	void SetDensity(float density) { m_fDensity = density; }	//フォグの密度を設定

private:

	//定数
	static const D3DXCOLOR DEFAULT_COLOR;					//デフォルトの色
	static constexpr float DEFAULT_DENDITY{ 0.0005f };		//デフォルトの密度

	//変数
	D3DXCOLOR m_Color;		//フォグの色
	float m_fDensity;		//フォグの密度
	
};

#endif