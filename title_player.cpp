//======================================
//
//	プレイヤーの処理[title_player.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "title_player.h"
#include "manager.h"
#include "modelparts.h"
#include "camera.h"

//静的メンバの初期化
const std::string CTitle_Player::FILEPATH = "data\\playermotion001.txt";

//============================
//プレイヤーのコンストラクタ
//============================
CTitle_Player::CTitle_Player(int nPriority) : CCharacter(nPriority)
{
	
}

//============================
//プレイヤーのデストラクタ
//============================
CTitle_Player::~CTitle_Player()
{

}

//============================
//プレイヤーの初期化
//============================
HRESULT CTitle_Player::Init()
{
	//初期化
	CCharacter::Init();

	//パラメータの初期化
	CCharacter::SetRot({ 0.0f, 0.0f, 0.0f });
	CCharacter::SetPos({ 0.0f, 0.0f, 0.0f });
	CCharacter::SetGoalRot({ 0.0f, 0.0f, 0.0f });

	//モーションの読み込み
	SetMotionInfo(FILEPATH.c_str());

	//モーションの設定
	SetMotion(CTitle_Player::TITLE_PLAYERMOTION_NORMAL);

	return S_OK;
}

//============================
//プレイヤーの終了処理
//============================
void CTitle_Player::Uninit()
{
	//終了処理
	CCharacter::Uninit();
}

//============================
//プレイヤーの更新
//============================
void CTitle_Player::Update()
{
	//共通処理の更新
	CCharacter::Update();
}

//============================
//プレイヤーの描画
//============================
void CTitle_Player::Draw()
{
	//キャラクタークラスの描画
	CCharacter::Draw();
}

//============================
//プレイヤーのクリエイト
//============================
CTitle_Player* CTitle_Player::Create()
{
	//ポインタ用の変数
	CTitle_Player* pTitle_Player;

	//メモリの確保
	pTitle_Player = new CTitle_Player;

	//初期化
	pTitle_Player->Init();

	return pTitle_Player;
}