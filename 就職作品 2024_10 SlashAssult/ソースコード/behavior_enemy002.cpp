//================================
//
//敵の行動まとめ[behavior_enemy002.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "behavior_enemy002.h"
#include "enemy002.h"
#include "enemybullet.h"
#include "game.h"
#include "manager.h"
#include "effect_death_boss.h"
#include "effect_explosion.h"
#include "direction_boss_destroy.h"

//======================================================================
//待機
//======================================================================

//====================================
//コンストラクタ
//====================================
CEnemyBehavior_Standby::CEnemyBehavior_Standby(CEnemy* enemy) : m_nCoolTime(0)
{
	//設定
	enemy->SetMotion(CEnemy002::ENEMY002MOTION_NORMAL);	//モーション
	m_nCoolTime = COOL_TIME;							//クールタイム
	enemy->SetCollisionProcess(true);					//当たり判定の処理を行う
};

//====================================
//アクション(待機)
//====================================
void CEnemyBehavior_Standby::Action(CEnemy* enemy)
{
	//クールタイムを減らす
	m_nCoolTime--;

	//クールタイムが終わったら次の行動を行う
	if (m_nCoolTime < 0)
	{
		NextAction(enemy);
	}
}

//====================================
//次の行動を設定
//====================================
void CEnemyBehavior_Standby::NextAction(CEnemy* enemy)
{
	//消える
	SetNextAction(new CEnemyBehavior_Disappear(enemy));
}

//======================================================================
//消える時間
//======================================================================

//====================================
//コンストラクタ
//====================================
CEnemyBehavior_Disappear::CEnemyBehavior_Disappear(CEnemy* enemy) : m_nDisappearTime(0)
{
	//基本の設定
	enemy->SetMotion(CEnemy002::ENEMY002MOTION_NORMAL);	//モーション
	m_nDisappearTime = DISAPPEAR_TIME;					//クールタイム
	enemy->SetCollisionProcess(false);					//当たり判定の処理
	
	//固有の設定
	CEnemy002* pEnemy002 = dynamic_cast<CEnemy002*>(enemy);
	pEnemy002->SetAlpha(0.0f);	//透明になる
};

//====================================
//アクション(待機)
//====================================
void CEnemyBehavior_Disappear::Action(CEnemy* enemy)
{
	//クールタイムを減らす
	m_nDisappearTime--;

	//クールタイムが終わったら次の行動を行う
	if (m_nDisappearTime < 0)
	{
		//次の行動を設定
		NextAction(enemy);

		//固有の設定
		CEnemy002* pEnemy002 = dynamic_cast<CEnemy002*>(enemy);
		pEnemy002->SetAlpha(CEnemy002::VALUE_INVISIBLE_ALPHA);	//透明になる
	}
}

//====================================
//次の行動を設定
//====================================
void CEnemyBehavior_Disappear::NextAction(CEnemy* enemy)
{
	//残り体力に応じて行動を変化
	if (enemy->GetLife() > LIFE_FIRST_ATTACK)
	{
		//攻撃する
		SetNextAction(new CEnemyBehavior_WarpShot(enemy));
	}
	else
	{
		//攻撃する
		SetNextAction(new CEnemyBehavior_AlterEgoAttack(enemy));
	}
}

//======================================================================
//チャージショット
//======================================================================

//====================================
//コンストラクタ
//====================================
CEnemyBehavior_ChargeShot::CEnemyBehavior_ChargeShot(CEnemy* enemy) : 
	m_nChargeCount(0),	//チャージカウント
	m_pBullet(nullptr), //弾のポインタ
	m_pEffect(nullptr), //エフェクトのポインタ
	m_bNext(false)		//次の行動の移行フラグ
{
	//設定
	enemy->SetMotion(CEnemy002::ENEMY002MOTION_CHARGESHOT);	//モーション
	enemy->SetCollisionProcess(false);
};

//====================================
//デストラクタ
//====================================
CEnemyBehavior_ChargeShot::~CEnemyBehavior_ChargeShot()
{
	//弾の破棄
	if (m_pBullet != nullptr)
	{
		m_pBullet->Uninit();
		m_pBullet = nullptr;

		//エフェクトの破棄
		if (m_pEffect != nullptr)
		{
			m_pEffect->Uninit();
			m_pEffect = nullptr;
		}
	}
}

