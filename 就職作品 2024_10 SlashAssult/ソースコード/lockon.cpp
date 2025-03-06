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
	m_pTarget(nullptr),	//現在ターゲット対象のポインタ
	m_pMark(nullptr),	//印のポインタ
	m_LockonList(),		//ロックオン対象たちのリスト
	m_pRushUi(nullptr)	//ラッシュ可能のUIを表示するポインタ
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

	//印がないなら
	if (m_pMark == nullptr)
	{
		//リストにいないなら抜ける
		if (m_LockonList.size() == 0)
		{
			return;
		}

		//最初の敵を取得
		auto iter = m_LockonList.begin();
		m_pTarget = *iter;
		m_pMark = CLockonMark::Create(MARK_RADIUS, &m_pTarget->GetCollision()->GetPos());
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