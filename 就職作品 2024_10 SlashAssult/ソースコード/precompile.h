//================================
//
//precompile.cppに必要な宣言[precompile.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _PRECOMPILE_H_ //このマクロ定義がされていなかったら
#define _PRECOMPILE_H_ //２重インクルード防止のマクロ定義

#include <windows.h>
#include"d3dx9.h"	//描画処理に必要
#define DIRECTINPUT_VERSION (0x0800) //ビルド時の警告対処用マクロ
#include "dinput.h" //入力処理に必要
#include "Xinput.h" //ジョイパッド処理に必要
#include "xaudio2.h" //サウンド処理に必要

//ライブラリのリンク
#pragma comment(lib, "d3d9.lib")	//描画処理に必要
#pragma comment(lib, "d3dx9.lib")	//[d3d9.lib]の拡張ライブラリ
#pragma comment(lib, "dxguid.lib")	//DirectXコンポーネント（部品）使用に必要
#pragma comment(lib,"winmm.lib")	//システム時刻取得に必要
#pragma comment(lib, "dinput8.lib")//入力処理に必要
#pragma comment(lib, "xinput.lib") //ジョイパッド処理に必要

//C++用関数のインクルード
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <list>
#include <random>
#include <fstream>

//システム系のインクルード
#include <assert.h>

#endif