//====================================
//アクション(チャージショット)
//====================================
void CEnemyBehavior_ChargeShot::Action(CEnemy* enemy)
{
	//カウントが回り切っていないなら更新
	if (m_nChargeCount <= CHARGE_TIME)
	{
		//カウントの更新
		m_nChargeCount++;

		//プレイヤーの方向を向く
		LookAtPlayer(enemy);

		//確認後、弾の生成
		if (CanCreateBullet())
		{
			CreateBullet(enemy);
		}

		//弾が生成済みなら
		if (m_pBullet != nullptr)
		{
			UpdateBullet(enemy);
		}
	}

	//当たっていたら消す
	if (CheckBulletHit())
	{
		HitBullet();
	}

	//フラグが立っていたら次の行動へ
	if (m_bNext)
	{
		NextAction(enemy);
	}
}

//====================================
//プレイヤーの方向を向く
//====================================
void CEnemyBehavior_ChargeShot::LookAtPlayer(CEnemy* enemy)
{
	//プレイヤーの角度を取得
	CGame* pGame = nullptr;
	pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());	//ゲームシーンの取得
	D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();			//プレイヤーの位置を取得
	D3DXVECTOR3 Pos = enemy->GetPos();									//自分の位置を取得

	//プレイヤーとの角度を算出
	float fAngle = atan2f(PlayerPos.x - Pos.x, PlayerPos.z - Pos.z);//対角線の角度を算出

	//角度を設定
	enemy->SetGoalRot({ enemy->GetRot().x, fAngle + D3DX_PI, enemy->GetRot().z });
}

//====================================
//弾の生成が可能かを確認
//====================================
bool CEnemyBehavior_ChargeShot::CanCreateBullet()
{
	//確認
	if (m_nChargeCount <= CREATE_BULLET_TIME) return false;	//カウントが上回っているなら通す
	if (m_pBullet != nullptr) return false;					//弾はまだ生成されていないなら通す

	return true;
}

//====================================
//弾の生成
//====================================
void CEnemyBehavior_ChargeShot::CreateBullet(CEnemy* enemy)
{
	//弾とエフェクトの生成
	m_pBullet = CEnemyBullet::Create(enemy->GetCollision()->GetPos(), { 0.0f, 0.0f, 0.0f }, this, enemy);	//弾の生成
	m_pEffect = CEffect_ChargeShot::Create(enemy->GetCollision()->GetPos());								//エフェクトの生成

	//SEの設定
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_CHARGE001);
}

//====================================
//弾の更新
//====================================
void CEnemyBehavior_ChargeShot::UpdateBullet(CEnemy* enemy)
{
	//プレイヤーの取得
	CGame* pGame = nullptr;
	pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());	//ゲームシーンの取得
	D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();			//プレイヤーの位置を取得
	D3DXVECTOR3 Pos = enemy->GetPos();									//自分の位置を取得

	//プレイヤーとの角度を算出
	float fAngle = atan2f(PlayerPos.x - Pos.x, PlayerPos.z - Pos.z);//対角線の角度を算出

	//弾を大きくする
	EnlargeBullet(enemy, fAngle);

	//エフェクトの位置を更新
	m_pEffect->SetPos(enemy->GetCollision()->GetPos());

	//チャージ時間を終えたら発射
	if (m_nChargeCount > CHARGE_TIME)
	{
		ShotBullet(fAngle);
	}
}

//====================================
//弾を大きくする
//====================================
void CEnemyBehavior_ChargeShot::EnlargeBullet(CEnemy* enemy, float angle)
{
	//スケールを大きくする
	m_pBullet->AddSizeRate(ADD_SCALE_VALUE);

	//大きさに応じて弾の距離を敵から遠くする
	m_pBullet->SetPos({ enemy->GetCollision()->GetPos().x + sinf(angle) * BULLET_LENGTH * m_pBullet->GetSizeRate(),
		enemy->GetCollision()->GetPos().y,
		enemy->GetCollision()->GetPos().z + cosf(angle) * BULLET_LENGTH * m_pBullet->GetSizeRate() });

}

