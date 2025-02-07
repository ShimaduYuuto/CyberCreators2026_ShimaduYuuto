//======================================
//
//	爆発樽の処理[explodingbarrel.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "explodingbarrel.h"
#include "explosion.h"
#include "manager.h"

//定数
const std::string CExplodingBarrel::FILEPATH = "data\\MODEL\\ExplodingBarrel000.x";

//============================
//コンストラクタ
//============================
CExplodingBarrel::CExplodingBarrel(int nPriority) : CGimmick(nPriority),
	m_bDetonation(false)
{

}

//============================
//デストラクタ
//============================
CExplodingBarrel::~CExplodingBarrel()
{
	
}

//============================
//初期化
//============================
HRESULT CExplodingBarrel::Init()
{
	//初期化
	CGimmick::Init();

	GetCollision()->SetRadius(SIZE_RADIUS);

	return S_OK;
}

//============================
//終了処理
//============================
void CExplodingBarrel::Uninit()
{
	//終了処理
	CGimmick::Uninit();
}

//============================
//更新
//============================
void CExplodingBarrel::Update()
{
	//死んでいたら抜ける
	if (CObject::GetDeath())
	{
		return;
	}

	//ゲームオブジェクトの共通処理更新
	CGimmick::Update();
}

//============================
//描画
//============================
void CExplodingBarrel::Draw()
{
	//オブジェクトの描画
	CObjectX::Draw(FILEPATH.c_str());
}

//============================
//クリエイト
//============================
CExplodingBarrel* CExplodingBarrel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//種類に応じて動的確保
	CExplodingBarrel* pExplodingBarrel = NULL;

	//クリエイトの処理
	pExplodingBarrel = new CExplodingBarrel;

	//初期化
	pExplodingBarrel->Init();

	//パラメータの設定
	pExplodingBarrel->SetPos(pos);		//位置
	pExplodingBarrel->SetRot(rot);		//向き

	//設定した情報を返す
	return pExplodingBarrel;
}

//============================
//ギミック作動処理
//============================
void CExplodingBarrel::GimmickActivation()
{
	//起爆
	SetDetonation();
}

//============================
//起爆設定
//============================
void CExplodingBarrel::SetDetonation()
{
	if (m_bDetonation)
	{
		return;
	}

	//フラグを立てる
	m_bDetonation = true;

	//爆発の生成
	CExplosion::Create(GetPos());

	//終了処理
	Uninit();
}