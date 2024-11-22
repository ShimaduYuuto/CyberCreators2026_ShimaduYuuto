////======================================
////
////	通常攻撃処理[normalattack_enemy000.cpp]
////	Author : Yuuto Shimadu
////
////======================================
//
////ヘッダーのインクルード
//#include "normalattack_enemy000.h"
//#include "enemy000.h"
//#include "manager.h"
//#include "game.h"
//
//const float CNormalAttack_Enemy000::ATTACK_RANGE = 30.0f;	//攻撃の範囲
//
////============================
////コンストラクタ
////============================
//CNormalAttack_Enemy000::CNormalAttack_Enemy000() :
//	m_fEndCount(0.0f),
//	m_bHit(false)
//{
//
//}
//
////============================
////デストラクタ
////============================
//CNormalAttack_Enemy000::~CNormalAttack_Enemy000()
//{
//
//}
//
////============================
////初期化
////============================
//HRESULT CNormalAttack_Enemy000::Init()
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
//void CNormalAttack_Enemy000::Update()
//{
//	//ゲームシーンの取得
//	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();
//
//	//当たり判定を始めるカウントになったら
//	if (m_fEndCount > START_COLLISION)
//	{
//		//ゲームシーンなら判定
//		if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
//		{
//			//当たっていないなら処理
//			if (!m_bHit)
//			{
//				//変数宣言
//				D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();	//プレイヤーの位置
//				D3DXVECTOR3 AttackRot = GetCharacter()->GetRot();			//攻撃の向き
//				D3DXVECTOR3 AttackPos = GetCharacter()->GetPos();			//攻撃の位置
//
//				//攻撃の位置を算出
//				AttackPos += D3DXVECTOR3(sinf(AttackRot.y + D3DX_PI) * 20.0f, 0.0f, cosf(AttackRot.y + D3DX_PI) * 20.0f);
//
//				//距離を計算
//				float fXZ = sqrtf((AttackPos.x - PlayerPos.x) * (AttackPos.x - PlayerPos.x) + (AttackPos.z - PlayerPos.z) * (AttackPos.z - PlayerPos.z)); //距離を算出する
//				float fXY = sqrtf((AttackPos.x - PlayerPos.x) * (AttackPos.x - PlayerPos.x) + (AttackPos.y - PlayerPos.y) * (AttackPos.y - PlayerPos.y)); //距離を算出する
//				float fLength = sqrtf(fXZ * fXZ + fXY * fXY);	//距離を算出
//
//				//攻撃の範囲内なら
//				if (fLength < ATTACK_RANGE)
//				{
//					//プレイヤーにダメージを与える
//					pGame->GetGamePlayer()->SetDamage(DAMAGE_VALUE);
//					m_bHit = true;
//				}
//			}
//		}
//	}
//
//	//カウントの更新
//	m_fEndCount += pGame->GetTime()->GetValue(1.0f);
//
//	//カウントが終了値になったら
//	if (END_TIME < m_fEndCount)
//	{
//		//アクションの終了判定
//		SetEndAction(true);
//	}
//}