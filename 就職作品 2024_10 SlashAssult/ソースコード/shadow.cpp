//======================================
//
//	空の処理[shadow.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "shadow.h"
#include "game.h"
#include "manager.h"

//定数
const std::string CShadow::FILEPATH = "data\\TEXTURE\\effect000.jpg";
const D3DXCOLOR CShadow::COLOR = { 1.0f, 1.0f, 1.0f, 0.5f };

//============================
//コンストラクタ
//============================
CShadow::CShadow(int nPriority) : CObject3D(nPriority),
	m_TargetPos(),
	m_bDrawJudge(true)
{

}

//============================
//デストラクタ
//============================
CShadow::~CShadow()
{
	//ポインタをnull
	if (m_TargetPos != nullptr)
	{
		m_TargetPos = nullptr;
	}
}

//============================
//初期化
//============================
HRESULT CShadow::Init()
{
	//初期化
	CObject3D::Init();

	return S_OK;
}

//============================
//終了処理
//============================
void CShadow::Uninit()
{
	//終了処理
	CObject3D::Uninit();
}

//============================
//更新
//============================
void CShadow::Update()
{
	//位置の更新
	D3DXVECTOR3 Pos = *m_TargetPos;		//ターゲットの位置を取得
	D3DXVECTOR3 Rot = GetRot();			//向き

	Pos.y = 0.01f;		//高さだけ変更

	//ゲームシーンならフィールドの高さに位置を補正
	if (CManager::GetInstance()->GetScene()->GetMode() == CScene::MODE_GAME)
	{
		CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();
		pGame->GetGameField()->MeshCollision(Pos, Rot);
		Pos.y += 1.0f;												//埋まらないように少しだけ高くする
	}

	//位置と向きを設定
	SetPos(Pos);
	SetRot(Rot);

	CObject3D::Update();
}

//============================
//描画
//============================
void CShadow::Draw()
{
	//描画しない判定なら抜ける
	if (!m_bDrawJudge) return;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//減算処理の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//Zの比較方法変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//Zバッファに書き込まない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//フォグの設定
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	//オブジェクトの描画
	CObject3D::Draw(FILEPATH.c_str());

	//減算処理の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//Zの比較方法変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//Zバッファに書き込む
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//フォグの設定
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
}

//============================
//クリエイト
//============================
CShadow* CShadow::Create(D3DXVECTOR3* pos, float radius)
{
	//種類に応じて動的確保
	CShadow* pShadow = nullptr;

	//クリエイトの処理
	pShadow = new CShadow;

	//初期化
	pShadow->Init();

	pShadow->SetSize(D3DXVECTOR3(radius * 2.0f, 0.0f, radius * 2.0f), CObject3D::TYPE_FLOOR);	//サイズ
	pShadow->SetRate(1.0f);												//サイズ倍率
	pShadow->SetPos(D3DXVECTOR3(pos->x, 1.0f, pos->z));					//位置
	pShadow->m_TargetPos = pos;											//対象の位置
	pShadow->SetColor(COLOR);											//色の設定

	//設定した情報を返す
	return pShadow;
}