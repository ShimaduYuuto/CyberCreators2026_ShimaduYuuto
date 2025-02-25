//================================
//
//プレイヤーの行動まとめ[behavior_player.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "behavior_player.h"
#include "manager.h"
#include "game.h"
#include "gauge_slow.h"
#include "effect_hitattack.h"
#include "effect_runsmoke.h"
#include "state_player_normal.h"
#include "state_player_counter.h"
#include "state_player_guard.h"
#include "particle_rush.h"

//定数
const D3DXVECTOR3 CPlayerBehavior_Attack::POS_OFFSET{ 0.0f, 20.0f, 30.0f };

//各行動を行おうとしたかを返す
bool TriggerJump(CPlayer* player);		//ジャンプをしたか
bool TriggerAttack();					//攻撃をしたか
bool TriggerDash();						//ダッシュをしたか

//=========================
//ジャンプをしたか
//=========================
bool TriggerJump(CPlayer* player)
{
	if (!player->GetOnStand()) return false;													//地上にいないなら抜ける
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_SPACE)) return true;				//キーボードの判定
	if (CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_A)) return true;	//ジョイパッドの確認

	return false;
}

//=========================
//攻撃をしたか
//=========================
bool TriggerAttack()
{
	if (CManager::GetInstance()->GetMouse()->GetTrigger(CInputMouse::MOUSEBUTTON_LEFT)) return true;	//キーボードの判定
	if (CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_X)) return true;			//ジョイパッドの確認

	return false;
}

//=========================
//ダッシュをしたか
//=========================
bool TriggerDash()
{
	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_LSHIFT)) return true;				//キーボードの判定
	if (CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_LB)) return true;		//ジョイパッドの確認

	return false;
}

//================================================================
//移動
//================================================================

//=========================
//コンストラクタ
//=========================
CPlayerBehavior_Move::CPlayerBehavior_Move(CPlayer* player)
{
	player->SetEnableGravity(true);	//重力を受ける
}

//=========================
//行動(移動)
//=========================
void CPlayerBehavior_Move::Behavior(CPlayer* player)
{
	//ローカル変数宣言
	D3DXVECTOR3 pos = player->GetPos();				//位置の取得
	D3DXVECTOR3 goalrot = player->GetGoalRot();		//目的の向きの取得
	D3DXVECTOR3 move = player->GetMove();			//移動量の取得

	//Xファイルの読み込み
	CXfile* pCXfile = CManager::GetInstance()->GetXfile();

	//ジャンプ
	if (TriggerJump(player))
	{//SPACEが押された場合
		move.y += JUMP_SPEED;
		player->SetOnStand(false);
		player->SetMotion(CPlayer::PLAYERMOTION_JUMP);
	}

	//空中にいるならモーションを変える
	if(!player->GetOnStand() && player->GetMotionState() != CPlayer::PLAYERMOTION_JUMP)
	{
		//ジャンプのモーション
		player->SetMotion(CPlayer::PLAYERMOTION_JUMP);
	}

	//移動量の更新
	move += UpdateMove(player, goalrot);

	//パラメータの設定
	player->SetPos(pos);			//位置
	player->SetGoalRot(goalrot);	//目的の向き
	player->SetMove(move);			//移動量

	//アクション処理
	Action(player);
}

//========================
//移動の更新
//========================
D3DXVECTOR3 CPlayerBehavior_Move::UpdateMove(CPlayer* player, D3DXVECTOR3& Rotgoal)
{
	//返す用の変数
	D3DXVECTOR3 move = { 0.0f, 0.0f, 0.0f };
	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	//動いたかの判定用
	bool bMove = false;
	bool bPressKey = false;

	//キーボードの更新があったか
	if (CheckUpdateKeyboard(player, Rotgoal, &move))
	{
		bMove = true;
		bPressKey = true;
	}

	//スティックが倒れていたらその方向に進む
	if (CheckUpdateStick(bPressKey))
	{
		//スティックでの更新
		UpdateStickMove(Rotgoal, &move);

		bMove = true;	//動いた判定
	}

	//動いたかの判定
	if (bMove && player->GetOnStand())
	{
		//歩きモーションを設定
		if (player->GetMotionState() != CPlayer::PLAYERMOTION_WALK)
		{
			//モーションの設定
			player->SetMotion(CPlayer::PLAYERMOTION_WALK);
		}
	}
	else if (player->GetOnStand())	//地面に着いているなら
	{
		//ニュートラルモーションを設定
		if (player->GetMotionState() != CPlayer::PLAYERMOTION_NORMAL)
		{
			//モーションの設定
			player->SetMotion(CPlayer::PLAYERMOTION_NORMAL);
		}
	}

	//移動量を返す
	return move;
}

