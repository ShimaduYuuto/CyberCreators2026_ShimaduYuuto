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
CEnemyAction_Standby::CEnemyAction_Standby(CEnemy* enemy) : m_nCoolTime(0)
{
	enemy->SetMotion(CEnemy002::ENEMY002MOTION_NORMAL);
	m_nCoolTime = COOL_TIME;
	enemy->SetCollisionProcess(true);
};

//====================================
//アクション(待機)
//====================================
void CEnemyAction_Standby::Action(CEnemy* enemy)
{
	//クールタイムが終わったら次の行動を行う
	m_nCoolTime--;

	if (m_nCoolTime < 0)
	{
		NextAction(enemy);
	}
}

//====================================
//次の行動を設定
//====================================
void CEnemyAction_Standby::NextAction(CEnemy* enemy)
{
	//残り体力に応じて行動を変化
	if (enemy->GetLife() > LIFE_FIRST_ATTACK)
	{
		//攻撃する
		SetNextAction(new CEnemyAction_ChargeShot(enemy));
	}
	else
	{
		//攻撃する
		SetNextAction(new CEnemyAction_AlterEgoAttack(enemy));
	}
}

//======================================================================
//チャージショット
//======================================================================

//====================================
//コンストラクタ
//====================================
CEnemyAction_ChargeShot::CEnemyAction_ChargeShot(CEnemy* enemy) : m_nChargeCount(0), m_pBullet(nullptr), m_pEffect(nullptr)
{
	//設定
	enemy->SetMotion(CEnemy002::ENEMY002MOTION_CHARGESHOT);	//モーション
};

//====================================
//デストラクタ
//====================================
CEnemyAction_ChargeShot::~CEnemyAction_ChargeShot()
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
void CEnemyAction_ChargeShot::Action(CEnemy* enemy)
{
	//カウントが回り切っていないなら更新
	if (m_nChargeCount <= CHARGE_TIME)
	{
		CGame* pGame = nullptr;
		pGame = (CGame*)CManager::GetInstance()->GetScene();		//ゲームシーンの取得
		D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();	//プレイヤーの位置を取得
		D3DXVECTOR3 Pos = enemy->GetPos();							//自分の位置を取得

		//プレイヤーとの角度を算出
		float fAngle = atan2f(PlayerPos.x - Pos.x, PlayerPos.z - Pos.z);//対角線の角度を算出

		//角度を設定
		enemy->SetGoalRot({ enemy->GetRot().x, fAngle + D3DX_PI, enemy->GetRot().z });

		//カウントの更新
		m_nChargeCount++;

		//弾の生成時間になったら生成
		if (m_nChargeCount > CREATE_BULLET_TIME)
		{
			//弾の生成
			if (m_pBullet == nullptr)
			{
				m_pBullet = CEnemyBullet::Create(enemy->GetCollision()->GetPos(), { 0.0f, 0.0f, 0.0f });
				m_pEffect = CEffect_ChargeShot::Create(enemy->GetCollision()->GetPos());

				//SEの設定
				CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_CHARGE001);
			}
		}

		//弾が生成済みなら
		if (m_pBullet != nullptr)
		{
			//スケールを大きくする
			m_pBullet->AddSizeRate(ADD_SCALE_VALUE);
			m_pBullet->SetPos({ enemy->GetCollision()->GetPos().x + sinf(fAngle) * BULLET_LENGTH * m_pBullet->GetSizeRate() , enemy->GetCollision()->GetPos().y, enemy->GetCollision()->GetPos().z + cosf(fAngle) * BULLET_LENGTH * m_pBullet->GetSizeRate() });

			//チャージ時間を終えたら発射
			if (m_nChargeCount > CHARGE_TIME)
			{
				//向いている方向に撃つ
				m_pBullet->SetMove({ sinf(fAngle) * BULLET_SPEED, 0.0f, cosf(fAngle) * BULLET_SPEED });
				m_pBullet->SetShooting(true);

				//SEの設定
				CManager::GetInstance()->GetSound()->Stop(CSound::SOUND_LABEL_CHARGE001);
				CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SHOT);

				//エフェクトの破棄
				if (m_pEffect != nullptr)
				{
					m_pEffect->Uninit();
					m_pEffect = nullptr;
				}	
			}
		}
	}

	//終了の時間になったら次のアクション
	if (m_nChargeCount > END_TIME)
	{
		NextAction(enemy);
	}

	//当たっていたら消す
	if (m_pBullet != nullptr)
	{
		if (m_pBullet->GetDeath())
		{
			m_pBullet = nullptr;
			NextAction(enemy);
		}
	}
}

//====================================
//次の行動を設定
//====================================
void CEnemyAction_ChargeShot::NextAction(CEnemy* enemy)
{
	SetNextAction(new CEnemyAction_Standby(enemy));
}

//======================================================================
//登場演出
//======================================================================

