//=============================================
//
//実用的な処理をまとめたもの[useful.cpp]
//Auther Matsuda Towa?
//
//=============================================

//ヘッダーのインクルード
#include "useful.h"
#include "manager.h"

//=============================================
//円の当たり判定
//=============================================
bool JudgeBallCollision(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float length)
{
    D3DXVECTOR3 Vector = { 0.0f, 0.0f, 0.0f };     //ベクトル
    float fDistance = 0.0f; //距離
    bool bHit = false;      //当たっているか

    //２点間の距離を計算
    D3DXVec3Subtract(&Vector, &pos2, &pos1);

    // 差分ベクトルの長さ（距離）を計算
    fDistance = static_cast<float>(D3DXVec3Length(&Vector));

    //引数の範囲以下なら当たっている
    if (fDistance <= length)
    {
        bHit = true;
    }

    return bHit;
}

//==================================================================
//計算系
//==================================================================

//=============================================
//割合を算出
//=============================================
float Ratio(float value, float max)
{
    return value / max;
}

//=============================================
//角度差を算出
//=============================================
float CheckAngleDiff(float angle0, float angle1)
{
    //変数宣言
    float InterpolationAngle = angle0 - angle1;

    if (InterpolationAngle > D3DX_PI)
    {
        InterpolationAngle = (-D3DX_PI - angle1) + -(D3DX_PI - InterpolationAngle);
    }
    else if (InterpolationAngle < -D3DX_PI)
    {
        InterpolationAngle = (D3DX_PI - angle1) + (D3DX_PI + InterpolationAngle);
    }

    //絶対値を返す
    return std::abs(InterpolationAngle);
}

//=============================================
//二点の距離を算出
//=============================================
float Vector3Distance(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1)
{
    //変数宣言
    D3DXVECTOR3 Vec3Distance = pos1 - pos0; //２点のベクトル
    float fDistance = 0.0f;                 //距離

    //距離を算出
    fDistance = D3DXVec3Length(&Vec3Distance);

    //距離を返す
    return fDistance; 
}

//==================================================================
//判定系
//==================================================================

//============================
//上を押したか
//============================
bool TriggerUp()
{
    if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_UP)) return true;					//キーボード
    if (CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_UP)) return true;		//ジョイパッド

    return false;
}

//============================
//下を押したか
//============================
bool TriggerDown()
{
    if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_DOWN)) return true;					//キーボード
    if (CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_DOWN)) return true;	//ジョイパッド

    return false;
}

//============================
//右を押したか
//============================
bool TriggerRight()
{
    if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RIGHT)) return true;					//キーボード
    if (CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_RIGHT)) return true;	//ジョイパッド

    return false;
}

//============================
//左を押したか
//============================
bool TriggerLeft()
{
    if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_LEFT)) return true;					//キーボード
    if (CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_LEFT)) return true;	//ジョイパッド

    return false;
}

//============================
//決定ボタンを押したか
//============================
bool TriggerDecision()
{
    if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_RETURN)) return true;				//キーボード
    if (CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_A)) return true;		//ジョイパッド

    return false;
}