//========================
//キーボードの更新確認
//========================
bool CPlayerBehavior_Move::CheckUpdateKeyboard(CPlayer* player, D3DXVECTOR3& Rotgoal, D3DXVECTOR3* move)
{
	//判定用
	bool bPressKey = false;
	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_A))
	{//Aキーが押された場合
		if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_W))
		{
			move->x += sinf(D3DX_PI * -0.75f - pCamera->GetRot().y) * MOVE_SPEED;
			move->z -= cosf(D3DX_PI * -0.75f - pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = D3DX_PI * 0.75f + pCamera->GetRot().y;
		}
		else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_S))
		{
			move->x += sinf(D3DX_PI * -0.25f - pCamera->GetRot().y) * MOVE_SPEED;
			move->z -= cosf(D3DX_PI * -0.25f - pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = D3DX_PI * 0.25f + pCamera->GetRot().y;
		}
		else
		{
			move->x += sinf(D3DX_PI * -0.5f + pCamera->GetRot().y) * MOVE_SPEED;
			move->z += cosf(D3DX_PI * -0.5f + pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = -(D3DX_PI * -0.5f - pCamera->GetRot().y);
		}

		bPressKey = true;	//キーボードを触っている
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_D))
	{//Dキーが押された場合

		if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_W))
		{
			move->x += sinf(D3DX_PI * 0.75f - pCamera->GetRot().y) * MOVE_SPEED;
			move->z -= cosf(D3DX_PI * 0.75f - pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = D3DX_PI * -0.75f + pCamera->GetRot().y;
		}
		else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_S))
		{
			move->x += sinf(D3DX_PI * 0.25f - pCamera->GetRot().y) * MOVE_SPEED;
			move->z -= cosf(D3DX_PI * 0.25f - pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = D3DX_PI * -0.25f + pCamera->GetRot().y;
		}
		else
		{
			move->x += sinf(D3DX_PI * 0.5f + pCamera->GetRot().y) * MOVE_SPEED;
			move->z += cosf(D3DX_PI * 0.5f + pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = -(D3DX_PI * 0.5f - pCamera->GetRot().y);
		}

		bPressKey = true;	//キーボードを触っている
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_W))
	{//Wキーが押された場合
		{
			move->z -= cosf(D3DX_PI + pCamera->GetRot().y) * MOVE_SPEED;
			move->x -= sinf(D3DX_PI + pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = D3DX_PI + pCamera->GetRot().y;
		}

		bPressKey = true;	//キーボードを触っている
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_S))
	{//Sキーが押された場合
		{
			move->z -= cosf(pCamera->GetRot().y) * MOVE_SPEED;
			move->x -= sinf(pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = pCamera->GetRot().y;
		}

		bPressKey = true;	//キーボードを触っている
	}

	return bPressKey;
}

//============================
//スティックで更新されたか
//============================
bool CPlayerBehavior_Move::CheckUpdateStick(bool pressed)
{
	float fDiameter = CManager::GetInstance()->GetJoypad()->GetStick().afTplDiameter[CInputJoypad::STICKTYPE_LEFT];	//スティックの倒し具合

	if (pressed) return false;				//キーがすでに押されているなら抜ける
	if (fDiameter > 0.001f) return true;	//スティックが倒れているなら真を返す

	return false;
}

//============================
//スティックで更新されたか
//============================
void CPlayerBehavior_Move::UpdateStickMove(D3DXVECTOR3& Rotgoal, D3DXVECTOR3* move)
{
	CCamera* pCamera = CManager::GetInstance()->GetCamera();												//カメラの取得
	float fAngle = CManager::GetInstance()->GetJoypad()->GetStick().afAngle[CInputJoypad::STICKTYPE_LEFT];	//スティックの角度を取得

	move->z += cosf(pCamera->GetRot().y + -fAngle + D3DX_PI) * MOVE_SPEED;	//X方向の移動
	move->x += sinf(pCamera->GetRot().y + -fAngle + D3DX_PI) * MOVE_SPEED;	//Z方向の移動
	Rotgoal.y = pCamera->GetRot().y + -fAngle;								//進行方向に向く
}

//============================
//プレイヤーのアクション処理
//============================
void CPlayerBehavior_Move::Action(CPlayer* player)
{
	//すでに次の行動が決まっているなら抜ける
	if (GetNextBehavior() != nullptr) return;

	//左シフトでダッシュを設定
	if (TriggerDash())
	{
		//ゲームシーンなら判定
		if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
		{
			//ゲームシーンの取得
			CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

			//ロックオン相手の確認
			if (pGame->GetLockon() != nullptr)
			{
				if (pGame->GetLockon()->GetTarget() != nullptr)
				{
					//ダッシュを生成
					SetNextBehavior(new CPlayerBehavior_Dash(player));
				}
			}
		}
	}

	//立っていたら
	if (player->GetOnStand())
	{
		//右クリックをしたら
		if (CManager::GetInstance()->GetMouse()->GetPress(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_RIGHT) || CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_RB))
		{
			//ガードを生成
			player->GetState()->SetNextState(new CState_Player_Guard(player));
			return;
		}
		else if (TriggerAttack())
		{
			//モーションの設定
			player->SetMotion(CPlayer::PLAYERMOTION_ACTION);

			//通常攻撃を生成
			SetNextBehavior(new CPlayerBehavior_NormalAttack000(player));
		}
	}
	else //空中
	{
		//左クリックをしたら
		if (TriggerAttack())
		{
			//モーションの設定
			player->SetMotion(CPlayer::PLAYERMOTION_ACTION);

			//空中攻撃に切り替え
			SetNextBehavior(new CPlayerBehavior_Arial000(player));
		}
		else if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_RIGHT))
		{
			//ゲームシーンなら判定
			if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
			{
				//ゲームシーンの取得
				CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

				//ロックオンの設定
				pGame->SetLockon(true);
			}
		}
	}
}

