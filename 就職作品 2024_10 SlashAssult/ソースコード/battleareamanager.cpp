//======================================
//
//	バトルエリアの管理処理[battleareamanager.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "battleareamanager.h"
#include "game.h"
#include "manager.h"

//============================
//コンストラクタ
//============================
CBattleAreaManager::CBattleAreaManager() :
	m_BattleAreaList(),
	m_pCurrentBattleArea(nullptr)
{
	//リストの初期化
	m_BattleAreaList.clear();
}

//============================
//デストラクタ
//============================
CBattleAreaManager::~CBattleAreaManager()
{
	//リストの初期化
	m_BattleAreaList.clear();
}

//============================
//初期化
//============================
HRESULT CBattleAreaManager::Init()
{
	//読み込み
	Load();

	return S_OK;
}

//============================
//終了処理
//============================
void CBattleAreaManager::Uninit()
{
	//リストのクリア
	m_BattleAreaList.clear();
	m_pCurrentBattleArea = nullptr;
}

//============================
//更新
//============================
void CBattleAreaManager::Update()
{
	//リストのエリアを更新
	for (auto itr : m_BattleAreaList)
	{
		itr->Update();	//更新
		
		//死亡判定が立っていたら消去
		if (itr->GetEnd())
		{
			itr->Uninit();
		}
	}

	//エリアの終了確認
	if (m_pCurrentBattleArea != nullptr)
	{
		if (m_pCurrentBattleArea->GetEnd())
		{
			//リストから削除
			Erase(m_pCurrentBattleArea);
		}
	}
}

//============================
//読み込み
//============================
void CBattleAreaManager::Load()
{
	m_BattleAreaList.clear();

	std::ifstream File("data\\FILE\\battleareaInfo.txt");	//読み込むファイルのパスを指定
	std::string String;										//読み取り用

	if (!File) return;	//読み込みに失敗したら抜ける

	//無限に繰り返す
	while (1)
	{
		//１文ごとに読み取る
		File >> String;

		//終わりを読み取ったらbreak
		if (String == "END_SCREPT") break;

		//バトルエリアの読み込み
		if (String == "BATTLEAREA")
		{
			LoadBattleArea(File);
		}
	}

	//ファイルを閉じる
	File.close();
}

//============================
//バトルエリアの読み込み
//============================
void CBattleAreaManager::LoadBattleArea(std::ifstream& File)
{
	//読み取り用の変数
	std::string String;
	D3DXVECTOR3 Pos = { VEC3_RESET_ZERO };
	std::string Path;

	//無限に繰り返す
	while (1)
	{
		//１文ごとに読み取る
		File >> String;

		//終わりを読み取ったらbreak
		if (String == "END_BATTLEAREA")
		{
			Regist(CBattleArea::Create(Pos, Path.c_str()));	//登録
			break;
		}

		//位置の読み込み
		if (String == "POS")
		{
			//位置情報を代入
			for (float& Coord : { std::ref(Pos.x), std::ref(Pos.y), std::ref(Pos.z) })
			{
				File >> String;
				Coord = std::stof(String);
			}
		}

		//パスの読み込み
		if (String == "PATH")
		{
			File >> String;
			Path = String;
		}
	}
}

//============================
//登録処理
//============================
void CBattleAreaManager::Regist(CBattleArea* area)
{
	//登録済みか
	bool bRegisted = false;

	//同じものが無いかを確認
	for (auto itr : m_BattleAreaList)
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
	m_BattleAreaList.push_back(area);
}

//============================
//削除処理
//============================
void CBattleAreaManager::Erase(CBattleArea* area)
{
	//サイズが0なら抜ける
	if (m_BattleAreaList.size() == 0)
	{
		return;
	}

	//登録済みか
	bool bRegisted = false;

	//同じものが無いかを確認
	for (auto itr : m_BattleAreaList)
	{
		if (itr == area)
		{
			bRegisted = true;
			break;
		}
	}

	//登録されていないなら抜ける
	if (!bRegisted)
	{
		return;
	}

	//現在のエリアならnullptrにする
	if (m_pCurrentBattleArea == area)
	{
		delete m_pCurrentBattleArea;
		m_pCurrentBattleArea = nullptr;

		//ゲームの戦闘判定をfalseに変更
		CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());
		pGame->SetBattle(false);
	}

	//エリアの情報を削除
	m_BattleAreaList.remove(area);
}