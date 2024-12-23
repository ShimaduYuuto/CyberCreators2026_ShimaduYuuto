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

//定数
const D3DXVECTOR3 CPlayerBehavior_Attack::POS_OFFSET{ 0.0f, 20.0f, 30.0f };

//================================================================
//移動
//================================================================

//=========================
//コンストラクタ
//=========================
CPlayerBehavior_Move::CPlayerBehavior_Move(CPlayer* player)
{
	player->SetEnableGravity(true);
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
	if ((CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_SPACE) == true || CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_A)) && player->GetOnStand())
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
//行動の更新
//========================
D3DXVECTOR3 CPlayerBehavior_Move::UpdateMove(CPlayer* player, D3DXVECTOR3& Rotgoal)
{
	//返す用の変数
	D3DXVECTOR3 move = { 0.0f, 0.0f, 0.0f };
	float fRotgoal = 0.0f;
	CCamera* pCamera = CManager::GetInstance()->GetCamera();

	//動いたかの判定用
	bool bMove = false;

	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_A))
	{//Aキーが押された場合
		if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_W))
		{
			move.x += sinf(D3DX_PI * -0.75f - pCamera->GetRot().y) * MOVE_SPEED;
			move.z -= cosf(D3DX_PI * -0.75f - pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = D3DX_PI * 0.75f + pCamera->GetRot().y;
		}
		else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_S))
		{
			move.x += sinf(D3DX_PI * -0.25f - pCamera->GetRot().y) * MOVE_SPEED;
			move.z -= cosf(D3DX_PI * -0.25f - pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = D3DX_PI * 0.25f + pCamera->GetRot().y;
		}
		else
		{
			move.x += sinf(D3DX_PI * -0.5f + pCamera->GetRot().y) * MOVE_SPEED;
			move.z += cosf(D3DX_PI * -0.5f + pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = -(D3DX_PI * -0.5f - pCamera->GetRot().y);
		}

		bMove = true;	//動いた判定
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_D))
	{//Dキーが押された場合

		if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_W))
		{
			move.x += sinf(D3DX_PI * 0.75f - pCamera->GetRot().y) * MOVE_SPEED;
			move.z -= cosf(D3DX_PI * 0.75f - pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = D3DX_PI * -0.75f + pCamera->GetRot().y;
		}
		else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_S))
		{
			move.x += sinf(D3DX_PI * 0.25f - pCamera->GetRot().y) * MOVE_SPEED;
			move.z -= cosf(D3DX_PI * 0.25f - pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = D3DX_PI * -0.25f + pCamera->GetRot().y;
		}
		else
		{
			move.x += sinf(D3DX_PI * 0.5f + pCamera->GetRot().y) * MOVE_SPEED;
			move.z += cosf(D3DX_PI * 0.5f + pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = -(D3DX_PI * 0.5f - pCamera->GetRot().y);
		}

		bMove = true;								//動いた判定
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_W))
	{//Wキーが押された場合
		{
			move.z -= cosf(D3DX_PI + pCamera->GetRot().y) * MOVE_SPEED;
			move.x -= sinf(D3DX_PI + pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = D3DX_PI + pCamera->GetRot().y;
		}

		bMove = true;								//動いた判定
	}
	else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_S))
	{//Sキーが押された場合
		{
			move.z -= cosf(pCamera->GetRot().y) * MOVE_SPEED;
			move.x -= sinf(pCamera->GetRot().y) * MOVE_SPEED;
			Rotgoal.y = pCamera->GetRot().y;
		}

		bMove = true;								//動いた判定
	}

	//動いたかの判定
	if (bMove && player->GetOnStand())
	{
		if (player->GetMotionState() != CPlayer::PLAYERMOTION_WALK)
		{
			//モーションの設定
			player->SetMotion(CPlayer::PLAYERMOTION_WALK);
		}
	}
	else if (player->GetOnStand())	//地面に着いているなら
	{
		if (player->GetMotionState() != CPlayer::PLAYERMOTION_NORMAL)
		{
			//モーションの設定
			player->SetMotion(CPlayer::PLAYERMOTION_NORMAL);
		}
	}

	//移動量を返す
	return move;
}

