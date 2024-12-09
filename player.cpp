//======================================
//
//	プレイヤーの処理[player.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "player.h"
#include "manager.h"
#include "game.h"
#include "modelparts.h"
#include "camera.h"
#include "state_player_normal.h"
#include "state_player_damage.h"
#include "state_player_knockback.h"
#include "battleareamanager.h"
#include "barriermanager.h"

//静的メンバの初期化
const float CPlayer::DAMAGE_IMPULSE = 10.0f;
const std::string CPlayer::FILEPATH = "data\\MODEL\\player001.x";

//============================
//プレイヤーのコンストラクタ
//============================
CPlayer::CPlayer(int nPriority) : CCharacter(nPriority),
	//m_pAction(),
	//m_pOrbit(nullptr),
	m_pLifeGauge(nullptr),
	m_pState(nullptr)
{
	m_pState = new CState_Player_Normal(this);
	SetType(TYPE_PLAYER);	//種類の設定
	SetCharacterType(CHARACTER_TYPE_PLAYER);
}

//============================
//プレイヤーのデストラクタ
//============================
CPlayer::~CPlayer()
{
	
}

//============================
//プレイヤーの初期化
//============================
HRESULT CPlayer::Init()
{
	//初期化
	CCharacter::Init();

	//パラメータの初期化
	CCharacter::SetRot({ 0.0f, 0.0f, 0.0f });
	CCharacter::SetPos({ 0.0f, 0.0f, 0.0f });
	CCharacter::SetGoalRot({ 0.0f, D3DX_PI, 0.0f });
	
	//モーションの読み込み
	SetMotionInfo("data\\playermotion000.txt");

	//ゲージの生成
	if (m_pLifeGauge == nullptr)
	{
		m_pLifeGauge = CGauge_PlayerLife::Create(20);
	}

	//仮のライフ設定
	SetLife(20);

	return S_OK;
}

//============================
//プレイヤーの終了処理
//============================
void CPlayer::Uninit()
{
	//初期化
	CCharacter::Uninit();

	//ゲージの消去
	if (m_pLifeGauge != nullptr)
	{
		m_pLifeGauge->Uninit();
		m_pLifeGauge = nullptr;
	}

	//状態の消去
	if (m_pState != nullptr)
	{
		delete m_pState;
		m_pState = nullptr;
	}

	SetOrbit(false);	//軌跡の削除
}

//============================
//プレイヤーの更新
//============================
void CPlayer::Update()
{
	//次の状態があるなら変更
	if (m_pState->GetNextState() != nullptr)
	{
		//次の状態に変更
		CState_Player* pNext = m_pState->GetNextState();
		delete m_pState;
		m_pState = nullptr;

		//代入
		m_pState = pNext;
	}

	//状態に応じた更新処理
	if (m_pState != nullptr)
	{
		m_pState->Update(this);

		//次の状態があるなら変更
		if (m_pState->GetNextState() != nullptr)
		{
			//次の状態に変更
			CState_Player* pNext = m_pState->GetNextState();
			delete m_pState;
			m_pState = nullptr;

			//代入
			m_pState = pNext;
		}
	}

	//結界との当たり判定
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();
	for (auto itr : pGame->GetBarrierManager()->GetList())
	{
		//仮の当たり判定
		if (GetPos().z + 30.0f >= itr->GetPos().z)
		{
			GetPos().z = itr->GetPos().z - 30.0f;
		}
	}

	//共通処理の更新
	CCharacter::Update();
}

//============================
//ダメージ時の処理
//============================
bool CPlayer::SetDamage(int damage)
{
	//ダメージの設定
	m_pState->SetDamage(this, damage);

	return true;
}

//============================
//プレイヤーの描画
//============================
void CPlayer::Draw()
{
	//キャラクタークラスの描画
	CCharacter::Draw();
}

//============================
//プレイヤーのクリエイト
//============================
CPlayer* CPlayer::Create()
{
	//ポインタ用の変数
	CPlayer* pPlayer;

	//メモリの確保
	pPlayer = new CPlayer;

	//初期化
	pPlayer->Init();

	return pPlayer;
}

//============================
//重力の処理
//============================
D3DXVECTOR3 CPlayer::GravityMove(D3DXVECTOR3 move)
{
	//空中にいるなら重力を加算
	if (!GetOnStand())
	{
		//重力の加算
		move.y -= GRAVITY;
	}
	else
	{
		//着地していて落ちていたら補正
		if (move.y < 0.0f)
		{
			move.y = 0.0f;
		}
	}

	return move;
}