//====================================
//弾を発射する
//====================================
void CEnemyBehavior_ChargeShot::ShotBullet(float angle)
{
	//向いている方向に撃つ
	m_pBullet->SetMove({ sinf(angle) * BULLET_SPEED, 0.0f, cosf(angle) * BULLET_SPEED });
	m_pBullet->SetShooting(true);

	//SEの設定
	CManager::GetInstance()->GetSound()->Stop(CSound::SOUND_LABEL_CHARGE001);	//チャージ音を止める
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SHOT);	//発射音を止める

	//エフェクトの破棄
	if (m_pEffect != nullptr)
	{
		m_pEffect->Uninit();
		m_pEffect = nullptr;
	}
}

//====================================
//弾が当たっているかを確認
//====================================
bool CEnemyBehavior_ChargeShot::CheckBulletHit()
{
	//確認
	if (m_pBullet == nullptr) return false;		//弾が残っているなら通す
	if (!m_pBullet->GetDeath()) return false;	//弾の死亡フラグが立っているなら通す

	return true;
}

//====================================
//弾がヒット時の処理
//====================================
void CEnemyBehavior_ChargeShot::HitBullet()
{
	m_pBullet = nullptr;	//弾のポインタを持たない
	m_bNext = true;			//次の行動へ移行フラグを立てる
}

//====================================
//次の行動を設定
//====================================
void CEnemyBehavior_ChargeShot::NextAction(CEnemy* enemy)
{
	//待機行動を設定
	SetNextAction(new CEnemyBehavior_Standby(enemy));
}

//====================================
//弾のポインタの削除
//====================================
void CEnemyBehavior_ChargeShot::Erase(CEnemyBullet* bullet)
{
	//同じポインタなら中身をnullptrにする
	if (m_pBullet == bullet)
	{
		m_pBullet = nullptr;
		m_bNext = true;
	}
}

//======================================================================
//ワープショット
//======================================================================

//====================================
//コンストラクタ
//====================================
CEnemyBehavior_WarpShot::CEnemyBehavior_WarpShot(CEnemy* enemy) : CEnemyBehavior_ChargeShot(enemy)
{
	//設定
	enemy->SetMotion(CEnemy002::ENEMY002MOTION_CHARGESHOT);	//モーション

	//ランダムな位置に敵を生成
	enemy->SetPos(D3DXVECTOR3(sinf(CRandom::GetInstance()->GetRandom(-D3DX_PI, D3DX_PI)) * CRandom::GetInstance()->GetRandom(0.0f, MAX_RUNDOM_LENGTH)
		, 0.0f
		, cosf(CRandom::GetInstance()->GetRandom(-D3DX_PI, D3DX_PI)) * CRandom::GetInstance()->GetRandom(0.0f, MAX_RUNDOM_LENGTH)) + enemy->GetStartPos());
};

//====================================
//デストラクタ
//====================================
CEnemyBehavior_WarpShot::~CEnemyBehavior_WarpShot()
{
	
}

//====================================
//アクション(チャージショット)
//====================================
void CEnemyBehavior_WarpShot::Action(CEnemy* enemy)
{
	//チャージショットの更新
	CEnemyBehavior_ChargeShot::Action(enemy);
}

//====================================
//次の行動を設定
//====================================
void CEnemyBehavior_WarpShot::NextAction(CEnemy* enemy)
{
	//待機状態の設定
	SetNextAction(new CEnemyBehavior_Standby(enemy));
}

//======================================================================
//登場演出
//======================================================================

//====================================
//コンストラクタ
//====================================
CEnemyBehavior_Direction::CEnemyBehavior_Direction(CEnemy* enemy) :
	m_nCount(0)
{
	//基本の設定
	enemy->SetMotion(CEnemy002::ENEMY002MOTION_DIRECTION);	//モーション

	//ゲームシーンに演出を設定
	CGame* pGame = nullptr;
	pGame = dynamic_cast<CGame*>(CManager::GetInstance()->GetScene());	//ゲームシーンの取得
	pGame->SetDirection(CDirection::DIRECTIONTYPE_BOSS);				//演出の設定

	//固有の設定
	CEnemy002* pEnemy002 = dynamic_cast<CEnemy002*>(enemy);	//ダウンキャスト
	pEnemy002->SetMaterialized(true);						//実体化の判定					
}