//================================================================
//ダッシュ
//================================================================

//============================
//コンストラクタ
//============================
CPlayerBehavior_Dash::CPlayerBehavior_Dash(CPlayer* player) :
	m_bFirst(true),
	m_DashSpeed()
{
	//設定
	player->SetMotion(CPlayer::PLAYERMOTION_JUMP);	//モーション
	player->SetOnStand(false);						//立っていない状態
	player->SetEnableGravity(false);				//重力を受けない
	player->GetPos().y += 0.01f;					//位置を少し上げる
}

//============================
//行動(ダッシュ)
//============================
void CPlayerBehavior_Dash::Behavior(CPlayer* player)
{
	//押している間ダッシュする
	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_LSHIFT) ||
		CManager::GetInstance()->GetJoypad()->GetPress(CInputJoypad::JOYKEY_LB))
	{
		//返す用の変数
		D3DXVECTOR3 move = { 0.0f, 0.0f, 0.0f };

		//ゲームシーンなら判定
		if (CManager::GetInstance()->GetScene()->GetMode() != CManager::GetInstance()->GetScene()->MODE_GAME)
		{
			return;
		}

		//ゲームシーンの取得
		CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

		//ロックオン相手の確認
		if (pGame->GetLockon() == nullptr)
		{
			return;
		}

		if (pGame->GetLockon()->GetTarget() != nullptr)
		{
			//ターゲットとの距離を算出
			D3DXVECTOR3 TagPos = pGame->GetLockon()->GetTarget()->GetPos();
			D3DXVECTOR3 Length = TagPos - player->GetPos();
			float fLength = sqrtf((Length.x * Length.x) + (Length.z * Length.z));
			fLength = D3DXVec3Length(&Length);	//距離を算出
			float fAngle = atan2f(TagPos.x - player->GetPos().x, TagPos.z - player->GetPos().z);

			//ロックオンの方に向ける
			player->SetGoalRot({ 0.0f, fAngle + D3DX_PI, 0.0f });

			//敵から離れているならダッシュ
			if (fLength > STOP_LENGYH)
			{
				//初めて通るなら速度を算出
				if (m_bFirst)
				{
					//線形補間の値を算出
					m_DashSpeed = Length * RATIO_LINEAR_INTERPOLATION;
					m_bFirst = false;
				}
				//ターゲットにダッシュ
				move.x = m_DashSpeed.x;
				move.y = m_DashSpeed.y;
				move.z = m_DashSpeed.z;

				//effect
				CEffect_RunSmoke::Create(player->GetPos());
			}

			//止まる距離になったら攻撃
			if (fLength < STOP_LENGYH)
			{
				//移動状態にする
				SetNextBehavior(new CPlayerBehavior_DashAttack000(player));
			}
		}
		else
		{
			//移動状態にする
			SetNextBehavior(new CPlayerBehavior_Move(player));
		}

		//移動量の設定
		player->SetMove({ move.x , move.y, move.z });
	}
	else if(CManager::GetInstance()->GetKeyboard()->GetRerease(DIK_LSHIFT) ||
			CManager::GetInstance()->GetJoypad()->GetRerease(CInputJoypad::JOYKEY_LB)) //離したらダッシュを終了
	{
		//移動状態にする
		SetNextBehavior(new CPlayerBehavior_Move(player));
	}
}

//================================================================
//攻撃
//================================================================

//============================
//コンストラクタ
//============================
CPlayerBehavior_Attack::CPlayerBehavior_Attack() :
	m_fAttackLength(0.0f),				//攻撃の距離
	m_HitEnemy(),						//ヒットした敵のリスト
	m_nCancelStartTime(0),				//キャンセル時間
	m_nCollisionlTime(0),				//当たり判定の発生時間
	m_nEndCount(0),						//終了カウント
	m_nEndTime(0),						//終了時間
	m_OffsetPos({0.0f, 0.0f, 0.0f}),	//オフセット位置
	m_bCancel(false)					//キャンセル判定
{
	//パラメータの設定
	SetEndTime(END_TIME);				//終了時間
	SetCollisionTime(START_COLLISION);	//当たり判定の時間
	SetCancelTime(START_CANCEL);		//キャンセル開始時間
	SetAttackLength(ATTACK_LENGTH);		//攻撃の距離
	SetOffsetPos(POS_OFFSET);			//オフセット位置
}

//============================
//コンストラクタ
//============================
CPlayerBehavior_Attack::CPlayerBehavior_Attack(CPlayer* player) :
	m_fAttackLength(0.0f),		//攻撃の距離
	m_HitEnemy(),				//ヒットした敵のリスト
	m_nCancelStartTime(0),		//キャンセル時間
	m_nCollisionlTime(0),		//当たり判定の発生時間
	m_nEndCount(0),				//終了カウント
	m_nEndTime(0),				//終了時間
	m_bCancel(false)			//キャンセル判定
{
	//パラメータの設定
	SetEndTime(END_TIME);				//終了時間
	SetCollisionTime(START_COLLISION);	//当たり判定の時間
	SetCancelTime(START_CANCEL);		//キャンセル開始時間
	SetAttackLength(ATTACK_LENGTH);		//攻撃の距離
	SetOffsetPos(POS_OFFSET);			//オフセット位置

	//SEを鳴らす
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SWING);
}