//============================
//プレイヤーのアクション処理
//============================
void CPlayerBehavior_Move::Action(CPlayer* player)
{
	//左シフトでダッシュを設定
	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_LSHIFT))
	{
		//アクションをしていないなら
		if (GetNextBehavior() == nullptr)
		{
			//ゲームシーンなら判定
			if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
			{
				//ゲームシーンの取得
				CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

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
	}

	//立っていたら
	if (player->GetOnStand())
	{
		//右クリックをしたら
		if (CManager::GetInstance()->GetMouse()->GetPress(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_RIGHT))
		{
			//アクションをしていないなら
			if (GetNextBehavior() == nullptr)
			{
				//ガードを生成
				player->GetState()->SetNextState(new CState_Player_Guard(player));
				return;
			}

		}
		else if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_LEFT))
		{

			//アクションをしていないなら
			if (GetNextBehavior() == nullptr)
			{
				//モーションの設定
				player->SetMotion(CPlayer::PLAYERMOTION_ACTION);

				//通常攻撃を生成
				SetNextBehavior(new CPlayerBehavior_NormalAttack000(player));
			}
		}
	}
	else //空中
	{
		//左クリックをしたら
		if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_LEFT))
		{
			//アクションをしていないなら
			if (GetNextBehavior() == nullptr)
			{
				//モーションの設定
				player->SetMotion(CPlayer::PLAYERMOTION_ACTION);

				//空中攻撃に切り替え
				SetNextBehavior(new CPlayerBehavior_Arial000(player));
			}
		}
		else if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_RIGHT))
		{
			//ゲームシーンなら判定
			if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
			{
				//ゲームシーンの取得
				CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

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
	//モーションの設定をする予定
	player->SetMotion(CPlayer::PLAYERMOTION_JUMP);
	player->SetOnStand(false);		//立っていない状態
	player->SetEnableGravity(false);//重力を受けない
	player->GetPos().y += 0.01f;
}

//============================
//行動(ダッシュ)
//============================
void CPlayerBehavior_Dash::Behavior(CPlayer* player)
{
	//押している間ダッシュする
	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_LSHIFT))
	{
		//返す用の変数
		D3DXVECTOR3 move = { 0.0f, 0.0f, 0.0f };

		//ゲームシーンなら判定
		if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
		{
			//ゲームシーンの取得
			CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

			//ロックオン相手の確認
			if (pGame->GetLockon() != nullptr)
			{
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
				
			}
		}

		//移動量の設定
		player->SetMove({ move.x , move.y, move.z });
	}
	else if(CManager::GetInstance()->GetKeyboard()->GetRerease(DIK_LSHIFT)) //離したらダッシュを終了
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
	m_fAttackLength(0.0f),
	m_HitEnemy(),
	m_nCancelStartTime(0),
	m_nCollisionlTime(0),
	m_nEndCount(0),
	m_nEndTime(0),
	m_OffsetPos({0.0f, 0.0f, 0.0f})
{
	//パラメータの設定
	SetEndTime(END_TIME);
	SetCollisionTime(START_COLLISION);
	SetCancelTime(START_CANCEL);
	SetAttackLength(ATTACK_LENGTH);
	SetOffsetPos(POS_OFFSET);
}

//============================
//コンストラクタ
//============================
CPlayerBehavior_Attack::CPlayerBehavior_Attack(CPlayer* player) :
	m_fAttackLength(0.0f),
	m_HitEnemy(),
	m_nCancelStartTime(0),
	m_nCollisionlTime(0),
	m_nEndCount(0),
	m_nEndTime(0)
{
	//パラメータの設定
	SetEndTime(END_TIME);
	SetCollisionTime(START_COLLISION);
	SetCancelTime(START_CANCEL);
	SetAttackLength(ATTACK_LENGTH);
	SetOffsetPos(POS_OFFSET);

	//SEを鳴らす
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SWING);
}