//====================================
//アクション(演出)
//====================================
void CEnemyBehavior_Direction::Action(CEnemy* enemy)
{
	//カウントの増加
	m_nCount++;

	//演出の時間を迎えたら次の行動を設定
	if (m_nCount > DIRECTION_TIME)
	{
		NextAction(enemy);
	}
}

//====================================
//次の行動を設定
//====================================
void CEnemyBehavior_Direction::NextAction(CEnemy* enemy)
{
	//待機行動を設定
	SetNextAction(new CEnemyBehavior_Standby(enemy));
}

//======================================================================
//分身攻撃
//======================================================================

//====================================
//コンストラクタ
//====================================
CEnemyBehavior_AlterEgoAttack::CEnemyBehavior_AlterEgoAttack(CEnemy* enemy) : CEnemyBehavior_ChargeShot(enemy),
	m_pShotAction(nullptr),		//アクションのポインタ
	m_bCreateAlterEgo(false),	//分身を生成したか
	m_pAlterEgo(),				//分身のポインタ
	m_fRundam(0.0f)				//ランダム値
{
	//設定
	enemy->SetMotion(CEnemy002::ENEMY002MOTION_NORMAL);	//モーション

	//分身のポインタを初期化
	for (int i = 0; i < NUM_ALTEREGO; i++)
	{
		m_pAlterEgo[i] = nullptr;
	}

	//本体の設定
	m_fRundam = CRandom::GetInstance()->GetRandom(-D3DX_PI, D3DX_PI);
	enemy->SetPos(D3DXVECTOR3(sinf(m_fRundam) * LENGTH_ENEMY, 0.0f, cosf(m_fRundam) * LENGTH_ENEMY) + enemy->GetStartPos());	//位置の設定
	enemy->SetMotion(CEnemy002::ENEMY002MOTION_CHARGESHOT);																		//モーションの設定

	//分身を生成
	for (int i = 0; i < NUM_ALTEREGO; i++)
	{
		float fAngle = (D3DX_PI * 2.0f) / (NUM_ALTEREGO + 1) * (i + 1) + m_fRundam;	//角度を算出
		D3DXVECTOR3 Pos = (D3DXVECTOR3(
			sinf(fAngle) * LENGTH_ENEMY,
			0.0f,
			cosf(fAngle) * LENGTH_ENEMY));	//位置を算出

		//生成
		m_pAlterEgo[i] = CEnemy002_AlterEgo::Create(Pos + enemy->GetStartPos(), this);
	}
}

//====================================
//デストラクタ
//====================================
CEnemyBehavior_AlterEgoAttack::~CEnemyBehavior_AlterEgoAttack()
{
	//分身を破棄
	for (int i = 0; i < NUM_ALTEREGO; i++)
	{
		if (m_pAlterEgo[i] != nullptr)
		{
			m_pAlterEgo[i]->Uninit();
			m_pAlterEgo[i] = nullptr;
		}
	}
}

//====================================
//アクション(分身)
//====================================
void CEnemyBehavior_AlterEgoAttack::Action(CEnemy* enemy)
{
	//ローカル変数
	int nNumAlterEgo = 0;		//現在の分身の数

	//分身を更新
	for (int i = 0; i < NUM_ALTEREGO; i++)
	{
		//存在しない、または死亡しているなら更新しない
		if (m_pAlterEgo[i] == nullptr || m_pAlterEgo[i]->GetDeath())
		{
			m_pAlterEgo[i] = nullptr;
			continue;
		}

		//更新
		nNumAlterEgo++;
	}

	//位置の更新
	UpdatePos(enemy);

	//分身がいないなら移行
	if (nNumAlterEgo == 0 && GetBullet() == nullptr)
	{
		SetNextFlag(true);
	}

	//アクション
	CEnemyBehavior_ChargeShot::Action(enemy);
}

