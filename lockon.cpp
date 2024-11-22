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
	m_TargetPos()
{

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
	//消去処理
	delete this;
}

//============================
//更新
//============================
void CLockon::Update()
{
	//ゲームシーンなら判定
	if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
	{
		//ゲームシーンの取得
		CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

		//プレイヤーの位置を取得
		D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();

		//敵の周回
		for (auto& iter : pGame->GetEnemyManager()->GetList())
		{
			//敵の位置を取得
			D3DXVECTOR3 EnemyLength = iter->GetCollision()->GetPos() - PlayerPos;

			float fXZ = sqrtf(EnemyLength.x * EnemyLength.x + EnemyLength.z * EnemyLength.z); //距離を算出する
			float fXY = sqrtf(EnemyLength.x * EnemyLength.x + EnemyLength.y * EnemyLength.y); //距離を算出する
			float fLength = sqrtf(fXZ * fXZ + fXY * fXY);	//距離を算出

			//敵の判定内なら
			if (fLength < 300.0f)
			{
				bool bLock = false;

				//カメラに入っているかを確認
				bLock = CManager::GetInstance()->GetCamera()->GetViewObject(iter->GetCollision()->GetPos());

				/*if (bLock)
				{
					CManager::
				}*/
			}
		}

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