//====================================
//コンストラクタ
//====================================
CEnemyAction_Direction::CEnemyAction_Direction(CEnemy* enemy) :
	m_nCount(0)
{
	enemy->SetMotion(CEnemy002::ENEMY002MOTION_DIRECTION);

	//ゲームシーンに演出を設定
	CGame* pGame = nullptr;
	pGame = (CGame*)CManager::GetInstance()->GetScene();	//ゲームシーンの取得
	pGame->SetDirection(CDirection::DIRECTIONTYPE_BOSS);	//演出の設定

	CEnemy002* pEnemy002 = (CEnemy002*)enemy;
	pEnemy002->SetMaterialized(true);
}

//====================================
//アクション(演出)
//====================================
void CEnemyAction_Direction::Action(CEnemy* enemy)
{
	//演出の時間が終わったら行動開始
	m_nCount++;

	if (m_nCount > DIRECTION_TIME)
	{
		NextAction(enemy);
	}
}

//====================================
//次の行動を設定
//====================================
void CEnemyAction_Direction::NextAction(CEnemy* enemy)
{
	SetNextAction(new CEnemyAction_Standby(enemy));
}

//======================================================================
//分身攻撃
//======================================================================

//====================================
//コンストラクタ
//====================================
CEnemyAction_AlterEgoAttack::CEnemyAction_AlterEgoAttack(CEnemy* enemy) :
	m_nCount(0),
	m_pShotAction(nullptr),
	m_bCreateAlterEgo(false),
	m_pAlterEgo(),
	m_pBullet(nullptr),
	m_pEffect(nullptr),
	m_nChargeCount(0)
{
	//設定
	enemy->SetMotion(CEnemy002::ENEMY002MOTION_NORMAL);	//モーション

	//分身のポインタを初期化
	for (int i = 0; i < NUM_ALTEREGO; i++)
	{
		m_pAlterEgo[i] = nullptr;
	}
}

//====================================
//デストラクタ
//====================================
CEnemyAction_AlterEgoAttack::~CEnemyAction_AlterEgoAttack()
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
//アクション(分身)
//====================================
void CEnemyAction_AlterEgoAttack::Action(CEnemy* enemy)
{
	//ローカル変数
	int nNumAlterEgo = 0;		//現在の分身の数

	m_nCount++;	//カウントアップ

	//徐々に消える
	if (m_nCount <= TIME_INTERPOLATION_ALPHA)
	{
		//パーツ数だけ周回
		for (auto itr : enemy->GetModelPartsVector())
		{
			//アルファ値を減算して設定
			float fAlpha = itr->GetAlpha();
			fAlpha -= CEnemy002::VALUE_INVISIBLE_ALPHA / TIME_INTERPOLATION_ALPHA;
			
			//補正
			if (fAlpha < 0.0f)
			{
				fAlpha = 0.0f;
			}

			itr->SetAlpha(fAlpha);
		}
	}

	//徐々に姿を表す
	else if (m_nCount > TIME_START_APPEAR && m_nCount <= TIME_START_APPEAR + TIME_INTERPOLATION_ALPHA)
	{
		//最初の一回目に分身を生成
		if (!m_bCreateAlterEgo)
		{
			//位置を設定
			m_bCreateAlterEgo = true;
			std::random_device Random;
			float fRandom = (Random() % 628) * 0.01f;
			enemy->SetPos(D3DXVECTOR3(sinf(fRandom) * CEnemyAction_ChargeShot::BULLET_LENGTH, 0.0f, cosf(fRandom) * CEnemyAction_ChargeShot::BULLET_LENGTH) + enemy->GetStartPos());
			enemy->SetMotion(CEnemy002::ENEMY002MOTION_CHARGESHOT);

			//分身を生成
			for (int i = 0; i < NUM_ALTEREGO; i++)
			{
				m_pAlterEgo[i] = CEnemy002_AlterEgo::Create(D3DXVECTOR3(sinf(((D3DX_PI * 2.0f) / (NUM_ALTEREGO + 1)) * (i + 1) + fRandom) * 200.0f, 0.0f, cosf(((D3DX_PI * 2.0f) / (NUM_ALTEREGO + 1)) * (i + 1) + fRandom) * 200.0f) + enemy->GetStartPos(), this);
			}
		}

		//パーツ数だけ周回
		for (auto itr : enemy->GetModelPartsVector())
		{
			//アルファ値を加算して設定
			float fAlpha = itr->GetAlpha();
			fAlpha += CEnemy002::VALUE_INVISIBLE_ALPHA / TIME_INTERPOLATION_ALPHA;

			//補正
			if (fAlpha > CEnemy002::VALUE_INVISIBLE_ALPHA)
			{
				fAlpha = CEnemy002::VALUE_INVISIBLE_ALPHA;
			}

			itr->SetAlpha(fAlpha);
		}
	}

	//分身が生成されていないなら抜ける
	if (!m_bCreateAlterEgo)
	{
		return;
	}

	//カウントが回り切っていないなら更新
	if (m_nChargeCount <= CHARGE_TIME)
	{
		CGame* pGame = nullptr;
		pGame = (CGame*)CManager::GetInstance()->GetScene();		//ゲームシーンの取得
		D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();	//プレイヤーの位置を取得
		D3DXVECTOR3 Pos = enemy->GetPos();							//自分の位置を取得

		//プレイヤーとの角度を算出
		float fAngle = atan2f(PlayerPos.x - Pos.x, PlayerPos.z - Pos.z);//対角線の角度を算出

		//角度を設定
		enemy->SetGoalRot({ enemy->GetRot().x, fAngle + D3DX_PI, enemy->GetRot().z });

		//カウントの更新
		m_nChargeCount++;

		//弾の生成時間になったら生成
		if (m_nChargeCount > CREATE_BULLET_TIME)
		{
			//弾の生成
			if (m_pBullet == nullptr)
			{
				m_pBullet = CEnemyBullet::Create(enemy->GetCollision()->GetPos(), { 0.0f, 0.0f, 0.0f });
				m_pEffect = CEffect_ChargeShot::Create(enemy->GetCollision()->GetPos());
			}
		}

		//弾が生成済みなら
		if (m_pBullet != nullptr)
		{
			//スケールを大きくする
			m_pBullet->AddSizeRate(ADD_SCALE_VALUE);
			m_pBullet->SetPos({ enemy->GetCollision()->GetPos().x + sinf(fAngle) * CEnemyAction_ChargeShot::BULLET_LENGTH * m_pBullet->GetSizeRate() , enemy->GetCollision()->GetPos().y, enemy->GetCollision()->GetPos().z + cosf(fAngle) * CEnemyAction_ChargeShot::BULLET_LENGTH * m_pBullet->GetSizeRate() });

			//チャージ時間を終えたら発射
			if (m_nChargeCount > CHARGE_TIME)
			{
				//向いている方向に撃つ
				m_pBullet->SetMove({ sinf(fAngle) * CEnemyAction_ChargeShot::BULLET_SPEED, 0.0f, cosf(fAngle) * CEnemyAction_ChargeShot::BULLET_SPEED });
				m_pBullet->SetShooting(true);

				//エフェクトの破棄
				if (m_pEffect != nullptr)
				{
					m_pEffect->Uninit();
					m_pEffect = nullptr;
				}
			}
		}
	}

	//当たっていたら消す
	if (m_pBullet != nullptr)
	{
		if (m_pBullet->GetDeath())
		{
			m_pBullet = nullptr;
		}
	}

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

		//死亡フラグが立っていたらnullptrにする
		if (m_pAlterEgo[i]->GetDeath())
		{
			m_pAlterEgo[i] = nullptr;
		}
	}

	//分身がいないなら移行
	if (nNumAlterEgo == 0 && m_pBullet == nullptr)
	{
		NextAction(enemy);
	}
}

