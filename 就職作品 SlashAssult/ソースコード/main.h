//================================
//
//main.cppに必要な宣言[main.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _MAIN_H_ //このマクロ定義がされていなかったら
#define _MAIN_H_ //２重インクルード防止のマクロ定義

//マクロ定義
#define SCREEN_WIDTH (1280)	//ウィンドウの幅
#define SCREEN_HEIGHT (720)	//ウィンドウの高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define CLASS_NAME "WindowClass" //ウィンドウクラスの名前

//汎用的なコードをまとめたヘッダー
#include "useful.h"

//頂点情報[2D]の構造体定義
typedef struct
{
	D3DXVECTOR3 pos; //頂点座標
	float rhw;		//座標変換用係数(1.0fで固定)
	D3DCOLOR col;	//頂点カラー
	D3DXVECTOR2 tex;//テクスチャ座標
}VERTEX_2D;

//頂点情報[3D]の構造体定義
typedef struct
{
	D3DXVECTOR3 pos; //頂点座標
	D3DXVECTOR3 nor; //法線ベクトル
	D3DCOLOR col;	 //頂点カラー
	D3DXVECTOR2 tex; //テクスチャ座標
}VERTEX_3D;

#endif