//====================================
//位置の更新
//====================================
void CEnemyBehavior_AlterEgoAttack::UpdatePos(CEnemy* enemy)
{
	//弾の発射状況を確認
	if (GetBullet() == nullptr) return;
	if (GetBullet()->GetShooting()) return;

	//本体の設定
	m_fRundam += ADD_RUNDOM;
	enemy->SetPos(D3DXVECTOR3(sinf(m_fRundam) * LENGTH_ENEMY, 0.0f, cosf(m_fRundam) * LENGTH_ENEMY) + enemy->GetStartPos());

	//分身を生成
	for (int i = 0; i < NUM_ALTEREGO; i++)
	{
		//分身の確認
		if (m_pAlterEgo[i] == nullptr) continue;

		//位置を設定
		float fAngle = (D3DX_PI * 2.0f) / (NUM_ALTEREGO + 1) * (i + 1) + m_fRundam;	//角度を算出
		D3DXVECTOR3 Pos = (D3DXVECTOR3(
			sinf(fAngle) * LENGTH_ENEMY,
			0.0f,
			cosf(fAngle) * LENGTH_ENEMY));	//位置を算出

		m_pAlterEgo[i]->SetPos(Pos + enemy->GetStartPos());	//位置の設定
	}
}

//====================================
//分身のポインタの削除
//====================================
void CEnemyBehavior_AlterEgoAttack::Erase(CEnemy002_AlterEgo* enemy)
{
	//配列分周回
	for (int i = 0; i < NUM_ALTEREGO; i++)
	{
		//保持している分身がいるならnullptrにする
		if (m_pAlterEgo[i] == enemy)
		{
			m_pAlterEgo[i] = nullptr;
		}
	}
}

//====================================
//次の行動を設定
//====================================
void CEnemyBehavior_AlterEgoAttack::NextAction(CEnemy* enemy)
{
	//待機行動を設定
	SetNextAction(new CEnemyBehavior_Standby(enemy));
}

//======================================================================
//撃破演出
//======================================================================

//定数
const D3DXVECTOR3 CEnemyBehavior_Direction_Destroy::CAMERA_POSV = { 0.0f, 0.0f, -200.0f };

//====================================
//コンストラクタ
//====================================
CEnemyBehavior_Direction_Destroy::CEnemyBehavior_Direction_Destroy(CEnemy* enemy) :
	m_nCount(0)
{
	//モーションの設定
	enemy->SetMotion(CEnemy002::ENEMY002MOTION_DEATHDIRECTION);

	//ゲームシーンに演出を設定
	CGame* pGame = nullptr;
	pGame = (CGame*)CManager::GetInstance()->GetScene();			//ゲームシーンの取得
	pGame->SetDirection(CDirection::DIRECTIONTYPE_BOSS_DESTROY);	//演出の設定

	//固有の設定
	CEnemy002* pEnemy002 = (CEnemy002*)enemy;									//ダウンキャスト
	pEnemy002->SetMaterialized(true);											//実体化する
	pEnemy002->SetPos(pEnemy002->GetPos() + D3DXVECTOR3(0.0f, 1.0f, 0.0f));		//位置の設定

	//エフェクトの生成
	CEffect_Death_Boss::Create(&pEnemy002->GetCollision()->GetPos());
}

//====================================
//アクション(演出)
//====================================
void CEnemyBehavior_Direction_Destroy::Action(CEnemy* enemy)
{
	//演出の時間が終わったら行動開始
	m_nCount++;

	//カメラの位置を設定
	CManager::GetInstance()->GetCamera()->SetPosR(enemy->GetCollision()->GetPos());
	CManager::GetInstance()->GetCamera()->SetPosV(enemy->GetCollision()->GetPos() + CAMERA_POSV);
	
	//カメラを揺らす時間に爆発を生成
	if (m_nCount == CDirection_Boss_Destroy::START_SHAKE_FRAME)
	{
		CEffect_Explosion::Create(enemy->GetPos());
	}

	//演出の時間を迎えたら敵を破棄
	if (m_nCount > DIRECTION_TIME)
	{
		enemy->Uninit();
	}
}