//=============================================
//
//実用的な処理をまとめたもの[useful.h]
//Auther Matsuda Towa?
//
//=============================================

//２重インクルード防止
#ifndef _USEFUL_H_ //これが定義されてないとき
#define _USEFUL_H_

#include "main.h"

//当たり判定系
bool JudgeBallCollision(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float length);	//円の当たり判定(位置、位置、判定する長さ)

//計算系
float Ratio(float value, float max);	//割合を算出

//0初期化用
#define INT_ZERO (0)
#define FLOAT_ZERO (0.0f)

//カラー初期化
#define COLOR_RESET_ZERO (D3DXVECTOR3(0.0f,0.0f,0.0f,0.0f))
#define COLOR_RESET_ONE (D3DXVECTOR3(1.0f,1.0f,1.0f,1.0f))

//頂点3D初期化
#define VEC3_RESET_ZERO (D3DXVECTOR3(0.0f,0.0f,0.0f))
#define VEC3_RESET_ONE (D3DXVECTOR3(1.0f,1.0f,1.0f))

//頂点2D初期化
#define VEC2_RESET_ZERO (D3DXVECTOR2(0.0f,0.0f))
#define VEC2_RESET_ONE (D3DXVECTOR2(1.0f,1.0f))

//半円
#define HALF_PI	(D3DX_PI * 0.5f)
//1/4円
#define QRTR_PI	(D3DX_PI * 0.25f)

//自動開放
template<class T>
constexpr void SafeDelete(T& p)
{
	if (p == nullptr) { return; }
	delete p;
	p = nullptr;
}

//汎用的なキー操作の判定
bool TriggerUp();		//上を押したか
bool TriggerDown();		//下を押したか
bool TriggerRight();	//右を押したか
bool TriggerLeft();		//左を押したか
bool TriggerDecision();	//決定ボタンを押したか

//２点の角度の差を算出
float CheckAngleDiff(float angle0, float angle1);

//上限値と下限値をそれぞれ比べる
//template<typename T>
//T Clamp(T x, T low, T high)
//{
//	assert(low <= high);
//	return std::min(std::max(x, low), high);
//}

#endif