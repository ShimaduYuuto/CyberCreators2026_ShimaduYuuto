//======================================
//
//	ラッシュチャンスのUIの描画[ui_gameguide.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "ui_gameguide.h"
#include "manager.h"
#include "game.h"

//定数
const std::string CUi_GameGuide::TEXTURE_PATH[CONTROLLER_MAX][GUIDE_MAX] =
{
	{//キーボードマウス
		{"data\\TEXTURE\\gameguide000.png"},
		{"data\\TEXTURE\\gameguide001.png"},
		{"data\\TEXTURE\\gameguide002.png"},
	},
	{//ジョイパッド
		{"data\\TEXTURE\\gameguide003.png"},
		{"data\\TEXTURE\\gameguide006.png"},
		{"data\\TEXTURE\\gameguide005.png"},
	}
};

//============================
//コンストラクタ
//============================
CUi_GameGuide::CUi_GameGuide(int nPriority) : CObject2D(nPriority),
	m_GuideType()
{
	
}

//============================
//デストラクタ
//============================
CUi_GameGuide::~CUi_GameGuide()
{

}

//============================
//初期化
//============================
HRESULT CUi_GameGuide::Init()
{
	CObject2D::Init();

	return S_OK;
}

//============================
//終了処理
//============================
void CUi_GameGuide::Uninit()
{
	CObject2D::Uninit();
}

//============================
//更新処理
//============================
void CUi_GameGuide::Update()
{
	
}

//============================
//描画処理
//============================
void CUi_GameGuide::Draw()
{
	//ゲームシーンの取得
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//演出中なら描画しない
	if (pGame->GetDirectioning())
	{
		return;
	}

	//テクスチャ描画
	CObject2D::Draw(TEXTURE_PATH[pGame->GetControllerUIType()][m_GuideType].c_str());
}

//============================
//生成処理
//============================
CUi_GameGuide* CUi_GameGuide::Create(D3DXVECTOR3 pos, GUIDE type, D3DXVECTOR3 size)
{
	//ポインタ用の変数
	CUi_GameGuide* pObject;

	//メモリの確保
	pObject = new CUi_GameGuide();

	//初期化
	pObject->Init();									//初期化
	pObject->SetPos(pos);								//位置
	pObject->SetSize(size);	//サイズ
	pObject->m_GuideType = type;

	return pObject;
}