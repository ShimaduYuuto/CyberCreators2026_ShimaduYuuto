//================================
//
//enemy002.cppに必要な宣言[enemy002.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _ENEMY002_H_ //このマクロ定義がされていなかったら
#define _ENEMY002_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "enemy.h"

//エネミークラス
class CEnemy002 : public CEnemy
{
public:

	//定数
	static const std::string FILEPATH;						//読み込むファイル
	static constexpr float VALUE_INVISIBLE_ALPHA{ 0.3f };	//透明状態のα値
	static constexpr int LIFE{ 70 };						//体力
	static constexpr int TIME_GOAL_ALPHA{ 10 };				//目的のα値になるまでの時間
	
	//敵のモーション
	typedef enum
	{
		ENEMY002MOTION_NORMAL = 0,		//ニュートラル
		ENEMY002MOTION_WALK,			//移動
		ENEMY002MOTION_TAKEOUT,			//取り出し
		ENEMY002MOTION_THROW,			//投げる
		ENEMY002MOTION_CHARGESHOT,		//チャージショット
		ENEMY002MOTION_STAN,			//スタン
		ENEMY002MOTION_DIRECTION,		//演出用
		ENEMY002MOTION_DEATHDIRECTION,	//死亡演出用
		ENEMY002MOTION_STICK,			//貼り付け
		ENEMY002MOTION_MAX				//最大
	}ENEMY002MOTION;

	//メンバ関数
	CEnemy002();						//コンストラクタ
	~CEnemy002() override;				//デストラクタ
	HRESULT Init() override;			//初期化
	void Uninit() override;				//終了
	void Update() override;				//更新
	void Draw() override;				//描画

	//位置の更新
	void UpdatePos() override;

	//ダメージの設定
	bool SetDamage(int damage, float angle) override;								//ダメージの設定
	//bool SetDamage(int damage, float rotY) override;					//ダメージの設定
	bool SetBlowDamage(int damage, float rotY) override;				//吹き飛ばしてダメージを与える
	bool SetBlowDamage(int damage, float rotY, float value) override;	//吹き飛ばしてダメージを与える

	//状態のリセット
	void StateReset() override;

	//貼り付け状態に変更
	void ChangeStickState() override;

	//スタン状態に変更
	void ChangeStanState() override;

	//実体化しているか
	void SetMaterialized(bool materialized);				//設定
	bool GetMaterialized() { return m_bMaterialized; }		//取得

	//α値
	void SetAlpha(float alpha) { m_fGoalfAlpha = alpha; }	//設定
	float GetAlpha() { return m_fCurrentAlpha; }			//取得

	//死亡時の処理
	void SetCharacterDeath() override;

private:

	void UpdateAlpha();		//α値の更新

	bool m_bMaterialized;	//実体化しているか
	float m_fGoalfAlpha;	//目的のアルファ値
	float m_fCurrentAlpha;	//現在の色
	float m_fAddAlpha;		//加算するα値
	bool m_bUpdateAlpha;	//α値を更新しているか
};

#endif