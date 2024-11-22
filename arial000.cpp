////======================================
////
////	打ち上げ攻撃処理[arial000.cpp]
////	Author : Yuuto Shimadu
////
////======================================
//
////ヘッダーのインクルード
//#include "arial000.h"
//#include "arial001.h"
//#include "player.h"
//#include "manager.h"
//
////============================
////コンストラクタ
////============================
//CArial000::CArial000()
//{
//
//}
//
////============================
////デストラクタ
////============================
//CArial000::~CArial000()
//{
//
//}
//
////============================
////初期化
////============================
//HRESULT CArial000::Init()
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
//	pPlayer->SetMotion(CPlayer::PLAYERMOTION_ARIAL000);
//
//	return S_OK;
//}
//
////============================
////更新
////============================
//void CArial000::Update()
//{
//	//更新処理
//	CContinuousAttack::Update();
//}
//
////============================
////キャンセル時の処理
////============================
//void CArial000::Cancel()
//{
//	//左クリックをしたら
//	if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_LEFT))
//	{
//		SetNextAction(new CArial001());
//
//		//アクションの終了判定
//		SetEndAction(true);
//	}
//}