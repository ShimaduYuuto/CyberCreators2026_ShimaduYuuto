//======================================
//
//	バトルエリアの処理[battlearea.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "battlearea.h"
#include "manager.h"
#include "game.h"
#include "battleareamanager.h"
#include "spawn_enemy.h"
#include "gimmick.h"

//============================
//コンストラクタ
//============================
CBattleArea::CBattleArea() :
	m_EnemyList(),
	m_fRadius(RADIUS),
	m_pWall(nullptr),
	m_Pos(),
	m_nEnemyNum(0),
	m_bEnd(false),
	m_bEnteredArea(false),
	m_Path()
{
	
}

//============================
//デストラクタ
//============================
CBattleArea::~CBattleArea()
{
	//壁に終了判定を渡す
	if (m_pWall != nullptr)
	{
		m_pWall->SetEnd(true);
		m_pWall =  nullptr;
	}

	//結界を消す
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();
	pGame->GetBarrierManager()->Erase();
}

//============================
//初期化
//============================
HRESULT CBattleArea::Init()
{
	return S_OK;
}

//============================
//終了処理
//============================
void CBattleArea::Uninit()
{
	m_bEnd = true;
}

//============================
//更新処理
//============================
void CBattleArea::Update()
{
	//すでにエリア内で敵が残っているなら抜ける
	if (m_bEnteredArea && m_nEnemyNum > 0)
	{
		return;
	}
	else if (m_bEnteredArea && m_nEnemyNum == 0)	//敵が全滅したいたら破棄
	{
		//BGMストップ
		CManager::GetInstance()->GetSound()->Stop(CSound::SOUND_LABEL_BATTLE);
		m_bEnd = true;
		return;
	}

	//ゲームシーンなら判定
	if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
	{
		//プレイヤーがエリアに入っているかを確認
		CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());
		D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();	//プレイヤー位置
		float fLength = sqrtf((PlayerPos.x - m_Pos.x) * (PlayerPos.x - m_Pos.x) + (PlayerPos.z - m_Pos.z) * (PlayerPos.z - m_Pos.z));	//xz平面の距離を算出

		//感知範囲内ならエリアを生成
		if (fLength < RADIUS_ENTEREDAREA)
		{
			//壁の生成
			if (m_pWall == nullptr)
			{
				m_pWall = CCollision_Wall::Create(m_Pos, m_fRadius);
			}

			//バトルエリアに入った
			m_bEnteredArea = true;
			CBattleAreaManager::GetInstance()->SetCurrentBattleArea(this);	//現在のエリアとして登録

			//ゲームの戦闘判定をfalseに変更
			pGame->SetBattle(true);

			//生成情報の読み込み
			SpawnLoad(m_Path.c_str());

			//BGMスタート
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_BATTLE);
		}
	}
}

//============================
//生成情報の読み込み
//============================
void CBattleArea::SpawnLoad(const char* path)
{
	if (path == nullptr) assert("バトルエリアのパスが見つかりませんでした");

	std::ifstream File(path);  // 読み込むファイルのパスを指定
	std::string line;

	if (!File)
	{// 種類毎の情報のデータファイルが開けなかった場合、
	 //処理を終了する
		return;
	}

	//無限に繰り返す
	while (1) 
	{
		//１文ごとに読み取る
		File >> line;

		//終わりを読み取ったらbreak
		if (line == "END_SCREPT") break;

		//敵情報の読み込み
		if (line == "ENEMYINFO")
		{
			CBattleArea::SpawnEnemy(File);
		}

		//ギミック情報の読み込み
		if (line == "GIMMICKINFO")
		{
			CBattleArea::SpawnGimmick(File);
		}
	}

	//ファイルを閉じる
	File.close();
}

//============================
//敵の生成
//============================
void CBattleArea::SpawnEnemy(std::ifstream& File)
{
	//読み取り用の変数
	std::string line;

	//無限に繰り返す
	while (1)
	{
		//１文ごとに読み取る
		File >> line;

		//終わりを読み取ったらbreak
		if (line == "END_ENEMYINFO") break;

		//敵情報の読み込み
		if (line == "ENEMY")
		{
			//読み取り用の変数
			D3DXVECTOR3 Pos = { VEC3_RESET_ZERO };
			int nType = NULL;

			//情報読み込み
			InfoLoad(File, "END_ENEMY", Pos, nType);

			//敵の生成
			CSpawn_Enemy::Create(GetPos() + Pos, static_cast<CEnemy::ENEMYTYPE>(nType));
		}
	}
}

//============================
//ギミックの生成
//============================
void CBattleArea::SpawnGimmick(std::ifstream& File)
{
	//読み取り用の変数
	std::string line;

	//無限に繰り返す
	while (1)
	{
		//１文ごとに読み取る
		File >> line;

		//終わりを読み取ったらbreak
		if (line == "END_GIMMICKINFO") break;

		//敵情報の読み込み
		if (line == "GIMMICK")
		{
			//読み取り用の変数
			D3DXVECTOR3 Pos = { VEC3_RESET_ZERO };
			int nType = NULL;

			//情報読み込み
			InfoLoad(File, "END_GIMMICK", Pos, nType);

			//ギミックの生成
			CGimmick::Create(GetPos() + Pos, static_cast<CGimmick::TYPE>(nType));
		}
	}
}

//============================
//情報の読み取り
//============================
void CBattleArea::InfoLoad(std::ifstream& File, const char* end, D3DXVECTOR3& pos, int& type)
{
	//読み取り用の変数
	std::string line;

	while (1)
	{
		//１文ごとに読み取る
		File >> line;

		//終わりを読み取ったらbreak
		if (line == end)
		{
			break;
		}

		//位置を読み取る
		if (line == "POS")
		{
			//位置情報を代入
			for (float& Coord : { std::ref(pos.x), std::ref(pos.y), std::ref(pos.z) })
			{
				File >> line;
				Coord = std::stof(line);
			}
		}

		//種類を読み取る
		if (line == "TYPE")
		{
			File >> line;
			type = std::stoi(line);
		}
	}
}

//============================
//生成処理
//============================
CBattleArea* CBattleArea::Create(D3DXVECTOR3 pos, const char* path)
{
	//ポインタ用の変数
	CBattleArea* pArea = new CBattleArea();

	//パラメータの代入
	pArea->m_Pos = pos;
	pArea->SetPath(path);

	//初期化
	pArea->Init();

	return pArea;
}