//============================
//攻撃行動
//============================
void CPlayerBehavior_Attack::Behavior(CPlayer* player)
{
	//カウントが一定以上なら
	if (m_nEndCount > m_nCollisionlTime)
	{
		//ゲームシーンなら判定
		if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
		{
			//ゲームシーンの取得
			CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

			//攻撃判定の生成
			D3DXVECTOR3 AttackPos = player->GetPos();
			AttackPos += {sinf(player->GetRot().y + D3DX_PI) * m_OffsetPos.z, m_OffsetPos.y, cosf(player->GetRot().y + D3DX_PI)* m_OffsetPos.z};

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
				D3DXVECTOR3 EnemyLength = iter->GetCollision()->GetPos() - AttackPos;

				float fXZ = sqrtf(EnemyLength.x * EnemyLength.x + EnemyLength.z * EnemyLength.z); //XZ距離を算出する
				float fXY = sqrtf(EnemyLength.x * EnemyLength.x + EnemyLength.y * EnemyLength.y); //XY距離を算出する
				float fLength = sqrtf(fXZ * fXZ + fXY * fXY);	//距離を算出

				//敵の判定内なら
				if (fLength < m_fAttackLength)
				{
					//ダメージ処理
					Damage(player, iter, 1);

					D3DXVECTOR3 Move = iter->CCharacter::GetMove();

					//落ちていたら少し浮かす
					if (Move.y < 0.0f)
					{
						Move.y = 0.0f;
					}

					iter->CCharacter::SetMove(Move);

					//敵の情報を保存
					m_HitEnemy.push_back(iter);
				}
			}

			//弾との当たり判定
			for (auto& iter : pGame->GetEnemyBulletManager()->GetList())
			{
				//反射済みは飛ばす
				if (iter->GetReflection() || !iter->GetShooting())
				{
					continue;
				}

				//敵の位置を取得
				D3DXVECTOR3 Length = iter->GetCollision()->GetPos() - AttackPos;

				float fXZ = sqrtf(Length.x * Length.x + Length.z * Length.z); //XZ距離を算出する
				float fXY = sqrtf(Length.x * Length.x + Length.y * Length.y); //XY距離を算出する
				float fLength = sqrtf(fXZ * fXZ + fXY * fXY);	//距離を算出

				//敵の判定内なら
				if (fLength < m_fAttackLength + iter->GetCollision()->GetRadius())
				{
					//弾を反射
					iter->Reflection();
					CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_REPEL);	//SE
				}
			}

			//キャンセルのカウント以上になったら
			if (m_nEndCount > m_nCancelStartTime)
			{
				//キャンセルの処理
				Cancel(player);
			}
		}
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
}

//============================
//ダメージを与える処理
//============================
void CPlayerBehavior_Attack::Damage(CPlayer* player, CEnemy* enemy, int damage)
{
	//ダメージ
	if (enemy->SetDamage(damage, player->GetRot().y))
	{
		//ヒット時の処理
		CEffect_HitAttack::Create(enemy->GetCollision()->GetPos());
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_ATTACK);
	}
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
//通常攻撃
//============================
void CPlayerBehavior_NormalAttack::Behavior(CPlayer* player)
{
	//移動量を加算する時間
	if (GetCount() < END_MOVE)
	{
		//ゲームシーンの取得
		CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

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
	player->SetMotion(2);
}

//============================
//キャンセル
//============================
void CPlayerBehavior_NormalAttack000::Cancel(CPlayer* player)
{
	//左クリックをしたら
	if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_LEFT))
	{
		//次の攻撃の生成
		SetNextBehavior(new CPlayerBehavior_NormalAttack001(player));
	}
}

//================================================================
//通常攻撃(2段目)
//================================================================

//============================
//コンストラクタ
//============================
CPlayerBehavior_NormalAttack001::CPlayerBehavior_NormalAttack001(CPlayer* player) : CPlayerBehavior_NormalAttack(player)
{
	player->SetMotion(9);
}

//============================
//キャンセル
//============================
void CPlayerBehavior_NormalAttack001::Cancel(CPlayer* player)
{
	//左クリックをしたら
	if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_LEFT))
	{
		//次の攻撃の生成
		SetNextBehavior(new CPlayerBehavior_NormalAttack002(player));
	}
}

//================================================================
//通常攻撃(3段目)
//================================================================

//============================
//コンストラクタ
//============================
CPlayerBehavior_NormalAttack002::CPlayerBehavior_NormalAttack002(CPlayer* player) : CPlayerBehavior_NormalAttack(player),
	m_bChargeEnd(false),
	m_fChargeRate(0.5f), 
	m_fChargeAcceleration(0.0f),
	m_nCancelCount(0),
	m_pEffect(nullptr)
{
	player->SetMotion(player->PLAYERMOTION_ATTACKCHARGE);

	//パラメータの設定
	SetEndTime(20);
	SetCollisionTime(5);
	SetCancelTime(25);
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

		//攻撃ボタンを離したら攻撃
		if (CManager::GetInstance()->GetMouse()->GetRerease(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_LEFT) || m_fChargeRate >= MAX_RATE)
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
				player->SetMotion(10);
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
	player->SetMotion(4);
	player->SetEnableGravity(false);
	player->SetMove({ player->GetMove().x, 0.0f, player->GetMove().z });
}

