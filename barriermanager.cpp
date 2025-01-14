//======================================
//
//	結界の処理[barriermanager.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "barriermanager.h"
#include "game.h"
#include "manager.h"

//============================
//コンストラクタ
//============================
CBarrierManager::CBarrierManager()
{
	m_BarrierList.clear();
}

//============================
//デストラクタ
//============================
CBarrierManager::~CBarrierManager()
{
	m_BarrierList.clear();
}

//============================
//初期化
//============================
HRESULT CBarrierManager::Init()
{
	//読み込み
	Load();
	return S_OK;
}

//============================
//終了処理
//============================
void CBarrierManager::Uninit()
{
	m_BarrierList.clear();
}

//============================
//更新
//============================
void CBarrierManager::Update()
{
	//リストのエリアを更新
	for (auto itr : m_BarrierList)
	{
		itr->Update();	//更新
	}
}

//============================
//読み込み
//============================
void CBarrierManager::Load()
{
	m_BarrierList.clear();

	// ファイルの読み込み
	FILE* pFile = fopen("data\\FILE\\barrier.txt", "r");

	if (pFile == NULL)
	{// 種類毎の情報のデータファイルが開けなかった場合、
	 //処理を終了する
		return;
	}

	char aDataSearch[256];		// データ検索用

	// ENDが見つかるまで読み込みを繰り返す
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch);	// 検索

		if (!strcmp(aDataSearch, "END"))
		{// 読み込みを終了
			fclose(pFile);
			break;
		}

		if (aDataSearch[0] == '#')
		{// 折り返す
			continue;
		}

		//位置情報を見つけたらその位置に生成
		if (!strcmp(aDataSearch, "POS"))
		{
			D3DXVECTOR3 Pos = { 0.0f, 0.0f, 0.0f };

			fscanf(pFile, "%f", &Pos.x);
			fscanf(pFile, "%f", &Pos.y);
			fscanf(pFile, "%f", &Pos.z);

			Regist(CBarrier::Create(Pos));
		}
	}
}

//============================
//登録処理
//============================
void CBarrierManager::Regist(CBarrier* area)
{
	//登録済みか
	bool bRegisted = false;

	//同じものが無いかを確認
	for (auto itr : m_BarrierList)
	{
		if (itr == area)
		{
			bRegisted = true;
			break;
		}
	}

	//登録済みなら抜ける
	if (bRegisted)
	{
		return;
	}

	//敵の情報を登録
	m_BarrierList.push_back(area);
}

//============================
//削除処理
//============================
void CBarrierManager::Erase()
{
	//サイズが0なら抜ける
	if (m_BarrierList.size() == 0)
	{
		return;
	}

	//登録済みか
	bool bRegisted = false;

	//登録されていないなら抜ける
	if (!bRegisted)
	{
		//return;
	}

	//エリアの情報を削除
	m_BarrierList.front()->Uninit();
	m_BarrierList.pop_front();
}