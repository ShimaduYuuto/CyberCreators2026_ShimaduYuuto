//================================
//
//状態に応じた処理を実行[state.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "state.h"

//====================================
//モーションの処理
//====================================
void CState::Motion(CCharacter* character)
{
	//モーションの更新
	character->UpdateMotion();
}