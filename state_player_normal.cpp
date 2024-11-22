//================================
//
//通常状態処理[state_player_normal.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "state_player_normal.h"
//#include "manager.h"
//#include "game.h"
#include "state_player_damage.h"
//#include "gauge_playerlife.h"
//#include "smash.h"
//#include "normalattack000.h"
//#include "arial000.h"
//
////静的メンバの初期化
//const float CState_Player_Normal::MOVE_SPEED = 2.0f;
//const float CState_Player_Normal::GRAVITY_SPEED = 0.6f;
//const float CState_Player_Normal::JUMP_SPEED = 14.0f;
//
////========================
////行動の処理
////========================
//void CState_Player_Normal::Move(CPlayer* player)
//{
//	//ローカル変数宣言
//	D3DXVECTOR3 pos = player->GetPos();				//位置の取得
//	D3DXVECTOR3 goalrot = player->GetGoalRot();		//目的の向きの取得
//	D3DXVECTOR3 move = player->GetMove();			//移動量の取得
//
//	//Xファイルの読み込み
//	CXfile* pCXfile = CManager::GetInstance()->GetXfile();
//
//	//ジャンプ
//	if ((CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_SPACE) == true || CManager::GetInstance()->GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_A)) && player->GetOnStand())
//	{//SPACEが押された場合
//		move.y += JUMP_SPEED;
//		player->SetOnStand(false);
//		player->SetMotion(CPlayer::PLAYERMOTION_JUMP);
//	}
//
//	//移動量の更新
//	move += UpdateMove(player, goalrot);
//
//	//パラメータの設定
//	player->SetPos(pos);			//位置
//	player->SetGoalRot(goalrot);	//目的の向き
//	player->SetMove(move);			//移動量
//
//	//アクション処理
//	Action(player);
//
//	//共通処理の更新
//	player->CCharacter::Update();
//
//	//パラメータの取得
//	pos = player->GetPos();
//	move = player->GetMove();
//
//	//アクションをしていないなら
//	if (player->GetAction() == nullptr)
//	{
//		//立ち状態
//		if (player->GetOnStand())
//		{
//			//歩いていないならモーションを変える
//			if (player->GetMotionState() != CPlayer::PLAYERMOTION_WALK)
//			{
//				player->SetMotion(CPlayer::PLAYERMOTION_NORMAL);
//			}
//		}
//		else
//		{
//			//ジャンプのモーション
//			player->SetMotion(CPlayer::PLAYERMOTION_JUMP);
//		}
//	}
//
//	player->SetMove(move);			//移動量の設定
//}
//
////========================
////行動の更新
////========================
//D3DXVECTOR3 CState_Player_Normal::UpdateMove(CPlayer* player, D3DXVECTOR3& Rotgoal)
//{
//	//空中にいてアクション中なら抜ける
//	if (player->GetAction() != nullptr)
//	{
//		return { 0.0f, 0.0f, 0.0f };
//	}
//
//	//返す用の変数
//	D3DXVECTOR3 move = { 0.0f, 0.0f, 0.0f };
//	float fRotgoal = 0.0f;
//	CCamera* pCamera = CManager::GetInstance()->GetCamera();
//
//	//動いたかの判定用
//	bool bMove = false;
//
//	if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_A))
//	{//Aキーが押された場合
//		if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_W))
//		{
//			move.x += sinf(D3DX_PI * -0.75f - pCamera->GetRot().y) * CState_Player_Normal::MOVE_SPEED;
//			move.z -= cosf(D3DX_PI * -0.75f - pCamera->GetRot().y) * CState_Player_Normal::MOVE_SPEED;
//			Rotgoal.y = D3DX_PI * 0.75f + pCamera->GetRot().y;
//		}
//		else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_S))
//		{
//			move.x += sinf(D3DX_PI * -0.25f - pCamera->GetRot().y) * CState_Player_Normal::MOVE_SPEED;
//			move.z -= cosf(D3DX_PI * -0.25f - pCamera->GetRot().y) * CState_Player_Normal::MOVE_SPEED;
//			Rotgoal.y = D3DX_PI * 0.25f + pCamera->GetRot().y;
//		}
//		else
//		{
//			move.x += sinf(D3DX_PI * -0.5f + pCamera->GetRot().y) * CState_Player_Normal::MOVE_SPEED;
//			move.z += cosf(D3DX_PI * -0.5f + pCamera->GetRot().y) * CState_Player_Normal::MOVE_SPEED;
//			Rotgoal.y = -(D3DX_PI * -0.5f - pCamera->GetRot().y);
//		}
//
//		bMove = true;	//動いた判定
//	}
//	else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_D))
//	{//Dキーが押された場合
//
//		if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_W))
//		{
//			move.x += sinf(D3DX_PI * 0.75f - pCamera->GetRot().y) * CState_Player_Normal::MOVE_SPEED;
//			move.z -= cosf(D3DX_PI * 0.75f - pCamera->GetRot().y) * CState_Player_Normal::MOVE_SPEED;
//			Rotgoal.y = D3DX_PI * -0.75f + pCamera->GetRot().y;
//		}
//		else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_S))
//		{
//			move.x += sinf(D3DX_PI * 0.25f - pCamera->GetRot().y) * CState_Player_Normal::MOVE_SPEED;
//			move.z -= cosf(D3DX_PI * 0.25f - pCamera->GetRot().y) * CState_Player_Normal::MOVE_SPEED;
//			Rotgoal.y = D3DX_PI * -0.25f + pCamera->GetRot().y;
//		}
//		else
//		{
//			move.x += sinf(D3DX_PI * 0.5f + pCamera->GetRot().y) * CState_Player_Normal::MOVE_SPEED;
//			move.z += cosf(D3DX_PI * 0.5f + pCamera->GetRot().y) * CState_Player_Normal::MOVE_SPEED;
//			Rotgoal.y = -(D3DX_PI * 0.5f - pCamera->GetRot().y);
//		}
//
//		bMove = true;								//動いた判定
//	}
//	else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_W))
//	{//Wキーが押された場合
//		{
//			move.z -= cosf(D3DX_PI + pCamera->GetRot().y) * CState_Player_Normal::MOVE_SPEED;
//			move.x -= sinf(D3DX_PI + pCamera->GetRot().y) * CState_Player_Normal::MOVE_SPEED;
//			Rotgoal.y = D3DX_PI + pCamera->GetRot().y;
//		}
//
//		bMove = true;								//動いた判定
//	}
//	else if (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_S))
//	{//Sキーが押された場合
//		{
//			move.z -= cosf(pCamera->GetRot().y) * CState_Player_Normal::MOVE_SPEED;
//			move.x -= sinf(pCamera->GetRot().y) * CState_Player_Normal::MOVE_SPEED;
//			Rotgoal.y = pCamera->GetRot().y;
//		}
//
//		bMove = true;								//動いた判定
//	}
//
//	//動いたかの判定
//	if (bMove && player->GetOnStand())
//	{
//		//モーションの設定
//		player->SetMotion(CPlayer::PLAYERMOTION_WALK);
//	}
//	else if (player->GetOnStand())	//地面に着いているなら
//	{
//		//モーションの設定
//		player->SetMotion(CPlayer::PLAYERMOTION_NORMAL);
//	}
//
//	//移動量を返す
//	return move;
//}
//
////============================
////ジャンプの計算処理
////============================
//D3DXVECTOR3 CState_Player_Normal::JumpCalculation(CPlayer* player, D3DXVECTOR3 move)
//{
//	//重力を加算
//	move.y -= GRAVITY_SPEED;
//
//	//通常の状態なら処理
//	//if (player->GetDamageState() == CCharacter::DAMAGESTATE_NORMAL)
//	{
//		//ジャンプのボタンを離したら
//		if (move.y > 0.0f && (CManager::GetInstance()->GetKeyboard()->GetPress(DIK_SPACE) == false && !CManager::GetInstance()->GetJoypad()->GetPress(CInputJoypad::JOYKEY_A)))
//		{
//			//徐々に移動量を減速
//			move.y *= 0.9f;
//		}
//	}
//
//	//移動量を返す
//	return move;
//}
//
////============================
////プレイヤーのアクション処理
////============================
//void CState_Player_Normal::Action(CPlayer*& player)
//{
//	CAction_Player* pAction = player->GetAction();
//
//	//立っていたら
//	if (player->GetOnStand())
//	{
//		//右クリックをしたら
//		if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_RIGHT))
//		{
//			//アクションをしていないなら
//			if (pAction == nullptr)
//			{
//				//スマッシュアクションを生成
//				pAction = player->ChangeAction(new CSmash());
//			}
//
//		}
//		else if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_LEFT))
//		{
//
//			//アクションをしていないなら
//			if (pAction == nullptr)
//			{
//				//モーションの設定
//				player->SetMotion(CPlayer::PLAYERMOTION_ACTION);
//
//				//通常攻撃を生成
//				pAction = player->ChangeAction(new CNormalAttack000());
//			}
//		}
//	}
//	else //空中
//	{
//		//左クリックをしたら
//		if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_LEFT))
//		{
//			//アクションをしていないなら
//			if (pAction == nullptr)
//			{
//				//モーションの設定
//				player->SetMotion(CPlayer::PLAYERMOTION_ACTION);
//
//				//アクションの切り替え
//				pAction = player->ChangeAction(new CArial000());
//			}
//		}
//		else if (CManager::GetInstance()->GetMouse()->GetTrigger(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_RIGHT))
//		{
//			//ゲームシーンなら判定
//			if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
//			{
//				//ゲームシーンの取得
//				CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();
//
//				//ロックオンの設定
//				pGame->SetLockon(true);
//			}
//		}
//	}
//
//	//アクションの更新処理
//	if (pAction != nullptr)
//	{
//		//アクションの更新
//		pAction->Update();
//
//		//軌跡の設定
//		player->SetOrbit(true);
//
//		//アクションが終了していたら
//		if (pAction->GetEndAction())
//		{
//			//次のアクションがあるなら
//			if (pAction->GetNextAction() != nullptr)
//			{
//				//ローカルに保存
//				CAction_Player* NextAction = pAction->GetNextAction();
//
//				//次の行動を設定
//				pAction = NextAction;
//
//				//軌跡の設定
//				player->SetOrbit(false);
//
//				//新しくアクションを生成
//				pAction = player->ChangeAction(pAction);
//			}
//			else
//			{
//				//消去
//				delete pAction;
//				pAction = nullptr;
//
//				//軌跡の設定
//				player->SetOrbit(false);
//			}
//		}
//	}
//
//	//アクションの設定
//	player->SetAction(pAction);
//}
//
//========================
//ダメージの設定
//========================
void CState_Player_Normal::SetDamage(CPlayer* player, int damage)
{
	//死亡フラグが立っていたら抜ける
	if (player->GetDeath())
	{
		return;
	}

	//ダメージを受ける
	player->CCharacter::SetDamage(damage);
	//player->SetDamageState(CCharacter::DAMAGESTATE_INVINCIBLE, 20);	//30フレームの間無敵
	player->SetMotion(8);											//モーションの設定
	SetNextState(new CState_Player_Damage(player));					//ステートの設定

	//ノックバックの移動量を設定
	D3DXVECTOR3 Rot = player->GetRot();
	D3DXVECTOR3 Move = player->GetMove();
	D3DXVECTOR3 AddMove = { sinf(Rot.y) * 10.0f, 0.0f, cosf(Rot.y) * 10.0f };

	//移動量の加算
	Move += AddMove;
	player->SetMove(Move);

	//インスタンスの取得
	CGauge_PlayerLife* pGauge = player->GetLifeGauge();

	//体力ゲージに反映
	if (pGauge != nullptr)
	{
		//ゲージに反映
		pGauge->GetGauge()->AddGauge(-(float)damage);
	}

	player->SetLifeGauge(pGauge);
}