//======================================
//
//	リザルトの処理[result.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "result.h"
#include "manager.h"
#include "result_bg.h"
#include "sky.h"
#include "model.h"
#include "cleartime.h"
#include "oldpaper.h"
#include "rank.h"
#include "result_txtui.h"
#include "camera_result.h"

//定数
const D3DXVECTOR3 CResult::TIME_POS = { SCREEN_WIDTH * 0.4f, 355.0f, 0.0f };

//============================
//リザルトのコンストラクタ
//============================
CResult::CResult() :
	m_pField(nullptr)
{
	
}

//============================
//リザルトのデストラクタ
//============================
CResult::~CResult()
{
	//フォグの設定
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
}

//============================
//リザルトの初期化
//============================
HRESULT CResult::Init()
{
	//フィールドの生成
	if (m_pField == nullptr)
	{
		m_pField = CField::Create({ 0.0f, 0.0f, 0.0f });
	}

	//クリアタイムの初期化
	CClearTime::GetInstance()->SetPos(TIME_POS);
	CClearTime::GetInstance()->Init();

	//その他のオブジェクト
	CSky::Create();
	CModel::Create({ 0.0f, 0.0f, 3.0f }, { 0.0f, D3DX_PI * 0.5f, 0.0f }, CModel::MODEL_TYPE_FENCE);
	COldPaper::Create();
	CRank::Create();
	CResult_Txtui::Create();

	//フォグの設定
	LPDIRECT3DDEVICE9 pDevice; //デバイスへのポインタ
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);					//有効
	pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP);		//フォグモードの設定
	pDevice->SetRenderState(D3DRS_FOGCOLOR, D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.1f));	//色の設定
	float m_fFogDensity = 0.0005f;
	pDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&m_fFogDensity));

	//BGM
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_RESULT);

	//カメラを切り替え
	CManager::GetInstance()->ChangeCamera(new CCamera_Result());
	
	return S_OK;
}

//============================
//リザルトの終了処理
//============================
void CResult::Uninit()
{
	//フィールドの破棄
	if (m_pField != nullptr)
	{
		m_pField = nullptr;
	}

	//終了処理
	CScene::Uninit();
}

//============================
//リザルトの更新処理
//============================
void CResult::Update()
{
	//マネージャーのインスタンスを取得
	CManager* pManager = CManager::GetInstance();

	//フェードが終わっていたら更新
	if (CManager::GetInstance()->GetFade()->GetEnd())
	{
		//エンターで画面遷移
		if (pManager->GetKeyboard()->GetTrigger(DIK_RETURN) || pManager->GetJoypad()->GetPress(CInputJoypad::JOYKEY_A) || pManager->GetJoypad()->GetPress(CInputJoypad::JOYKEY_START))
		{
			//タイトルに画面遷移
			pManager->GetFade()->SetFade(CScene::MODE_TITLE);
		}
	}
}

//============================
//リザルトの描画処理
//============================
void CResult::Draw()
{

}