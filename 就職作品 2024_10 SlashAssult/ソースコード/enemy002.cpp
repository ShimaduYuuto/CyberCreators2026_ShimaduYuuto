//======================================
//
//	エネミーの処理[enemy002.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "enemy002.h"
#include "manager.h"
#include "game.h"
#include "state_enemy002.h"

//定数
const std::string CEnemy002::FILEPATH = "data\\enemy012motion.txt";

//============================
//エネミーのコンストラクタ
//============================
CEnemy002::CEnemy002() : 
	m_bMaterialized(true),
	m_fCurrentAlpha(1.0f),
	m_fGoalfAlpha(1.0f),
	m_fAddAlpha(0.0f),
	m_bUpdateAlpha(false)
{
	
}

//============================
//エネミーのデストラクタ
//============================
CEnemy002::~CEnemy002()
{

}

//============================
//エネミーの初期化
//============================
HRESULT CEnemy002::Init()
{
	//初期化
	CEnemy::Init();

	//パラメータの初期化
	SetLife(LIFE);	//体力

	//モーションの読み込み
	SetMotionInfo(FILEPATH.c_str());

	//ポインタに行動を設定
	ChangeState(new CState_Enemy002_Direction(this));

	SetMaterialized(true);
	
	return S_OK;
}

//============================
//エネミーの終了処理
//============================
void CEnemy002::Uninit()
{
	//初期化
	CEnemy::Uninit();
}

//============================
//エネミーの更新
//============================
void CEnemy002::Update()
{
	//死亡フラグが立っているなら抜ける
	if (GetDeath())
	{
		return;
	}

	//α値の更新
	UpdateAlpha();

	//共通処理の更新
	CEnemy::Update();
}

//============================
//エネミーの描画
//============================
void CEnemy002::Draw()
{
	//描画
	CCharacter::Draw();
}

//============================
//位置の更新
//============================
void CEnemy002::UpdatePos()
{
	//体力が残っているなら位置を更新
	if (GetLife() <= 0)
	{
		return;
	}

	CGame_Character::UpdatePos();
}

//============================
//α値の更新
//============================
void CEnemy002::UpdateAlpha()
{
	//目的のα値と同じなら抜ける
	if (m_fCurrentAlpha == m_fGoalfAlpha)
	{
		m_bUpdateAlpha = false;
		m_fAddAlpha = 0.0f;
		return;
	}

	//更新中の判定にして初期設定
	if (!m_bUpdateAlpha)
	{
		m_bUpdateAlpha = true;
		m_fAddAlpha = (m_fGoalfAlpha - m_fCurrentAlpha) / TIME_GOAL_ALPHA;	//加算する色を算出
	}

	m_fCurrentAlpha += m_fAddAlpha;	//加算

	//誤差を修正
	if (m_fCurrentAlpha > m_fGoalfAlpha - 0.001f && m_fCurrentAlpha < m_fGoalfAlpha + 0.001f)
	{
		m_fCurrentAlpha = m_fGoalfAlpha;
	}

	//パーツ数だけ周回
	for (auto itr : GetModelPartsVector())
	{
		itr->SetAlpha(m_fCurrentAlpha);
	}
}

//============================
//ダメージの設定
//============================
bool CEnemy002::SetDamage(int damage, float angle)
{
	//実体化していないなら当たらない
	if (!m_bMaterialized)
	{
		return false;
	}

	//張り付いていないならダメージ状態に
	if (!GetEnteredStick())
	{
		//状態の変更
		ChangeState(new CState_Enemy002_Damage(this));

		//基底の処理
		CEnemy::SetDamage(damage, angle);
	}
	else
	{
		//基底の処理
		CEnemy::SetDamage(damage, angle);
	}

	return true;
}

//============================
//ダメージの設定
//============================
bool CEnemy002::SetBlowDamage(int damage, float rotY)
{
	//実体化していないなら当たらない
	if (!m_bMaterialized)
	{
		return false;
	}

	CEnemy::SetBlowDamage(damage, rotY);

	return true;
}

//============================
//ダメージの設定
//============================
bool CEnemy002::SetBlowDamage(int damage, float rotY, float value)
{
	//実体化していないなら当たらない
	if (!m_bMaterialized)
	{
		return false;
	}

	CEnemy::SetBlowDamage(damage, rotY, value);

	return true;
}

//============================
//実体化の設定
//============================
void CEnemy002::SetMaterialized(bool materialized)
{
	//同じなら抜ける
	if (m_bMaterialized == materialized)
	{
		return;
	}

	//実体化するならパーツを透明にする
	if (materialized)
	{
		m_fGoalfAlpha = 1.0f;
		GetShadow()->SetDrawJudge(true);
	}
	else
	{
		m_fGoalfAlpha = VALUE_INVISIBLE_ALPHA;
		GetShadow()->SetDrawJudge(false);
	}

	//設定
	m_bMaterialized = materialized;
}

//============================
//状態のリセット
//============================
void CEnemy002::StateReset()
{
	//通常の状態に戻す
	ChangeState(new CState_Enemy002_Normal(this));
	SetEnableGravity(true);
	SetMaterialized(false);
}

//============================
//貼り付け状態に変更
//============================
void CEnemy002::ChangeStickState()
{
	ChangeState(new CState_Enemy002_Stick(this));
}

//============================
//スタン状態に変更
//============================
void CEnemy002::ChangeStanState()
{
	ChangeState(new CState_Enemy002_Stan(this));
	SetMaterialized(true);
}

//============================
//死亡時の処理
//============================
void CEnemy002::SetCharacterDeath()
{
	//BGMストップ
	CManager::GetInstance()->GetSound()->Stop(CSound::SOUND_LABEL_BATTLE);

	ChangeState(new CState_Enemy002_Direction_Destroy(this));
}