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
#include "explodingbarrel.h"

//============================
//コンストラクタ
//============================
CBattleArea::CBattleArea() :
	m_EnemyList(),
	m_fRadius(500.0f),
	m_pWall(nullptr),
	m_Pos(),
	m_nEnemyNum(0),
	m_bEnd(false),
	m_bEnteredArea(false)
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

			//エネミーの生成
			SpawnEnemy();

			//ギミックの生成
			SpawnGimmick();

			//BGMスタート
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_BATTLE);
		}
	}
}

//============================
//敵の生成
//============================
void CBattleArea::SpawnEnemy()
{

}

//============================
//ギミックの生成
//============================
void CBattleArea::SpawnGimmick()
{
	
}

//============================
//生成処理
//============================
CBattleArea* CBattleArea::Create(D3DXVECTOR3 pos, CBattleArea* area)
{
	//ポインタ用の変数
	CBattleArea* pArea = nullptr;
	pArea = area;

	//パラメータの代入
	pArea->m_Pos = pos;

	//初期化
	pArea->Init();

	return pArea;
}