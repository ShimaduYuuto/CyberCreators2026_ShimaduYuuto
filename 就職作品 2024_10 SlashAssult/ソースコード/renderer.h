//================================
//
//renderer.cppに必要な宣言[renderer.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _RENDERER_H_ //このマクロ定義がされていなかったら
#define _RENDERER_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"

//レンダラークラス
class CRenderer
{
public:
	CRenderer();								//コンストラクタ
	~CRenderer();								//デストラクタ
	HRESULT Init(HWND hWnd, BOOL bWindow);		//初期化
	void Uninit();								//終了
	void Update();								//更新
	void Draw();								//描画
	LPDIRECT3DDEVICE9 GetDevice();				//３Dデバイスの取得
private:
	LPDIRECT3D9 m_pD3D;							//Direct3D
	LPDIRECT3DDEVICE9 m_pD3DDevice;				//Direct3Dデバイス
};

#endif