//======================================
//
//	当たり判定の位置[collision.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "collision.h"
#include "useful.h"

//============================
//コンストラクタ
//============================
CCollision::CCollision() : 
	m_CollisionPos(VEC3_RESET_ZERO),		//ローカル位置
	m_fRadius(FLOAT_ZERO),					//半径
	m_Pos(VEC3_RESET_ZERO),					//親の位置
	m_pCollisionView(nullptr)				//コリジョンの可視化
{

}

//============================
//デストラクタ
//============================
CCollision::~CCollision()
{

}

//============================
//初期化
//============================
HRESULT CCollision::Init()
{
#if _DEBUG
	//当たり判定の可視化
	m_pCollisionView = CCollision_View::Create(m_fRadius, &m_Pos);
#endif

	return S_OK;
}

//============================
//終了処理
//============================
void CCollision::Uninit()
{

#if _DEBUG
	//当たり判定可視化の消去
	if (m_pCollisionView != nullptr)
	{
		m_pCollisionView->Uninit();
		m_pCollisionView = nullptr;
	}
#endif

	//消去処理
	delete this;
}

//============================
//更新処理
//============================
void CCollision::Update(D3DXVECTOR3 offsetpos)
{
	//位置を算出
	m_Pos = offsetpos + m_CollisionPos;

	//デバック時に範囲を表示
#if _DEBUG
	m_pCollisionView->SetSize({ m_fRadius * 2.0f, m_fRadius * 2.0f, 0.0f });
	m_pCollisionView->Update();
#endif
}

//============================
//クリエイト
//============================
CCollision* CCollision::Create(float radius, D3DXVECTOR3 collisionpos)
{
	//ポインタ用の変数
	CCollision* pCollision = nullptr;
	pCollision = new CCollision;

	//パラメータの代入
	pCollision->m_fRadius = radius;				//半径
	pCollision->m_CollisionPos = collisionpos;	//ローカル位置

	//初期化
	pCollision->Init();

	return pCollision;
}