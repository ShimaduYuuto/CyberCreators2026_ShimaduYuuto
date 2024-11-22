////======================================
////
////	通常攻撃処理[normalattack000.cpp]
////	Author : Yuuto Shimadu
////
////======================================
//
////ヘッダーのインクルード
//#include "normalattack000.h"
//#include "normalattack001.h"
//#include "manager.h"
//#include "game.h"
//
////============================
////初期化
////============================
//HRESULT CNormalAttack000::Init()
//{
//	CContinuousAttack::Init();
//
//	return S_OK;
//}
//
////============================
////キャンセル時の処理
////============================
//void CNormalAttack000::Cancel()
//{
//	//左クリックをしたら
//	if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_LEFT))
//	{
//		//次の攻撃の生成
//		SetNextAction(new CNormalAttack001());
//
//		//アクションの終了判定
//		SetEndAction(true);
//	}
//}