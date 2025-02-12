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
#include "state_player_death.h"

//静的メンバの初期化
const float CPlayer::DAMAGE_IMPULSE = 10.0f;
const std::string CPlayer::FILEPATH = "data\\MODEL\\player001.x";

//============================
//プレイヤーのコンストラクタ
//============================
CPlayer::CPlayer(int nPriority) : CGame_Character(nPriority),
	m_pLifeGauge(nullptr),
	m_pState(nullptr),
	m_bGuard(false)
{
	m_pState = new CState_Player_Normal(this);
	SetType(TYPE_PLAYER);	//種類の設定
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
	CGame_Character::Init();

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
	CGame_Character::Uninit();

	//ゲージの消去
	if (m_pLifeGauge != nullptr)
	{
		m_pLifeGauge->Uninit();
		m_pLifeGauge = nullptr;
	}

	//状態の消去
	if (m_pState != nullptr)
	{
		if (m_pState->GetBehavior() != nullptr)
		{
			//次の行動を削除
			if (m_pState->GetBehavior()->GetNextBehavior() != nullptr)
			{
				delete m_pState->GetBehavior()->GetNextBehavior();
			}
		}

		//次の状態を破棄
		if (m_pState->GetNextState() != nullptr)
		{
			delete m_pState->GetNextState();
		}
		
		delete m_pState;
		m_pState = nullptr;
	}
}

//============================
//プレイヤーの更新
//============================
void CPlayer::Update()
{
	//ゲームシーンの取得
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//演出中なら更新しない
	if (pGame->GetDirectioning())
	{
		return;
	}

	//状態の更新
	CPlayer::UpdateState();

	//コリジョンの判定
	CPlayer::CollisionJudge();

	//共通処理の更新
	CGame_Character::Update();
}

//============================
//状態の更新
//============================
void CPlayer::UpdateState()
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
}

//============================
//コリジョンの判定
//============================
void CPlayer::CollisionJudge()
{
	//ゲームシーンの取得
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//結界との当たり判定
	for (auto itr : pGame->GetBarrierManager()->GetList())
	{
		//仮の当たり判定
		if (GetPos().z + 30.0f >= itr->GetPos().z)
		{
			GetPos().z = itr->GetPos().z - 30.0f;
		}
	}

	//各ギミックとの当たり判定
	for (auto& iter : pGame->GetGimmickManager()->GetList())
	{
		//位置の取得
		D3DXVECTOR3 GimmickPos = iter->GetCollision()->GetPos();
		D3DXVECTOR3 CharacterPos = GetCollision()->GetPos();

		//距離を計算
		float fLength = sqrtf((CharacterPos.x - GimmickPos.x) * (CharacterPos.x - GimmickPos.x) + (CharacterPos.z - GimmickPos.z) * (CharacterPos.z - GimmickPos.z));
		float fTotalRadius = iter->GetCollision()->GetRadius() + GetCollision()->GetRadius();
		float fHeightLength = CharacterPos.y - GimmickPos.y;

		//高さの距離を絶対値に変更
		if (fHeightLength < 0.0f) { fHeightLength *= -1.0f; }

		//範囲内の確認
		if (fLength < fTotalRadius && fHeightLength < fTotalRadius)
		{
			//樽の当たらない位置に補正
			float fAngle = atan2f(GimmickPos.x - CharacterPos.x, GimmickPos.z - CharacterPos.z);//対角線の角度を算出

			//位置の設定
			SetPos(D3DXVECTOR3(sinf(fAngle + D3DX_PI) * fTotalRadius + GimmickPos.x,
				GetPos().y,
				cosf(fAngle + D3DX_PI) * fTotalRadius + GimmickPos.z));
		}
	}

	//位置を補正
	if (GetPos().z < 0.0f)
	{
		GetPos().z = 0.0f;
	}

	if (GetPos().z > 4000.0f)
	{
		GetPos().z = 4000.0f;
	}
}

//============================
//ダメージ時の処理
//============================
bool CPlayer::SetDamage(int damage, float angle)
{
	//ダメージの設定
	return m_pState->SetDamage(this, damage, angle);
}

//============================
//プレイヤーの描画
//============================
void CPlayer::Draw()
{
	//ゲームシーンの取得
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//演出中なら更新しない
	if (pGame->GetDirectioning())
	{
		return;
	}
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
	//体力がないなら更新しない
	if (GetLife() <= 0)
	{
		return;
	}

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
		CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

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
//状態の設定
//============================
void CPlayer::SetState(CState_Player* state)
{
	//状態の変更
	delete m_pState;
	m_pState = state;
}

//============================
//死亡時の処理
//============================
void CPlayer::SetCharacterDeath()
{
	ChangeState(new CState_Player_Death(this));
}

//============================
//状態の変更
//============================
void CPlayer::ChangeState(CState_Player* state)
{
	//チェック後に開放
	if (m_pState == nullptr)
	{
		delete m_pState;
		m_pState = nullptr;
	}

	m_pState = state;
}