//============================
//デストラクタ
//============================
CPlayerBehavior_Attack::~CPlayerBehavior_Attack()
{
	m_HitEnemy.clear();
}

//============================
//敵の方を見る
//============================
void CPlayerBehavior_Attack::LookAtEnemy(CPlayer* player)
{
	//ゲームシーンの取得
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//敵が見つかったか
	bool bHit = false;

	//保存する情報
	D3DXVECTOR3 GoalEnemyPos = { VEC3_RESET_ZERO };
	float ShortLength = 100.0f;
	float fSaveAngleDifference = D3DX_PI;

	//敵の周回
	for (auto& iter : pGame->GetEnemyManager()->GetList())
	{
		//位置の情報を更新
		D3DXVECTOR3 PlayerPos = player->GetPos();
		D3DXVECTOR3 EnemyLength = iter->GetCollision()->GetPos() - PlayerPos;

		float fXZ = sqrtf(EnemyLength.x * EnemyLength.x + EnemyLength.z * EnemyLength.z); //XZ距離を算出する
		float fXY = sqrtf(EnemyLength.x * EnemyLength.x + EnemyLength.y * EnemyLength.y); //XY距離を算出する
		float fLength = sqrtf(fXZ * fXZ + fXY * fXY);	//距離を算出

		//より近い敵を見つけたら更新
		if (fLength < ShortLength)
		{
			//プレイヤーの向いている方向にいるかを判断
			float fPlayerAngle = player->GetRot().y;
			D3DXVECTOR3 Length = iter->GetPos() - player->GetPos();
			float fAngle = atan2f(-Length.x, -Length.z)/* + D3DX_PI*/;
			
			if (CheckEnemyInFront(player, fAngle, D3DX_PI))
			{
				float fAngleDifference = CheckAngleDiff(fPlayerAngle, fAngle);

				if (fAngleDifference < fSaveAngleDifference)
				{
					//情報を保存
					fSaveAngleDifference = fAngleDifference;
					ShortLength = fLength;
					GoalEnemyPos = iter->GetPos();
					bHit = true;
				}
			}
		}
	}

	//追尾する敵を見つけたらそっちを向く
	if (bHit)
	{
		D3DXVECTOR3 Length = GoalEnemyPos - player->GetPos();
		float fAngle = atan2f(Length.x, Length.z);
		player->SetGoalRot({ 0.0f, fAngle + D3DX_PI, 0.0f });
	}
}

//============================
//前方に敵がいるかの確認
//============================
bool CPlayerBehavior_Attack::CheckEnemyInFront(CPlayer* player, float targetangle, float radian)
{
	float fPlayerRot = player->GetRot().y;
	float fRot = targetangle;
	float fMin = fPlayerRot - radian * 0.5f;
	float fMax = fPlayerRot + radian * 0.5f;

	//後ろからの攻撃なら通す
	if (fRot > fMin && fRot < fMax)
	{
		return true;
	}

	return false;
}

//============================
//攻撃行動
//============================
void CPlayerBehavior_Attack::Behavior(CPlayer* player)
{
	//当たり判定
	if (IsHitProcess())
	{
		//ゲームシーンの取得
		CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

		//攻撃判定の生成
		D3DXVECTOR3 AttackPos = player->GetPos();
		AttackPos += {sinf(player->GetRot().y + D3DX_PI)* m_OffsetPos.z, m_OffsetPos.y, cosf(player->GetRot().y + D3DX_PI)* m_OffsetPos.z};

		//敵との当たり判定
		HitEnemyProcess(player, AttackPos);

		//弾との当たり判定
		HitBulletProcess(player, AttackPos);

		//キャンセルのカウント以上になったら
		if (m_nEndCount > m_nCancelStartTime && m_bCancel)
		{
			//キャンセルの処理
			Cancel(player);
		}
	}

	//先行入力の受付
	if (m_nEndCount > m_nCancelStartTime - TYPE_AHEAD)
	{
		CancelInput();
	}

	//終了時間になったら行動を移動に変更
	if (m_nEndCount >= m_nEndTime)
	{
		if (GetNextBehavior() == nullptr)
		{
			//次の行動を設定
			NextBehavior(player);
		}
	}

	//カウントの更新
	m_nEndCount++;

	//エフェクト処理
	Effect(player);
}

//============================
//当たり判定を行うか
//============================
bool CPlayerBehavior_Attack::IsHitProcess()
{
	//各判定
	if (m_nEndCount <= m_nCollisionlTime) return false;	//カウントが当たり判定を行う時間じゃないなら抜ける
	if (CManager::GetInstance()->GetScene()->GetMode() !=
		CManager::GetInstance()->GetScene()->MODE_GAME)return false;	//ゲームシーンじゃないなら抜ける

	return true;
}

