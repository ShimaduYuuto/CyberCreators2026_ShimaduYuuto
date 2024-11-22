////======================================
////
////	シールド再生処理[spawn_shield.cpp]
////	Author : Yuuto Shimadu
////
////======================================
//
////ヘッダーのインクルード
//#include "spawn_shield.h"
//#include "enemy000.h"
//#include "manager.h"
//#include "game.h"
//
////============================
////コンストラクタ
////============================
//CSpawn_Shield::CSpawn_Shield() :
//	m_nEndCount(0)
//{
//
//}
//
////============================
////デストラクタ
////============================
//CSpawn_Shield::~CSpawn_Shield()
//{
//
//}
//
////============================
////初期化
////============================
//HRESULT CSpawn_Shield::Init()
//{
//	//アクションの開始判定
//	SetEndAction(false);
//	GetCharacter()->SetMotion(CEnemy000::ENEMY000MOTION_ACTION);
//
//	return S_OK;
//}
//
////============================
////更新
////============================
//void CSpawn_Shield::Update()
//{
//	//当たり判定を始めるカウントになったら
//	if (m_nEndCount > SPAWN_TIME)
//	{
//		//ゲームシーンなら判定
//		if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
//		{
//			
//		}
//	}
//
//	//カウントの更新
//	m_nEndCount++;
//
//	//カウントが終了値になったら
//	if (END_TIME < m_nEndCount)
//	{
//		//アクションの終了判定
//		SetEndAction(true);
//	}
//}