//============================
//キャンセル処理
//============================
void CPlayerBehavior_Arial000::Cancel(CPlayer* player)
{
	//左クリックをしたら
	if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_LEFT))
	{
		//次の攻撃の生成
		SetNextBehavior(new CPlayerBehavior_Arial001(player));
	}
}

//============================
//行動処理(攻撃)
//============================
void CPlayerBehavior_Arial000::Behavior(CPlayer* player)
{
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
	player->SetMotion(5);
}

//============================
//キャンセル処理
//============================
void CPlayerBehavior_Arial001::Cancel(CPlayer* player)
{
	//左クリックをしたら
	if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_LEFT))
	{
		//次の攻撃の生成
		SetNextBehavior(new CPlayerBehavior_Arial002(player));
	}
}

//============================
//行動処理(攻撃)
//============================
void CPlayerBehavior_Arial001::Behavior(CPlayer* player)
{
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
	player->SetMotion(6);
}

//============================
//行動処理(攻撃)
//============================
void CPlayerBehavior_Arial002::Behavior(CPlayer* player)
{
	CPlayerBehavior_Attack::Behavior(player);
}

//=================================================
//打ち上げ攻撃
//=================================================

//============================
//コンストラクタ
//============================
CPlayerBehavior_Smash::CPlayerBehavior_Smash(CPlayer* player) :
	m_pImpact(nullptr),
	m_bAttack(false),
	m_bHit(false),
	m_nDelayCount(0),
	m_nSlowTime(0)
{
	m_pImpact = CImpactRange::Create(player->GetPos());
}						//コンストラクタ

//============================
//行動処理(打ち上げ攻撃)
//============================
void CPlayerBehavior_Smash::Behavior(CPlayer* player)
{
	//ゲームシーンのプレイヤーの位置を取得
	CGame* pGame = nullptr;
	pGame = (CGame*)CManager::GetInstance()->GetScene();	//ゲームシーンの取得
	D3DXVECTOR3 Pos = pGame->GetGamePlayer()->GetPos();		//位置の取得

	//攻撃をしていなかったら
	if (!m_bAttack)
	{
		//右ボタンを離したら当たり判定を確認
		if (CManager::GetInstance()->GetMouse()->GetRerease(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_RIGHT))
		{
			//敵の周回
			for (auto& iter : pGame->GetEnemyManager()->GetList())
			{
				//位置の取得
				D3DXVECTOR3 Pos = m_pImpact->GetPos();
				D3DXVECTOR3 EnemyPos = iter->GetPos();

				//距離を計算
				float fLength = sqrtf((EnemyPos.x - Pos.x) * (EnemyPos.x - Pos.x) + (EnemyPos.z - Pos.z) * (EnemyPos.z - Pos.z));

				//範囲内の確認
				if (fLength < m_pImpact->GetSize().x * m_pImpact->GetRate() * 0.5f)
				{
					//吹き飛び処理
					if (iter->SetBlowOff())
					{
						m_nSlowTime += ADD_SLOWTIME; //	スロー時間の追加

						//フラグがオフならオンにする
						if (!m_bHit)
						{
							m_bHit = true;
						}
					}
				}
			}

			//インパクトの範囲がnullなら
			if (m_pImpact != nullptr)
			{
				//生成
				m_pImpact->Uninit();
				m_pImpact = nullptr;
			}

			//攻撃判定をオン
			m_bAttack = true;
			CManager::GetInstance()->GetCamera()->SetShake(15, 15);	//ヒット時カメラを揺らす
		}
	}

	//攻撃をしたら
	if (m_bAttack)
	{
		//カウントの加算
		m_nDelayCount++;

		//遅延のカウントが指定値になったら
		if (m_nDelayCount >= DELAY_TIME)
		{
			//当たっていたらカウント
			if (m_bHit)
			{
				//遅延のカウントが指定値になったら
				if (m_nDelayCount >= DELAY_TIME)
				{
					//ゲームシーンのプレイヤーの位置を取得
					CGame* pGame = nullptr;
					pGame = (CGame*)CManager::GetInstance()->GetScene();	//ゲームシーンの取得
					pGame->GetTime()->SetStateTimer(pGame->GetTime()->TIME_SLOW, m_nSlowTime);	//時間の状態を設定
					CGauge_Slow::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.8f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.05f, 0.0f), (float)m_nSlowTime);
				}
			}
			
			//行動を移動に変更
			SetNextBehavior(new CPlayerBehavior_Move(player));
		}
	}

	//インパクトの範囲がnullなら
	if (m_pImpact != nullptr)
	{
		//位置の更新
		m_pImpact->SetPos(Pos);
	}
}