//============================
//敵との当たり判定
//============================
void CPlayerBehavior_Attack::HitEnemyProcess(CPlayer* player, D3DXVECTOR3 pos)
{
	//ゲームシーンの取得
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//敵の周回
	for (auto& iter : pGame->GetEnemyManager()->GetList())
	{
		//当たったか
		bool bHit = false;

		//すでに当たっているかを確認
		for (auto& HitEnemyiter : m_HitEnemy)
		{
			//すでに当たっていたら抜ける
			if (HitEnemyiter == iter)
			{
				bHit = true;	//すでに当たっている
				break;
			}
		}

		//すでに当たっていたら飛ばす
		if (bHit)
		{
			continue;
		}

		//敵の位置を取得
		D3DXVECTOR3 EnemyLength = iter->GetCollision()->GetPos() - pos;

		float fXZ = sqrtf(EnemyLength.x * EnemyLength.x + EnemyLength.z * EnemyLength.z); //XZ距離を算出する
		float fXY = sqrtf(EnemyLength.x * EnemyLength.x + EnemyLength.y * EnemyLength.y); //XY距離を算出する
		float fLength = sqrtf(fXZ * fXZ + fXY * fXY);	//距離を算出

		//敵の判定内なら
		if (fLength < m_fAttackLength)
		{
			//ダメージ処理
			Damage(player, iter, 1);

			//敵の移動量を取得
			D3DXVECTOR3 Move = iter->CCharacter::GetMove();

			//落ちていたら移動量を戻す
			if (Move.y < 0.0f)
			{
				Move.y = 0.0f;
			}

			//設定
			iter->CCharacter::SetMove(Move);

			//敵の情報を保存
			m_HitEnemy.push_back(iter);
		}
	}
}

//============================
//弾との当たり判定
//============================
void CPlayerBehavior_Attack::HitBulletProcess(CPlayer* player, D3DXVECTOR3 pos)
{
	//ゲームシーンの取得
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//弾との当たり判定
	for (auto& iter : pGame->GetEnemyBulletManager()->GetList())
	{
		//反射済みは飛ばす
		if (iter->GetReflection() || !iter->GetShooting())
		{
			continue;
		}

		//敵の位置を取得
		D3DXVECTOR3 Length = iter->GetCollision()->GetPos() - pos;

		float fXZ = sqrtf(Length.x * Length.x + Length.z * Length.z); //XZ距離を算出する
		float fXY = sqrtf(Length.x * Length.x + Length.y * Length.y); //XY距離を算出する
		float fLength = sqrtf(fXZ * fXZ + fXY * fXY);	//距離を算出
		D3DXVECTOR3 Distance = iter->GetPos() - pos;
		float fAngle = atan2f(Distance.x, Distance.z);

		//敵の判定内なら
		if (fLength < m_fAttackLength + iter->GetCollision()->GetRadius())
		{
			//弾を反射
			iter->Reflection(player->GetRot().y);
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_REPEL);	//SE
		}
	}
}

//============================
//ダメージを与える処理
//============================
void CPlayerBehavior_Attack::Damage(CPlayer* player, CEnemy* enemy, int damage)
{
	//ダメージが与えられたらヒット処理
	if (enemy->SetDamage(damage, player->GetRot().y))
	{
		//ヒット時の処理
		CEffect_HitAttack::Create(enemy->GetCollision()->GetPos());
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_ATTACK);
	}

	//ダメージが与えられなかったら敵の効果を受ける
	else
	{
		enemy->DamageEffect(player);
	}
}

//============================
//次の行動(移動)
//============================
void CPlayerBehavior_Attack::NextBehavior(CPlayer* player)
{
	SetNextBehavior(new CPlayerBehavior_Move(player));
}

//============================
//攻撃ボタンを入力したか
//============================
bool CPlayerBehavior_Attack::TriggerAttack()
{
	if (CManager::GetInstance()->GetMouse()->GetTrigger(CInputMouse::MOUSEBUTTON_LEFT)) return true;	//マウス
	if (CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_X)) return true;			//ジョイパッド

	return false;
}

//============================
//キャンセル入力の処理
//============================
void CPlayerBehavior_Attack::CancelInput()
{
	if (TriggerAttack())
	{
		m_bCancel = true;
	}
}

//============================
//エフェクトの処理
//============================
void CPlayerBehavior_Attack::Effect(CPlayer* player)
{
	//モデルパーツの取得
	CModelparts* pModelParts = player->GetModelParts(15);

	//オフセット位置の設定
	D3DXVECTOR3 OffsetPos = { 0.0f, ORBIT_OFFSET_LENGTH, 0.0f };
	D3DXVec3TransformCoord(&OffsetPos, &OffsetPos, &pModelParts->GetMtx());

	//パーティクルの生成
	CParticle_Rush::Create(OffsetPos, player->GetRot());
}

//================================================================
//通常攻撃(基底クラス)
//================================================================

