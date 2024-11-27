//======================================
//
//	ロックオン処理[lockon.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "lockon.h"
#include "camera.h"
#include "manager.h"
#include "game.h"

//============================
//コンストラクタ
//============================
CLockon::CLockon() : 
	m_pTarget(nullptr),
	m_pMark(nullptr),
	m_LockonList()
{
	m_LockonList.clear();
}

//============================
//デストラクタ
//============================
CLockon::~CLockon()
{

}

//============================
//初期化
//============================
HRESULT CLockon::Init()
{
	return S_OK;
}

//============================
//終了処理
//============================
void CLockon::Uninit()
{
	//マークを生成
	if (m_pMark != nullptr)
	{
		m_pMark->Uninit();
		m_pMark = nullptr;
	}

	//消去処理
	delete this;
}

//============================
//更新
//============================
void CLockon::Update()
{
	//ロックオン対象が画面内に存在するかを確認
	if (m_pMark != nullptr)
	{
		//いなかったら破棄
		if (!CManager::GetInstance()->GetCamera()->GetViewObject(m_pMark->GetPos()))
		{
			//印と対象のポインタを破棄
			m_pMark->Uninit();
			m_pMark = nullptr;
			m_pTarget = nullptr;
		}
		else
		{
			return;
		}
	}

	if (m_pMark == nullptr)
	{
		//ゲームシーンなら判定
		//if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
		//{
		//	//ゲームシーンの取得
		//	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

		//	//プレイヤーの位置を取得
		//	D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();

		//	//敵の周回
		//	for (auto& iter : pGame->GetEnemyManager()->GetList())
		//	{
		//		//敵の位置を取得
		//		D3DXVECTOR3 EnemyLength = iter->GetCollision()->GetPos() - PlayerPos;

		//		float fXZ = sqrtf(EnemyLength.x * EnemyLength.x + EnemyLength.z * EnemyLength.z); //距離を算出する
		//		float fXY = sqrtf(EnemyLength.x * EnemyLength.x + EnemyLength.y * EnemyLength.y); //距離を算出する
		//		float fLength = sqrtf(fXZ * fXZ + fXY * fXY);	//距離を算出

		//		//敵の判定内なら
		//		if (fLength < 300.0f)
		//		{
		//			bool bLock = false;

		//			//カメラに入っているかを確認
		//			bLock = CManager::GetInstance()->GetCamera()->GetViewObject(iter->GetCollision()->GetPos());

		//			//ロックオンできたら
		//			if (bLock)
		//			{
		//				//マークを生成
		//				m_pMark = CLockonMark::Create(30.0f, &iter->GetCollision()->GetPos());
		//				m_pTarget = iter;	//ターゲットのポインタ
		//				break;
		//			}
		//		}
		//	}

		//}

		//リストにいないなら抜ける
		if (m_LockonList.size() == 0)
		{
			return;
		}

		//最初の敵を取得
		auto iter = m_LockonList.begin();
		m_pTarget = *iter;
		m_pMark = CLockonMark::Create(30.0f, &m_pTarget->GetCollision()->GetPos());
	}
}

//============================
//クリエイト
//============================
CLockon* CLockon::Create()
{
	//ポインタ用の変数
	CLockon* pLockon = nullptr;

	//生成
	pLockon = new CLockon;

	//初期化
	pLockon->Init();

	return pLockon;
}

//============================
//登録
//============================
void CLockon::Regist(CEnemy* enemy)
{
	//変数宣言
	bool bRegist = false;

	//敵の周回
	for (auto& iter : m_LockonList)
	{
		//すでに登録しているなら登録しない
		if (iter == enemy)
		{
			bRegist = true;
			break;
		}
	}

	//登録していないなら登録
	if (!bRegist)
	{
		m_LockonList.push_back(enemy);
	}
}

//============================
//削除
//============================
void CLockon::Erase(CEnemy* enemy)
{
	//敵の周回
	for (auto& iter : m_LockonList)
	{
		//すでに登録しているなら登録しない
		if (iter == enemy)
		{
			//敵の情報を削除
			if (m_pTarget == enemy)
			{
				m_pTarget = nullptr;
				m_pMark->Uninit();
				m_pMark = nullptr;
			}
			m_LockonList.remove(iter);
			break;
		}
	}
}