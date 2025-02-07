//======================================
//
//	ギミックの処理[gimmick.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "gimmick.h"
#include "manager.h"
#include "game.h"
#include "explodingbarrel.h"

//定数
const D3DXVECTOR3 CGimmick::COLLISION_POS = { 0.0f, 30.0f, 0.0f };

//============================
//コンストラクタ
//============================
CGimmick::CGimmick(int nPriority) : CObjectX(nPriority),
	m_Collision(nullptr)
{
	//ゲームシーンの取得
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

	//マネージャーに登録
	pGame->GetGimmickManager()->Regist(this);

	//ゲームタグを設定
	SetTag(CObject::TAG_GAME);
}

//============================
//デストラクタ
//============================
CGimmick::~CGimmick()
{
	//ゲームシーンの取得
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

	//マネージャーから削除
	if (pGame->GetGimmickManager() != nullptr)
	{
		pGame->GetGimmickManager()->Erase(this);
	}	

	//当たり判定の消去
	if (m_Collision != nullptr)
	{
		m_Collision->Uninit();
		m_Collision = nullptr;
	}
}

//============================
//初期化
//============================
HRESULT CGimmick::Init()
{
	//初期化
	CObjectX::Init();

	//当たり判定の生成
	if (m_Collision == nullptr)
	{
		m_Collision = CCollision::Create(COLLISION_RADIUS, COLLISION_POS);
	}

	return S_OK;
}

//============================
//終了処理
//============================
void CGimmick::Uninit()
{
	//初期化
	CObjectX::Uninit();
}

//============================
//更新
//============================
void CGimmick::Update()
{
	//ゲームオブジェクトの共通処理更新
	CObjectX::Update();
	m_Collision->Update(GetPos());
}

//============================
//生成処理
//============================
CGimmick* CGimmick::Create(D3DXVECTOR3 pos, TYPE type)
{
	CGimmick* pGimmick = nullptr;

	//種類に応じて派生
	switch (type)
	{
	case TYPE::TYPE_EXPLODINGBARREL:
		pGimmick = new CExplodingBarrel();
		break;

	default:
		assert("範囲外のギミック種類です");
	}

	//パラメータの設定
	pGimmick->Init();		//初期化
	pGimmick->SetPos(pos);	//位置の設定

	return pGimmick;
}