//=================================================
//ダッシュ攻撃(1段目)
//=================================================

//============================
//コンストラクタ
//============================
CPlayerBehavior_DashAttack000::CPlayerBehavior_DashAttack000(CPlayer* player) : CPlayerBehavior_DashAttack(player)
{
	player->SetMotion(player->PLAYERMOTION_DASHATTACK000);
	player->SetEnableGravity(false);
	player->SetMove({ player->GetMove().x, 0.0f, player->GetMove().z });
}

//============================
//キャンセル処理
//============================
void CPlayerBehavior_DashAttack000::Cancel(CPlayer* player)
{
	//左クリックをしたら
	if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_LEFT))
	{
		//ゲームシーンの取得
		CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

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
					SetNextBehavior(new CPlayerBehavior_Dash(player));
				}
				else
				{
					//次の攻撃の生成
					SetNextBehavior(new CPlayerBehavior_DashAttack001(player));
				}
			}
		}
	}
}

//============================
//行動処理(攻撃)
//============================
void CPlayerBehavior_DashAttack000::Behavior(CPlayer* player)
{
	CPlayerBehavior_Attack::Behavior(player);
}

//=================================================
//ダッシュ攻撃(2段目)
//=================================================

//============================
//コンストラクタ
//============================
CPlayerBehavior_DashAttack001::CPlayerBehavior_DashAttack001(CPlayer* player) : CPlayerBehavior_DashAttack(player)
{
	player->SetMotion(player->PLAYERMOTION_DASHATTACK001);
}

//============================
//キャンセル処理
//============================
void CPlayerBehavior_DashAttack001::Cancel(CPlayer* player)
{
	//左クリックをしたら
	if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_LEFT))
	{
		//ゲームシーンの取得
		CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

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
					SetNextBehavior(new CPlayerBehavior_Dash(player));
				}
				else
				{
					//次の攻撃の生成
					SetNextBehavior(new CPlayerBehavior_DashAttack000(player));
				}
			}
		}
	}
}

//============================
//行動処理(攻撃)
//============================
void CPlayerBehavior_DashAttack001::Behavior(CPlayer* player)
{
	CPlayerBehavior_Attack::Behavior(player);
}

//=================================================
//カウンター攻撃
//=================================================

//============================
//行動処理(攻撃)
//============================
CPlayerBehavior_CounterAttack::CPlayerBehavior_CounterAttack(CPlayer* player)
{
	//パラメータの設定
	SetCancelTime(START_CANCELTIME);	//キャンセル
	SetEndTime(END_TIME);				//終了時間
	SetCollisionTime(START_COLLISION);	//当たり判定
	SetAttackLength(ATTACK_LENGTH);		//攻撃の距離
	SetOffsetPos({ 0.0f, 30.0f, 0.0f });//オフセットは無し
	player->SetMotion(CPlayer::PLAYERMOTION_ACTION002);
}

//============================
//行動処理(攻撃)
//============================
void CPlayerBehavior_CounterAttack::Behavior(CPlayer* player)
{
	CPlayerBehavior_Attack::Behavior(player);
}

//============================
//行動処理(通常状態に変更)
//============================
void CPlayerBehavior_CounterAttack::NextBehavior(CPlayer* player)
{
	player->GetState()->SetNextState(new CState_Player_Normal(player));
}

//============================
//攻撃ヒット時の処理
//============================
void CPlayerBehavior_CounterAttack::Damage(CPlayer* player, CEnemy* enemy, int damage)
{
	D3DXVECTOR3 Vector = enemy->GetCollision()->GetPos() - player->GetCollision()->GetPos();
	float fAngle = atan2f(Vector.x, Vector.z);

	//ダメージ
	enemy->SetBlowDamage(damage, fAngle + D3DX_PI, 10.0f);
}

//=================================================
//ガード
//=================================================

//============================
//コンストラクタ
//============================
CPlayerBehavior_Guard::CPlayerBehavior_Guard(CPlayer* player) : m_nStiffnessCount(0)
{
	player->SetMotion(CPlayer::PLAYERMOTION_GUARD);
}

//============================
//行動処理(ガード)
//============================
void CPlayerBehavior_Guard::Behavior(CPlayer* player)
{
	//左クリックを離したら
	if (!CManager::GetInstance()->GetMouse()->GetPress(CInputMouse::MOUSEBUTTON_RIGHT))
	{
		//通常状態に変更
		player->GetState()->SetNextState(new CState_Player_Normal(player));
	}
}