////======================================
////
////	通常攻撃処理[normalattack.cpp]
////	Author : Yuuto Shimadu
////
////======================================
//
////ヘッダーのインクルード
//#include "normalattack.h"
//#include "normalattack000.h"
//#include "normalattack001.h"
//#include "normalattack002.h"
//#include "manager.h"
//#include "game.h"
//
////定数
//const float CNormalAttack::VALUE_MOVE = 0.8f;
//
////============================
////コンストラクタ
////============================
//CNormalAttack::CNormalAttack()
//{
//
//}
//
////============================
////デストラクタ
////============================
//CNormalAttack::~CNormalAttack()
//{
//	
//}
//
////============================
////初期化
////============================
//HRESULT CNormalAttack::Init()
//{
//	return S_OK;
//}
//
////============================
////更新
////============================
//void CNormalAttack::Update()
//{
//	//更新
//	CContinuousAttack::Update();
//
//	//移動量を加算する時間
//	if (GetCount() < END_MOVE)
//	{
//		//ゲームシーンの取得
//		CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();
//
//		//移動量を加算
//		D3DXVECTOR3 Move = pGame->GetGamePlayer()->GetMove();
//		D3DXVECTOR3 Rot = pGame->GetGamePlayer()->GetRot();
//
//		//計算して加算
//		Move += { sinf(Rot.y + D3DX_PI) * VALUE_MOVE, 0.0f, cosf(Rot.y + D3DX_PI) * VALUE_MOVE };
//		pGame->GetGamePlayer()->SetMove(Move);
//	}
//}
//
////============================
////キャンセル時の処理
////============================
//void CNormalAttack::Cancel()
//{
//	
//}