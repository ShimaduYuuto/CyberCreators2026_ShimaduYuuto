////======================================
////
////	打ち上げ攻撃処理[arial002.cpp]
////	Author : Yuuto Shimadu
////
////======================================
//
////ヘッダーのインクルード
//#include "arial002.h"
//#include "manager.h"
//#include "game.h"
//#include "manager.h"
//
////============================
////コンストラクタ
////============================
//CArial002::CArial002()
//{
//
//}
//
////============================
////デストラクタ
////============================
//CArial002::~CArial002()
//{
//
//}
//
////============================
////初期化
////============================
//HRESULT CArial002::Init()
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
//	pPlayer->SetMotion(CPlayer::PLAYERMOTION_ARIAL002);
//
//	return S_OK;
//}
//
////============================
////更新
////============================
//void CArial002::Update()
//{
//	//更新処理
//	CContinuousAttack::Update();
//}