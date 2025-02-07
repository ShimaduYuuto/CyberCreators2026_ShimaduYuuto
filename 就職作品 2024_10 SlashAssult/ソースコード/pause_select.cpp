//======================================
//
//	ポーズの選択肢の処理[pause_select.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "pause_select.h"
#include "select_continue.h"
#include "select_restart.h"
#include "select_title.h"

//サイズ
const D3DXVECTOR3 CPause_Select::SIZE = { 400.0f, 100.0f, 0.0f };

//============================
//コンストラクタ
//============================
CPause_Select::CPause_Select(int nPriority) : CObject2D(nPriority)
{

}

//============================
//デストラクタ
//============================
CPause_Select::~CPause_Select()
{

}

//============================
//初期化
//============================
HRESULT CPause_Select::Init()
{
	//初期化
	CObject2D::Init();

	SetPos({ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f });
	SetSize(SIZE);

	return S_OK;
}

//============================
//終了処理
//============================
void CPause_Select::Uninit()
{
	CObject2D::Uninit();
}

//============================
//更新
//============================
void CPause_Select::Update()
{
	//更新処理
	CObject2D::Update();
}

//============================
//決定時の処理
//============================
void CPause_Select::Decision()
{

}

//============================
//描画
//============================
void CPause_Select::Draw()
{
	//描画処理
	CObject2D::Draw();
}

//============================
//クリエイト
//============================
CPause_Select* CPause_Select::Create(CHOICE choice, D3DXVECTOR3 pos)
{
	//ポインタ用の変数
	CPause_Select* pPause_Select = nullptr;

	switch (choice)
	{
	case CHOICE_CONTINUE:
		pPause_Select = new CSelect_Continue();
		break;

	case CHOICE_RESTART:
		pPause_Select = new CSelect_Restart();
		break;

	case CHOICE_TITLE:
		pPause_Select = new CSelect_Title();
		break;
	}

	//初期化
	pPause_Select->Init();
	pPause_Select->SetPos(pos);

	return pPause_Select;
}