//====================================
//分身のポインタの削除
//====================================
void CEnemyAction_AlterEgoAttack::Erase(CEnemy002_AlterEgo* enemy)
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
void CEnemyAction_AlterEgoAttack::NextAction(CEnemy* enemy)
{
	SetNextAction(new CEnemyAction_Standby(enemy));
}

//======================================================================
//撃破演出
//======================================================================

//定数
const D3DXVECTOR3 CEnemyAction_Direction_Destroy::CAMERA_POSV = { 0.0f, 0.0f, -200.0f };

//====================================
//コンストラクタ
//====================================
CEnemyAction_Direction_Destroy::CEnemyAction_Direction_Destroy(CEnemy* enemy) :
	m_nCount(0)
{
	enemy->SetMotion(CEnemy002::ENEMY002MOTION_DEATHDIRECTION);

	//ゲームシーンに演出を設定
	CGame* pGame = nullptr;
	pGame = (CGame*)CManager::GetInstance()->GetScene();			//ゲームシーンの取得
	pGame->SetDirection(CDirection::DIRECTIONTYPE_BOSS_DESTROY);	//演出の設定

	//固有の設定
	CEnemy002* pEnemy002 = (CEnemy002*)enemy;
	pEnemy002->SetMaterialized(true);
	pEnemy002->SetPos(pEnemy002->GetPos() + D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	//エフェクトの生成
	CEffect_Death_Boss::Create(&pEnemy002->GetCollision()->GetPos());
}

//====================================
//アクション(演出)
//====================================
void CEnemyAction_Direction_Destroy::Action(CEnemy* enemy)
{
	//演出の時間が終わったら行動開始
	m_nCount++;

	//カメラの位置を設定
	CManager::GetInstance()->GetCamera()->SetPosR(enemy->GetCollision()->GetPos());
	CManager::GetInstance()->GetCamera()->SetPosV(enemy->GetCollision()->GetPos() + CAMERA_POSV);
	
	if (m_nCount == CDirection_Boss_Destroy::START_SHAKE_FRAME)
	{
		CEffect_Explosion::Create(enemy->GetPos());
	}

	if (m_nCount > DIRECTION_TIME)
	{
		enemy->Uninit();
	}
}