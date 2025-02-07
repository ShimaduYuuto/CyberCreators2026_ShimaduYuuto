//======================================
//
//	シーンの処理[scene.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "scene.h"
#include "object.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "manager.h"

//静的メンバの初期化
CScene::MODE CScene::m_Mode = CScene::MODE_TITLE;	//タイトルに初期化

//============================
//シーンのコンストラクタ
//============================
CScene::CScene()
{
	
}

//============================
//シーンのデストラクタ
//============================
CScene::~CScene()
{

}

//============================
//シーンの初期化
//============================
HRESULT CScene::Init()
{
	
	return S_OK;
}

//============================
//シーンの終了処理
//============================
void CScene::Uninit()
{
	//全オブジェクトの開放
	CObject::ReleaseAll();

	//サウンドの停止
	CManager::GetInstance()->GetSound()->Stop();
}

//============================
//シーンの更新処理
//============================
void CScene::Update()
{
	
}

//============================
//シーンの描画処理
//============================
void CScene::Draw()
{
	
}

//============================
//読み込み
//============================
void CScene::Load()
{

}

//============================
//シーンの生成
//============================
CScene* CScene::Create(CScene::MODE mode)
{
	//消す用の変数
	CScene* pScene = nullptr;

	//モードの代入
	m_Mode = mode;

	//引数に応じて動的確保
	switch (mode)
	{
	case CScene::MODE_TITLE:	//タイトル
		pScene = new CTitle();
		break;

	case CScene::MODE_GAME:		//ゲーム
		pScene = new CGame();
		break;

	case CScene::MODE_RESULT:	//リザルト
		pScene = new CResult();
		break;
	}

	//メモリを確保していたら
	if (pScene != nullptr)
	{
		//初期化
		//pScene->Init();
		pScene->Load();

		return pScene;
	}

	return nullptr;

}