//============================
//通常攻撃
//============================
void CPlayerBehavior_NormalAttack::Behavior(CPlayer* player)
{
	//移動量を加算する時間
	if (GetCount() < END_MOVE)
	{
		//ゲームシーンの取得
		CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

		//移動量を加算
		D3DXVECTOR3 Move = player->GetMove();
		D3DXVECTOR3 Rot = player->GetRot();

		//計算して加算
		Move += { sinf(Rot.y + D3DX_PI)* VALUE_MOVE, 0.0f, cosf(Rot.y + D3DX_PI)* VALUE_MOVE };
		pGame->GetGamePlayer()->SetMove(Move);
	}

	//攻撃の処理
	CPlayerBehavior_Attack::Behavior(player);
}

//================================================================
//通常攻撃(1段目)
//================================================================

//============================
//コンストラクタ
//============================
CPlayerBehavior_NormalAttack000::CPlayerBehavior_NormalAttack000(CPlayer* player) : CPlayerBehavior_NormalAttack(player)
{
	//敵の方向を向く
	LookAtEnemy(player);

	//モーションの設定
	player->SetMotion(CPlayer::PLAYERMOTION_ACTION);
}

//============================
//キャンセル
//============================
void CPlayerBehavior_NormalAttack000::Cancel(CPlayer* player)
{
	//次の攻撃の生成
	SetNextBehavior(new CPlayerBehavior_NormalAttack001(player));
}

//================================================================
//通常攻撃(2段目)
//================================================================

//============================
//コンストラクタ
//============================
CPlayerBehavior_NormalAttack001::CPlayerBehavior_NormalAttack001(CPlayer* player) : CPlayerBehavior_NormalAttack(player)
{
	//モーションの設定
	player->SetMotion(CPlayer::PLAYERMOTION_ACTION001);
}

//============================
//キャンセル
//============================
void CPlayerBehavior_NormalAttack001::Cancel(CPlayer* player)
{
	//次の攻撃の生成
	SetNextBehavior(new CPlayerBehavior_NormalAttack002(player));
}

//================================================================
//通常攻撃(3段目)
//================================================================

//============================
//コンストラクタ
//============================
CPlayerBehavior_NormalAttack002::CPlayerBehavior_NormalAttack002(CPlayer* player) : CPlayerBehavior_NormalAttack(player),
	m_bChargeEnd(false),			//チャージ終了フラグ
	m_fChargeRate(0.5f),			//チャージ倍率
	m_fChargeAcceleration(0.0f),	//チャージ加速度
	m_nCancelCount(0),				//キャンセルカウント
	m_pEffect(nullptr)				//エフェクトのポインタ
{
	//モーションの設定
	player->SetMotion(player->PLAYERMOTION_ATTACKCHARGE);

	//パラメータの設定
	SetEndTime(END_TIME);
	SetCollisionTime(START_COLLISION);
	SetCancelTime(START_CANCEL);
	SetAttackLength(ATTACK_LENGTH);
	SetOffsetPos(POS_OFFSET);

	//SEを止める
	CManager::GetInstance()->GetSound()->Stop(CSound::SOUND_LABEL_SWING);
}

//============================
//デストラクタ
//============================
CPlayerBehavior_NormalAttack002::~CPlayerBehavior_NormalAttack002()
{
	//エフェクトの破棄
	if (m_pEffect != nullptr)
	{
		m_pEffect->Uninit();
		m_pEffect = nullptr;
	}

	CManager::GetInstance()->GetSound()->Stop(CSound::SOUND_LABEL_CHARGE000);
}

//============================
//行動(攻撃)
//============================
void CPlayerBehavior_NormalAttack002::Behavior(CPlayer* player)
{
	if (!m_bChargeEnd)
	{
		//キャンセルカウントの加算
		if (m_nCancelCount < ACCEPT_CANCELTIME)
		{
			m_nCancelCount++;

			//チャージ攻撃に遷移する時間まで溜めたらエフェクトを生成
			if (m_nCancelCount >= ACCEPT_CANCELTIME)
			{
				m_pEffect = CEffect_Charge::Create(player->GetCollision()->GetPos());

				//SEの生成
				CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_CHARGE000);
			}
		}

		//マックスまでチャージ
		if (m_fChargeRate < MAX_RATE)
		{
			m_fChargeAcceleration += ACCELERATION_VALUE;
			m_fChargeRate += m_fChargeAcceleration;
		}

		//攻撃ボタンを離しているなら攻撃
		if ((!CManager::GetInstance()->GetMouse()->GetPress(CInputMouse::MOUSEBUTTON_LEFT) && !CManager::GetInstance()->GetJoypad()->GetPress(CInputJoypad::JOYKEY_X)) || m_fChargeRate >= MAX_RATE)
		{
			//キャンセル時間後に離したらチャージ
			if (m_nCancelCount >= ACCEPT_CANCELTIME)
			{
				//攻撃モーション
				player->SetMotion(player->PLAYERMOTION_CHARGEATTACK);

				//チャージが終わったか
				m_bChargeEnd = true;

				//各パラメータの設定
				SetAttackLength(ATTACK_LENGTH * (m_fChargeRate * 0.01f));
				SetOffsetPos(D3DXVECTOR3(POS_OFFSET.x, POS_OFFSET.y, POS_OFFSET.z * (m_fChargeRate * 0.01f)));
			}
			else
			{
				//攻撃モーション
				player->SetMotion(CPlayer::PLAYERMOTION_ACTION002);
			}

			//エフェクトの破棄
			if (m_pEffect != nullptr)
			{
				m_pEffect->Uninit();
				m_pEffect = nullptr;
			}

			//チャージが終わったか
			m_bChargeEnd = true;
			CManager::GetInstance()->GetSound()->Stop(CSound::SOUND_LABEL_CHARGE000);
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SWING);
		}
	}
	//チャージが終わっていたら攻撃
	else
	{
		//通常攻撃
		CPlayerBehavior_NormalAttack::Behavior(player);
	}
}

