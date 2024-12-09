//================================
//
//character.cppに必要な宣言[character.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _CHARACTER_H_ //このマクロ定義がされていなかったら
#define _CHARACTER_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"
#include "object.h"
#include "modelparts.h"
#include "shadow.h"

//キャラクタークラス
class CCharacter : public CObject
{
public:

	//定数
	static const float ROTATE_SPEED;			//回転の速度
	static const int DAMAGE_TIME{5};			//ダメージ状態の時間
	static const int INTERPOLATION_FRAME{3};	//モーションの補間カウント
	static const float GRAVITY;					//重力の強さ
	static constexpr float SIZE_RADIUS{30.0f};	//サイズの半径

	//キャラクターの種類
	typedef enum
	{
		CHARACTER_TYPE_NONE = 0,//無し
		CHARACTER_TYPE_PLAYER,	//プレイヤー
		CHARACTER_TYPE_ENEMY,	//敵
		CHARACTER_TYPE_MAX,		//列挙の最大
	}CHARACTER_TYPE;

	//キーの構造体
	struct Key
	{
		D3DXVECTOR3 pos;	//位置
		D3DXVECTOR3 rot;	//向き
		Key() : pos(), rot()
		{

		}
	};

	//キーセットの構造体
	struct KeySet
	{
		int nFrame;				//モーションのフレーム数
		std::vector<Key> Key;	//各キーの情報
		KeySet() : nFrame(0), Key()
		{

		}
	};
	
	//モーション情報の構造体
	struct Motion
	{
		bool bLoop;					//モーションをループするか
		int nNumKey;				//キーの種類
		std::vector<KeySet> KeySet;	//各キーの設定
		Motion() : bLoop(false), nNumKey(0), KeySet()
		{

		}
	};

	//パーツ情報の構造体
	struct PartsInfo
	{
		D3DXVECTOR3 pos;	//位置
		D3DXVECTOR3 rot;	//向き
		PartsInfo() : pos(), rot()
		{

		}
	};

	//メンバ関数
	CCharacter(int nPriority = 3);						//コンストラクタ
	virtual ~CCharacter() override;						//デストラクタ
	virtual HRESULT Init() override;					//初期化
	virtual void Uninit() override;						//終了
	virtual void Update() override;						//更新
	void Draw() override;								//描画

	virtual void UpdatePos();							//位置の更新
	void UpdateRot();									//向きの更新
	virtual D3DXVECTOR3 GravityMove(D3DXVECTOR3 move);	//重力の処理
	
	//パラメータ関連の関数
	void SetRot(D3DXVECTOR3 rot) { m_Rot = rot; }								//向きの設定
	D3DXVECTOR3& GetRot() {return m_Rot;}										//向きの取得
	void SetLife(int life) {m_nLife = life;}									//体力の設定
	int& GetLife() { return m_nLife; }											//体力を取得

	//移動量
	void SetMove(D3DXVECTOR3 move) { m_Move = move; }							//設定
	void AddMove(D3DXVECTOR3 move) { m_Move += move; }							//追加
	D3DXVECTOR3& GetMove() { return m_Move; }									//取得

	//目的の向き
	void SetGoalRot(D3DXVECTOR3 goalrot);										//設定
	D3DXVECTOR3& GetGoalRot() { return m_GoalRot; }								//取得

	//前回の位置
	void SetOldPos(D3DXVECTOR3 oldpos) { m_OldPos = oldpos; }					//設定
	D3DXVECTOR3& GetOldPos() { return m_OldPos; }								//取得

	//立ち状態
	void SetOnStand(bool onstand) { m_bOnStand = onstand; }						//設定
	bool GetOnStand() { return m_bOnStand; }									//取得

	//種類
	void SetCharacterType(CHARACTER_TYPE type) { m_CharacterType = type; }		//設定

	//サイズの半径
	void SetSizeRadius(float radius) { m_fRadiusSize = radius; }				//設定
	float GetSizeRadius() { return m_fRadiusSize; }								//取得

	//ダメージ処理
	virtual bool SetDamage(int damage);											//設定

	//重力を受けるか
	void SetEnableGravity(bool enable) { m_bEnableGravity = enable; }			//設定
	bool GetEnableGravity() { return m_bEnableGravity; }						//取得

	//吹き飛び量
	void SetBlowValue(D3DXVECTOR3 value) { m_BlowValue = value; }				//設定
	D3DXVECTOR3 GetBlowValue() { return m_BlowValue; }							//取得

	//すでに張り付いたか
	void SetEnteredStick(bool enter) { m_bEnteredStick = enter; }	//設定
	bool GetEnteredStick() { return m_bEnteredStick; }				//取得

	//モーション
	void SetMotionInfo(const char* motionfilename);								//モーション情報の設定
	void SetMotion(int motion);													//モーションの設定
	int GetMotionState() { return m_MotionState; }								//モーション状態の取得
	void UpdateMotion();														//モーションの更新をする関数
	CModelparts* GetModelParts(int index) { return m_apModel[index]; }			//モデルパーツの取得

	//位置の設定
	void SetPos(D3DXVECTOR3 pos) override
	{
		CObject::SetPos(pos);
		m_OldPos = pos;
	}

private:

	//メンバ関数
	float AddRot(float addrot);		//向きの加算をする関数

	//メンバ変数
	CHARACTER_TYPE m_CharacterType;			//種類
	int m_nLife;							//体力
	D3DXVECTOR3 m_OldPos;					//前回の位置
	D3DXVECTOR3 m_Move;						//移動量
	D3DXVECTOR3 m_Rot;						//向き
	D3DXVECTOR3 m_GoalRot;					//目的の向き
	D3DXMATRIX m_mtxWorld;					//マトリックス
	bool m_bOnStand;						//立っているか
	float m_fRadiusSize;					//サイズの半径
	bool m_bEnableGravity;					//重力を受けるか
	D3DXVECTOR3 m_BlowValue;				//吹き飛びの量
	bool m_bEnteredStick;					//一度でも張り付いたか
	CShadow* m_pShadow;						//影のポインタ

	//モーションの変数
	int m_MotionState;						//現在のモーションの状態
	int m_nMotionCount;						//モーションキーのカウント
	float m_fFrameCount;					//モーションフレームのカウント
	bool m_bChangeMotion;					//モーションを切り替えるかの変数
	float m_fInterpolationCount;			//線形補間のカウント
	float m_bInterpolationEnd;				//線形保管が終わっているか
	std::vector<PartsInfo> m_InterpolationInfo;		//パーツの情報
	std::vector<Motion> m_Motion;			//モーション情報
	std::vector<CModelparts*> m_apModel;	//プレイヤーのパーツ[パーツ数]
	std::vector<PartsInfo> m_PartsInfo;		//パーツの情報
};

#endif