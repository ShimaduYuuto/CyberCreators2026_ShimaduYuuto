//======================================
//
//	演出の処理[direction_boss.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "direction_boss_destroy.h"
#include "manager.h"
#include "game.h"
#include "particle.h"

//定数
const D3DXVECTOR3 CDirection_Boss_Destroy::CAMERA_POSR = { 0.0f, 100.0f, 3500.0f };
const D3DXVECTOR3 CDirection_Boss_Destroy::CAMERA_POSV = { 0.0f, 100.0f, 3300.0f };

//============================
//演出のコンストラクタ
//============================
CDirection_Boss_Destroy::CDirection_Boss_Destroy() :
	m_fFadeAlpfa(0.0f),
	m_pDirectionFade(nullptr)
{
	//カメラの位置を固定
	CCamera* pCamera = CManager::GetInstance()->GetCamera();
	pCamera->SetPosR(CAMERA_POSR);
	pCamera->SetPosV(CAMERA_POSV);

	//終了時間
	SetEndTime(END_TIME);

	//演出用フェード
	m_pDirectionFade = new CObject2D(5);	//プライオリティを変更したいのでnew
	m_pDirectionFade->Init();
	m_pDirectionFade->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	m_pDirectionFade->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	m_pDirectionFade->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	//サウンド
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_DESTROY);
}

//============================
//演出のデストラクタ
//============================
CDirection_Boss_Destroy::~CDirection_Boss_Destroy()
{
	//フェードを破棄
	if (m_pDirectionFade != nullptr)
	{
		m_pDirectionFade = nullptr;
	}
}

//============================
//演出の初期化
//============================
HRESULT CDirection_Boss_Destroy::Init()
{
	return S_OK;
}

//============================
//演出の更新
//============================
bool CDirection_Boss_Destroy::TimeUpdate()
{
	//揺らす時間
	if (GetCount() == START_SHAKE_FRAME)
	{
		//カメラを揺らす
		CCamera* pCamera = CManager::GetInstance()->GetCamera();
		pCamera->SetShake(SHAKE_FRAME, SHAKE_MAGNITUDE);

		//サウンド
		CManager::GetInstance()->GetSound()->Stop(CSound::SOUND_LABEL_DESTROY);				//死亡SEを止める
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_EXPLOSION001);	//爆発SEを再生
	}

	//パーティクルを出す
	if (GetCount() >= START_SHAKE_FRAME)
	{
		CCamera* pCamera = CManager::GetInstance()->GetCamera();
		CParticle* pParticle = CParticle::Create(D3DXVECTOR3(pCamera->GetPosR()));
		float fRandom = CManager::GetInstance()->GetRundom(0, 628) * 0.01f;
		pParticle->SetMove(D3DXVECTOR3(sinf(fRandom) * 10.0f, cosf(fRandom) * 10.0f, 0.0f));
		pParticle->SetNormalSize(100.0f);
	}

	//演出用フェードの更新
	if (GetCount() >= START_SHAKE_FRAME && GetCount() < TIME_ENDFADE_FRAME)
	{
		//α値の更新
		m_fFadeAlpfa += 1.0f / (TIME_ENDFADE_FRAME - START_SHAKE_FRAME);
		if (m_fFadeAlpfa > 1.0f)
		{
			m_fFadeAlpfa = 1.0f;
		}

		//設定
		m_pDirectionFade->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fFadeAlpfa));
	}

	//ゲームを終わらせる時間
	if (GetCount() == TIME_ENDGAME_FRAME)
	{
		CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());
		pGame->SetClear(true);
	}

	//演出の更新
	return CDirection::TimeUpdate();
}

//============================
//パーティクルの生成
//============================
void CDirection_Boss_Destroy::CreateParticle()
{
	//変数宣言
	CCamera* pCamera = CManager::GetInstance()->GetCamera();					//カメラを取得
	CParticle* pParticle = CParticle::Create(D3DXVECTOR3(pCamera->GetPosR()));	//パーティクルの生成
	float fRandom = CManager::GetInstance()->GetRundom(0, 628) * 0.01f;			//ランダム値の算出(0.0f, 6.28f)

	//パラメータの設定
	pParticle->SetMove(D3DXVECTOR3(sinf(fRandom) * PARTICLE_SPEED, cosf(fRandom) * PARTICLE_SPEED, 0.0f));	//移動量の設定
	pParticle->SetNormalSize(PARTICLE_SIZE);																//通常サイズの設定
}