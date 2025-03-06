//======================================
//
//	壁の処理[collision_wall.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "collision_wall.h"
#include "manager.h"

//定数の初期化
const std::string CCollision_Wall::FILEPATH = "data\\TEXTURE\\SmashMesh000.png";//テクスチャパス
const int CCollision_Wall::NUM_CORNER = 20;										//角の数
const float CCollision_Wall::HEIGHT = 50.0f;									//高さ

//============================
//コンストラクタ
//============================
CCollision_Wall::CCollision_Wall(int nPriority) : CObjectCylinder(nPriority),
	m_bEnd(false),			//終了判定
	m_fAlpha(FLOAT_ZERO)	//α値
{

}

//============================
//デストラクタ
//============================
CCollision_Wall::~CCollision_Wall()
{

}

//============================
//初期化
//============================
HRESULT CCollision_Wall::Init()
{
	//基底の初期化
	CObjectCylinder::Init();

	//設定
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	//頂点を透明に

	return S_OK;
}

//============================
//終了処理
//============================
void CCollision_Wall::Uninit()
{
	//自分の開放
	CObjectCylinder::Uninit();
}

//============================
//更新
//============================
void CCollision_Wall::Update()
{
	//透明度を徐々に不透明にする処理
	if (m_fAlpha < 1.0f && !m_bEnd)
	{
		m_fAlpha += ADD_ALPHA;	//加算

		if (m_fAlpha > 1.0f)	//補正
		{
			m_fAlpha = 1.0f;
		}

		//頂点の色を設定
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha));
	}
	else if (m_bEnd)
	{
		m_fAlpha -= ADD_ALPHA;	//減算

		if (m_fAlpha <= 0.0f)	//補正
		{
			m_fAlpha = 0.0f;
			Uninit();
			return;
		}

		//頂点の色を設定
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha));
	}

	//更新
	CObjectCylinder::Update();
}

//============================
//描画
//============================
void CCollision_Wall::Draw()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//ライトをオフ
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//カリング方法を変更
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//描画処理
	CObjectCylinder::Draw(FILEPATH.c_str());

	//カリング方法を変更
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//ライトをオン
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//================================
//クリエイト
//================================
CCollision_Wall* CCollision_Wall::Create(D3DXVECTOR3 pos, float radius)
{
	//ポインタ用の変数
	CCollision_Wall* pObject;

	//メモリの確保
	pObject = new CCollision_Wall;

	//パラメータの設定
	pObject->SetPos(pos);			//位置の設定
	pObject->SetRadius(radius);	//半径の設定

	//初期化
	pObject->Init();

	return pObject;
}

//================================
//壁の当たり判定結果を返す
//================================
bool CCollision_Wall::GetHit(D3DXVECTOR3& pos, float radius)
{
	//返り値用の変数
	bool bHit = false;

	//計算用の変数を宣言
	D3DXVECTOR3 WallPos = GetPos();		//壁の位置
	float fWallRadius = GetRadius();	//壁の半径
	D3DXVECTOR3 TargetPos = pos;		//ターゲット位置
	float fTargetRadius = radius;		//ターゲット半径

	//中心点からの距離を算出
	D3DXVECTOR3 Vec3Length = WallPos - TargetPos;	//位置
	float fLength = sqrtf(Vec3Length.x * Vec3Length.x + Vec3Length.z * Vec3Length.z);	//距離を算出
	float fAngle = atan2f(Vec3Length.x, Vec3Length.z);									//角度を算出

	//壁より外側にいるかを判定
	if (fWallRadius <= fLength + radius)
	{
		//円の内側に補正
		pos.x = sinf(fAngle + D3DX_PI) * (fWallRadius - radius) + WallPos.x;
		pos.z = cosf(fAngle + D3DX_PI) * (fWallRadius - radius) + WallPos.z;

		//ヒット判定
		bHit = true;
	}

	//判定を返す
	return bHit;
}