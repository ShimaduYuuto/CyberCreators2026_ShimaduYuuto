////======================================
////
////	打ち上げ攻撃処理[smash.cpp]
////	Author : Yuuto Shimadu
////
////======================================
//
////ヘッダーのインクルード
//#include "smash.h"
//#include "manager.h"
//#include "game.h"
//#include "object.h"
//#include "enemy.h"
//#include "player.h"
//#include "gauge_slow.h"
//
////============================
////コンストラクタ
////============================
//CSmash::CSmash() :
//	m_pImpact(),
//	m_bHit(false),
//	m_nDelayCount(0),
//	m_bAttack(false),
//	m_nSlowTime(0)
//{
//
//}
//
////============================
////デストラクタ
////============================
//CSmash::~CSmash()
//{
//	//インパクトの範囲がnullなら
//	if (m_pImpact != nullptr)
//	{
//		//生成
//		m_pImpact->Uninit();
//		m_pImpact = nullptr;
//	}
//}
//
////============================
////初期化
////============================
//HRESULT CSmash::Init()
//{
//	//ゲームシーンのプレイヤーの位置を取得
//	CGame* pGame = nullptr;
//	pGame = (CGame*)CManager::GetInstance()->GetScene();	//ゲームシーンの取得
//	D3DXVECTOR3 Pos = pGame->GetGamePlayer()->GetPos();		//位置の取得
//
//	m_pImpact = CImpactRange::Create(Pos);
//	return S_OK;
//}
//
////============================
////更新
////============================
//void CSmash::Update()
//{
//	//ゲームシーンのプレイヤーの位置を取得
//	CGame* pGame = nullptr;
//	pGame = (CGame*)CManager::GetInstance()->GetScene();	//ゲームシーンの取得
//	D3DXVECTOR3 Pos = pGame->GetGamePlayer()->GetPos();		//位置の取得
//
//	//攻撃をしていなかったら
//	if (!m_bAttack)
//	{
//		//右ボタンを離したら当たり判定を確認
//		if (CManager::GetInstance()->GetMouse()->GetRerease(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_RIGHT))
//		{
//			//変数の宣言
//			CObject* pObj = nullptr;
//
//			//プライオリティの数だけ周回
//			for (int i = 0; i < CObject::NUM_PRIORITY; i++)
//			{
//				pObj = CObject::GetTopObject(i);	//先頭取得
//
//				//最大数が不明なのでwhileを使用
//				while (pObj != nullptr)
//				{
//					CObject* pNext = pObj->GetNext();	//次のポインタを取得
//
//					//種類の確認
//					if (pObj->GetType() == CObject::TYPE_ENEMY)	//敵なら
//					{
//						//敵の種類
//						CEnemy* pEnemy = (CEnemy*)pObj;	//敵の取得
//
//						//位置の取得
//						D3DXVECTOR3 Pos = m_pImpact->GetPos();
//						D3DXVECTOR3 EnemyPos = pEnemy->GetPos();
//
//						//距離を計算
//						float fLength = sqrtf((EnemyPos.x - Pos.x) * (EnemyPos.x - Pos.x) + (EnemyPos.z - Pos.z) * (EnemyPos.z - Pos.z));
//
//						//範囲内の確認
//						if (fLength < m_pImpact->GetSize().x * m_pImpact->GetRate() * 0.5f)
//						{
//							//吹き飛び処理
//							if (pEnemy->SetBlowOff())
//							{
//								m_nSlowTime += ADD_SLOWTIME; //	スロー時間の追加
//
//								//フラグがオフならオンにする
//								if (!m_bHit)
//								{
//									m_bHit = true;
//								}
//							}
//						}
//					}
//
//					pObj = pNext;	//ポインタを進める
//				}
//			}
//
//			//インパクトの範囲がnullなら
//			if (m_pImpact != nullptr)
//			{
//				//生成
//				m_pImpact->Uninit();
//				m_pImpact = nullptr;
//			}
//
//			//攻撃判定をオン
//			m_bAttack = true;
//			CManager::GetInstance()->GetCamera()->SetShake(15, 15);	//ヒット時カメラを揺らす
//		}
//	}
//
//	//攻撃をしたら
//	if (m_bAttack)
//	{
//		//カウントの加算
//		m_nDelayCount++;
//
//		//遅延のカウントが指定値になったら
//		if (m_nDelayCount >= DELAY_TIME)
//		{
//			//当たっていたらカウント
//			if (m_bHit)
//			{
//				//遅延のカウントが指定値になったら
//				if (m_nDelayCount >= DELAY_TIME)
//				{
//					//アクションの終了判定
//					SetEndAction(true);
//
//					//ゲームシーンのプレイヤーの位置を取得
//					CGame* pGame = nullptr;
//					pGame = (CGame*)CManager::GetInstance()->GetScene();	//ゲームシーンの取得
//					pGame->GetTime()->SetStateTimer(pGame->GetTime()->TIME_SLOW, m_nSlowTime);	//時間の状態を設定
//					CGauge_Slow::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.8f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.05f, 0.0f), m_nSlowTime);
//				}
//			}
//			else
//			{
//				//アクションの終了判定
//				SetEndAction(true);
//			}
//		}
//	}
//
//	//インパクトの範囲がnullなら
//	if (m_pImpact != nullptr)
//	{
//		//位置の更新
//		m_pImpact->SetPos(Pos);
//	}
//}