////======================================
////
////	通常攻撃処理[normalattack001.cpp]
////	Author : Yuuto Shimadu
////
////======================================
//
////ヘッダーのインクルード
//#include "normalattack001.h"
//#include "normalattack002.h"
//#include "manager.h"
//#include "game.h"
//#include "smash.h"
//
////============================
////初期化
////============================
//HRESULT CNormalAttack001::Init()
//{
//	//モーションの設定
//	CCharacter* pPlayer = GetCharacter();
//	pPlayer->SetMotion(CPlayer::PLAYERMOTION_ACTION001);
//
//	CContinuousAttack::Init();
//
//	return S_OK;
//}
//
////============================
////キャンセル時の処理
////============================
//void CNormalAttack001::Cancel()
//{
//	//左クリックをしたら
//	if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_LEFT))
//	{
//		//次の攻撃の生成
//		SetNextAction(new CNormalAttack002());
//
//		//アクションの終了判定
//		SetEndAction(true);
//	}
//	else if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_RIGHT))
//	{
//		//次の攻撃の生成
//		SetNextAction(new CSmash());
//
//		//アクションの終了判定
//		SetEndAction(true);
//	}
//}