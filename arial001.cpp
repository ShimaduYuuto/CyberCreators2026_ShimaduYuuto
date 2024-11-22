////======================================
////
////	打ち上げ攻撃処理[arial001.cpp]
////	Author : Yuuto Shimadu
////
////======================================
//
////ヘッダーのインクルード
//#include "arial001.h"
//#include "arial002.h"
//#include "manager.h"
//#include "game.h"
//#include "manager.h"
//
////============================
////コンストラクタ
////============================
//CArial001::CArial001()
//{
//
//}
//
////============================
////デストラクタ
////============================
//CArial001::~CArial001()
//{
//
//}
//
////============================
////初期化
////============================
//HRESULT CArial001::Init()
//{
//	//初期化
//	CContinuousAttack::Init();
//
//	//パラメータの設定
//	CArial::SetCancelTime(START_CANCELTIME);	//キャンセル
//	CArial::SetEndTime(END_TIME);				//終了時間
//	CArial::SetCollisionTime(START_COLLISION);	//当たり判定
//
//	//モーションの設定
//	CCharacter* pPlayer = GetCharacter();
//	pPlayer->SetMotion(CPlayer::PLAYERMOTION_ARIAL001);
//
//	return S_OK;
//}
//
////============================
////更新
////============================
//void CArial001::Update()
//{
//	//更新処理
//	CContinuousAttack::Update();
//}
//
////============================
////キャンセル時の処理
////============================
//void CArial001::Cancel()
//{
//	//左クリックをしたら
//	if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_LEFT))
//	{
//		//次のアクションの設定
//		SetNextAction(new CArial002());
//
//		//アクションの終了判定
//		SetEndAction(true);
//	}
//}