//============================
//ダメージを与える処理
//============================
void CPlayerBehavior_NormalAttack002::Damage(CPlayer* player, CEnemy* enemy, int damage)
{
	//ヒットしたか
	bool bHit = false;

	//キャンセルカウントの加算
	if (m_nCancelCount < ACCEPT_CANCELTIME)
	{
		bHit = enemy->SetBlowDamage(damage, player->GetRot().y);
	}
	else
	{
		//ダメージ
		bHit = enemy->SetBlowDamage(damage * 3, player->GetRot().y, m_fChargeRate * 0.5f);
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_CHARGEATTACK);
	}

	//ヒット時の処理
	if (bHit)
	{
		CEffect_HitAttack::Create(enemy->GetCollision()->GetPos());
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_ATTACK);
	}
}

//=================================================
//空中攻撃(1段目)
//=================================================

//============================
//コンストラクタ
//============================
CPlayerBehavior_Arial000::CPlayerBehavior_Arial000(CPlayer* player)
{
	//基本の設定
	player->SetMotion(CPlayer::PLAYERMOTION_ARIAL000);	//モーション
	player->SetEnableGravity(false);					//重力を受けない
	player->SetMove({ player->GetMove().x, 0.0f, player->GetMove().z });	//Y方向の移動量を無くす
}

//============================
//キャンセル処理
//============================
void CPlayerBehavior_Arial000::Cancel(CPlayer* player)
{
	//次の攻撃の生成
	SetNextBehavior(new CPlayerBehavior_Arial001(player));
}

//============================
//行動処理(攻撃)
//============================
void CPlayerBehavior_Arial000::Behavior(CPlayer* player)
{
	//攻撃の基底行動
	CPlayerBehavior_Attack::Behavior(player);
}

//=================================================
//空中攻撃(2段目)
//=================================================

//============================
//コンストラクタ
//============================
CPlayerBehavior_Arial001::CPlayerBehavior_Arial001(CPlayer* player)
{
	//モーションの設定
	player->SetMotion(CPlayer::PLAYERMOTION_ARIAL001);
}

//============================
//キャンセル処理
//============================
void CPlayerBehavior_Arial001::Cancel(CPlayer* player)
{
	//次の攻撃の生成
	SetNextBehavior(new CPlayerBehavior_Arial002(player));
}

//============================
//行動処理(攻撃)
//============================
void CPlayerBehavior_Arial001::Behavior(CPlayer* player)
{
	//攻撃の基底行動
	CPlayerBehavior_Attack::Behavior(player);
}

//=================================================
//空中攻撃(3段目)
//=================================================

//============================
//コンストラクタ
//============================
CPlayerBehavior_Arial002::CPlayerBehavior_Arial002(CPlayer* player)
{
	//モーションの設定
	player->SetMotion(CPlayer::PLAYERMOTION_ARIAL002);
}

//============================
//行動処理(攻撃)
//============================
void CPlayerBehavior_Arial002::Behavior(CPlayer* player)
{
	//攻撃の基底行動
	CPlayerBehavior_Attack::Behavior(player);
}

//=================================================
//ダッシュ攻撃(基底)
//=================================================

//============================
//コンストラクタ
//============================
CPlayerBehavior_DashAttack::CPlayerBehavior_DashAttack(CPlayer* player) : CPlayerBehavior_Attack(player),
	m_RushContinue(false)
{
	//パラメータの設定
	SetCancelTime(START_CANCELTIME);	//キャンセル
	SetEndTime(END_TIME);				//終了時間
	SetCollisionTime(START_COLLISION);	//当たり判定
	SetAttackLength(ATTACK_LENGTH);		//攻撃の距離

	//ラッシュ判定をゲームシーンに設定
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());
	pGame->SetRushJudge(true);
}

//============================
//デストラクタ
//============================
CPlayerBehavior_DashAttack::~CPlayerBehavior_DashAttack()
{
	//ラッシュ判定をゲームシーンに設定
	if (!m_RushContinue)
	{
		CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());
		pGame->SetRushJudge(false);
	}
}

//============================
//行動処理(攻撃)
//============================
void CPlayerBehavior_DashAttack::Behavior(CPlayer* player)
{
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//ラッシュ判定の確認
	if (!pGame->GetRushJudge())
	{
		pGame->SetRushJudge(true);
	}

	//モデルパーツの取得
	CModelparts* pModelParts = player->GetModelParts(15);

	//オフセット位置の設定
	D3DXVECTOR3 OffsetPos = { 0.0f, ORBIT_OFFSET_LENGTH, 0.0f };
	D3DXVec3TransformCoord(&OffsetPos, &OffsetPos, &pModelParts->GetMtx());

	//攻撃処理
	CPlayerBehavior_Attack::Behavior(player);
}

