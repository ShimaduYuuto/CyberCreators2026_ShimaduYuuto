//======================================
//
//	敵シールドの処理[shield.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "shield.h"
#include "manager.h"
#include "game.h"
#include "character.h"

//============================
//コンストラクタ
//============================
CShield::CShield(int nPriority) : CModelparts(nPriority)
{

}

//============================
//デストラクタ
//============================
CShield::~CShield()
{

}

//============================
//初期化
//============================
HRESULT CShield::Init()
{
	//初期化
	CObjectX::Init();

	//Xファイルパーツの読み込み
	//位置(オフセット)の設定
	//向き(オフセット)の設定

	//パラメータの初期化
	CObjectX::SetRot({ 0.0f, 0.0f, 0.0f });
	CObjectX::SetPos({ 1.0f, 50.0f, 0.0f });

	return S_OK;
}

//============================
//終了処理
//============================
void CShield::Uninit()
{
	//初期化
	CObjectX::Uninit();
}

//============================
//更新
//============================
void CShield::Update()
{
	//ゲームオブジェクトの共通処理更新
	CObject::Update();
}

//============================
//描画
//============================
void CShield::Draw()
{
	//描画処理
	CModelparts::Draw(0, 0);
}

//============================
//クリエイト
//============================
CShield* CShield::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//種類に応じて動的確保
	CShield* pShield = NULL;

	//クリエイトの処理
	pShield = new CShield;

	//初期化
	pShield->Init();

	//パラメータの設定
	pShield->SetFilePath("data\\MODEL\\enemy011_shield.x");	//ファイル名
	pShield->SetPos(pos);									//位置
	pShield->SetRot(rot);									//向き

	//設定した情報を返す
	return pShield;
}