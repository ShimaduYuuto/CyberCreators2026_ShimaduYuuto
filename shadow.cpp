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
	m_quat(),
	m_mtxRot(),
	m_fValueRor(),
	m_vecAxis()
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
	D3DXVECTOR3 Pos = *m_TargetPos;				//ターゲットの位置を取得
	D3DXVECTOR3 Rot = GetRot();					//向き
	D3DXVECTOR3 QuotRot = {0.0f, 1.0f, 0.0f};	//クォータニオンの向き
	D3DXVECTOR3 CameraRot = { 0.0f, 0.0f, 0.0f };//カメラの向き
	D3DXVECTOR3 normalizedNormal;

	Pos.y = 0.01f;		//高さだけ変更

	//ゲームシーンならフィールドの高さに位置を補正
	if (CManager::GetInstance()->GetScene()->GetMode() == CScene::MODE_GAME)
	{
		CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();
		pGame->GetGameField()->MeshCollision(Pos, Rot);
		//Rot.x *= -1.0f;
		Pos.y += 1.0f;												//埋まらないように少しだけ高くする
		Rot.y = 0.0f;
		normalizedNormal *= D3DX_PI;
		//Rot.x = normalizedNormal.x/* + D3DX_PI * 0.5f*/;
		//Rot.z = normalizedNormal.z/* + D3DX_PI * 0.5f*/;
	}

	//クォータニオンの設定
	//m_vecAxis = QuotRot;
	//m_fValueRor = acos(D3DXVec3Dot(&CameraRot, &m_vecAxis));
	
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
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//減算処理の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//Zの比較方法変更
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

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
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//Zバッファに書き込む
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//フォグの設定
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	//位置の取得
	//D3DXVECTOR3 Pos = GetPos();

	////テクスチャの読み込み
	//CTexture* pTexture = CManager::GetInstance()->GetTexture();

	//D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
	//LPDIRECT3DDEVICE9 pDevice;

	////デバイスの取得
	//pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	////ワールドの初期化
	//D3DXMatrixIdentity(&GetMtx());

	////クォータニオンの初期化
	//m_quat = { 0.0f, 0.0f, 0.0f, 1.0f };

	//D3DXQuaternionRotationAxis(&m_quat, &m_vecAxis, m_fValueRor);   // クォータニオン作成
	//D3DXMatrixRotationQuaternion(&m_mtxRot, &m_quat);

	////向きを反映
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, m_polygon.rot.y, m_polygon.rot.x, m_polygon.rot.z);

	//D3DXMatrixMultiply(&GetMtx(), &GetMtx(), &mtxRot);

	////位置を反映
	//D3DXMatrixTranslation(&mtxTrans, Pos.x, Pos.y, Pos.z);

	//D3DXMatrixMultiply(&GetMtx(), &GetMtx(), &mtxTrans);

	////ワールドマトリックスの設定
	//pDevice->SetTransform(D3DTS_WORLD, &GetMtx());

	////頂点バッファをデータストリームに設定
	//pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	////頂点フォーマットの設定
	//pDevice->SetFVF(FVF_VERTEX_3D);

	////テクスチャの設定
	//pDevice->SetTexture(0, pTexture->GetAddress(pTexture->Regist(texturepath)));

	////ポリゴンの描画
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	////位置の設定
	//SetPos(Pos);
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