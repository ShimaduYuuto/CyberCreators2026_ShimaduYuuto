//================================
//
//animation.cppに必要な宣言[animation.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _ANIMATION_H_ //このマクロ定義がされていなかったら
#define _ANIMATION_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"

//アニメーションクラス
class CAnimation
{
public:

	//テクスチャ情報の構造体
	struct TextureInfo
	{
		int nVertical = 0;		//縦の分割数
		int nHorizontal = 0;	//横の分割数
		int nUpdateSpeed = 0;	//アニメーションの速度
		bool bLoop = false;		//ループするか
	};

	//テクスチャカウントの構造体
	struct TextureCount
	{
		int nVerticalAnimCount = 0;		//縦のカウント
		int nHorizontalAnimCount = 0;	//横のカウント
		int nFrameCount = 0;			//フレームのカウント
	};

	//メンバ関数
	CAnimation();			//コンストラクタ
	~CAnimation();			//デストラクタ

	//更新
	D3DXVECTOR2 UpdateAnim();	//UV座標の更新

	//テクスチャ情報
	void SetTextureInfo(TextureInfo info) { m_TextureInfo = info; }	//設定
	TextureInfo& GetTextureInfo() { return m_TextureInfo; }			//取得

	//テクスチャカウント
	TextureCount& GetTextureCount() { return m_TextureCount; }

	//終了判定
	bool GetEnd() { return m_bEnd; }		//終了

private:

	void UpdateCnt();	//カウントの更新

	TextureInfo m_TextureInfo;	//テクスチャの情報
	TextureCount m_TextureCount;//テクスチャのカウント
	bool m_bEnd;				//終了判定
};

#endif