//=================================================
//ダッシュ攻撃(1段目)
//=================================================

//============================
//コンストラクタ
//============================
CPlayerBehavior_DashAttack000::CPlayerBehavior_DashAttack000(CPlayer* player) : CPlayerBehavior_DashAttack(player)
{
	//基本の設定
	player->SetMotion(CPlayer::PLAYERMOTION_ARIAL000);					//モーション
	player->SetEnableGravity(false);									//重力を受けない
	player->SetMove({ player->GetMove().x, 0.0f, player->GetMove().z });//Y方向の移動量を無くす
}

//============================
//キャンセル処理
//============================
void CPlayerBehavior_DashAttack000::Cancel(CPlayer* player)
{
	//ゲームシーンの取得
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//ロックオン相手の確認
	if (pGame->GetLockon() != nullptr)
	{
		if (pGame->GetLockon()->GetTarget() != nullptr)
		{
			//ターゲットにダッシュ
			D3DXVECTOR3 TagPos = pGame->GetLockon()->GetTarget()->GetPos();
			D3DXVECTOR3 Length = TagPos - player->GetPos();
			float fLength = sqrtf((Length.x * Length.x) + (Length.z * Length.z));
			fLength = D3DXVec3Length(&Length);	//距離を算出

			//攻撃の範囲外ならダッシュする
			if (fLength > CPlayerBehavior_Dash::STOP_LENGYH)
			{
				SetNextBehavior(new CPlayerBehavior_Move(player));
			}
			else
			{
				//次の攻撃の生成
				SetNextBehavior(new CPlayerBehavior_DashAttack001(player));
				SetRushContinue(true);
			}
		}
	}
}

//============================
//行動処理(攻撃)
//============================
void CPlayerBehavior_DashAttack000::Behavior(CPlayer* player)
{
	//ダッシュ攻撃
	CPlayerBehavior_DashAttack::Behavior(player);
}

//=================================================
//ダッシュ攻撃(2段目)
//=================================================

//============================
//コンストラクタ
//============================
CPlayerBehavior_DashAttack001::CPlayerBehavior_DashAttack001(CPlayer* player) : CPlayerBehavior_DashAttack(player)
{
	//モーションの設定
	player->SetMotion(CPlayer::PLAYERMOTION_ARIAL001);
}

//============================
//キャンセル処理
//============================
void CPlayerBehavior_DashAttack001::Cancel(CPlayer* player)
{
	//ゲームシーンの取得
	CGame* pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());

	//ロックオン相手の確認
	if (pGame->GetLockon() != nullptr)
	{
		if (pGame->GetLockon()->GetTarget() != nullptr)
		{
			//ターゲットにダッシュ
			D3DXVECTOR3 TagPos = pGame->GetLockon()->GetTarget()->GetPos();
			D3DXVECTOR3 Length = TagPos - player->GetPos();
			float fLength = sqrtf((Length.x * Length.x) + (Length.z * Length.z));
			fLength = D3DXVec3Length(&Length);	//距離を算出

			//攻撃の範囲外ならダッシュする
			if (fLength > CPlayerBehavior_Dash::STOP_LENGYH)
			{
				SetNextBehavior(new CPlayerBehavior_Move(player));
			}
			else
			{
				//次の攻撃の生成
				SetNextBehavior(new CPlayerBehavior_DashAttack000(player));
				SetRushContinue(true);
			}
		}
	}
}

//============================
//行動処理(攻撃)
//============================
void CPlayerBehavior_DashAttack001::Behavior(CPlayer* player)
{
	//ダッシュ攻撃
	CPlayerBehavior_DashAttack::Behavior(player);
}

//=================================================
//ガード
//=================================================

//============================
//コンストラクタ
//============================
CPlayerBehavior_Guard::CPlayerBehavior_Guard(CPlayer* player) : m_nStiffnessCount(0)
{
	//基本の処理
	player->SetMotion(CPlayer::PLAYERMOTION_GUARD);	//モーション
	player->SetGuardJudge(true);					//ガードをしているか
}

//============================
//行動処理(ガード)
//============================
void CPlayerBehavior_Guard::Behavior(CPlayer* player)
{
	//硬直時間を過ぎていたら抜ける
	if (m_nStiffnessCount <= TIME_FIRST_STIFFNESS)
	{
		m_nStiffnessCount++;
	}

	//発動硬直時間を過ぎたら硬直をやめる
	if (m_nStiffnessCount > TIME_FIRST_STIFFNESS)
	{
		m_bStiffening = false;

		//左クリックを離したら
		if (!CManager::GetInstance()->GetMouse()->GetPress(CInputMouse::MOUSEBUTTON_RIGHT) &&
			!CManager::GetInstance()->GetJoypad()->GetPress(CInputJoypad::JOYKEY_RB))
		{
			//通常状態に変更
			player->GetState()->SetNextState(new CState_Player_Normal(player));
			player->SetGuardJudge(false);
		}
	}
}