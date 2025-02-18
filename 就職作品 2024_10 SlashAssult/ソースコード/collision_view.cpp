//======================================
//
//	当たり判定の位置の可視化[collision_view.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "collision_view.h"
#include "manager.h"

//定数
const std::string CCollision_View::TEXTURE_PATH = "data\\TEXTURE\\circle000.png";

//============================
//コンストラクタ
//============================
CCollision_View::CCollision_View() :
	m_fRadius(),	//半径
	m_Pos()			//位置
{

}

//============================
//デストラクタ
//============================
CCollision_View::~CCollision_View()
{

}

//============================
//初期化
//============================
HRESULT CCollision_View::Init()
{
	CObjectBillboard::Init();

	return S_OK;
}

//============================
//終了処理
//============================
void CCollision_View::Uninit()
{
	CObjectBillboard::Uninit();
}

//============================
//更新処理
//============================
void CCollision_View::Update()
{
	//位置の設定
	SetPos(*m_Pos);
	CObjectBillboard::Update();
}

//============================
//描画処理
//============================
void CCollision_View::Draw()
{
	CObjectBillboard::Draw(TEXTURE_PATH.c_str());
}

//============================
//クリエイト
//============================
CCollision_View* CCollision_View::Create(float radius, D3DXVECTOR3* pos)
{
	//ポインタ用の変数
	CCollision_View* pCollision_View = nullptr;
	pCollision_View = new CCollision_View;

	//初期化
	pCollision_View->Init();

	//パラメータの代入
	pCollision_View->m_fRadius = radius;
	pCollision_View->m_Pos = pos;
	pCollision_View->SetSize(D3DXVECTOR3(radius * 2.0f, radius * 2.0f, 0.0f));
	pCollision_View->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));

	return pCollision_View;
}