//============================
//位置の更新
//============================
void CPlayer::UpdatePos()
{
	//パラメータの取得
	D3DXVECTOR3 pos = CObject::GetPos();	//位置

	//前回の位置を保存
	GetOldPos() = pos;

	//重力の処理
	if (GetEnableGravity())
	{
		GetMove() = GravityMove(GetMove());
	}

	//ゲームシーンなら判定
	if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
	{
		//ゲームシーンの取得
		CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

		//移動量を位置に加算
		pos += GetMove();

		//エリアの確認
		if (CBattleAreaManager::GetInstance()->GetCurrentBattleArea() != nullptr)
		{
			//壁との当たり判定
			CBattleAreaManager::GetInstance()->GetCurrentBattleArea()->GetWall()->GetHit(pos, GetSizeRadius());
		}

		//立っていないなら
		if (!GetOnStand())
		{
			//地面に接していたら
			if (pGame->GetGameField()->MeshCollision(pos))
			{
				//立っている判定
				SetOnStand(true);
			}
		}
		else
		{
			//位置を補正
			pos = pGame->GetGameField()->ConvertMeshPos(pos);
		}

		//横の当たり判定
		pos = pGame->GetGameField()->WidthCollision(pos);
	}

	//移動量を減衰
	GetMove().x += (0.0f - GetMove().x) * 0.5f;
	GetMove().z += (0.0f - GetMove().z) * 0.5f;

	//パラメータの設定
	CObject::SetPos(pos);	//位置
}

//============================
//軌跡の設定
//============================
void CPlayer::SetOrbit(bool set)
{
	//if (set) //trueなら
	//{
	//	//軌跡がないなら
	//	if (m_pOrbit == nullptr)
	//	{
	//		m_pOrbit = COrbit::Create();
	//	}
	//	
	//	//モデルパーツの取得
	//	CModelparts* pModelParts = GetModelParts(15);

	//	//オフセット位置の設定
	//	D3DXVECTOR3 OffsetPos = { 0.0f, 70.0f, 0.0f };
	//	D3DXVec3TransformCoord(&OffsetPos, &OffsetPos, &pModelParts->GetMtx());

	//	//軌跡の設定
	//	m_pOrbit->SetOrbit(pModelParts->GetWorldPos(), OffsetPos);
	//	m_pOrbit->SetOrbit(OffsetPos, pModelParts->GetWorldPos());
	//}
	//else //falseなら
	//{
	//	//軌跡がないなら
	//	if (m_pOrbit != nullptr)
	//	{
	//		//終了処理
	//		m_pOrbit->Uninit();
	//		m_pOrbit = nullptr;
	//	}
	//}
}

//============================
//ノックバックの設定
//============================
void CPlayer::SetKnockBack(int time)
{
	SetMotion(PLAYERMOTION_KNOCKBACK);	//モーションの設定

	//ノックバックの移動量を設定
	D3DXVECTOR3 Rot = GetRot();
	D3DXVECTOR3 Move = GetMove();
	D3DXVECTOR3 AddMove = { sinf(Rot.y) * 10.0f, 0.0f, cosf(Rot.y) * 10.0f };

	//移動量の加算
	Move += AddMove;
	SetMove(Move);
	ChangeState(new CState_Player_Knockback(this));
}

//============================
//ステートの設定
//============================
void CPlayer::SetState(CState_Player* state)
{
	//軌跡の削除
	SetOrbit(false);	

	//状態の変更
	delete m_pState;
	m_pState = state;
}

//============================
//アクションの切り替え
//============================
//CAction_Player* CPlayer::ChangeAction(CAction_Player* action)
//{
//	//nullチェック
//	if (m_pAction != nullptr)
//	{
//		delete m_pAction;
//		m_pAction = nullptr;
//	}
//
//	//アクションの設定
//	m_pAction = action;
//	m_pAction->SetCharacter(this);
//	m_pAction->Init();
//
//	return m_pAction;
//}

//============================
//状態の変更
//============================
void CPlayer::ChangeState(CState_Player* state)
{
	//チェック後に開放
	if (m_pState == nullptr)
	{
		delete m_pState;
	}

	m_pState = state;
}