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
	static constexpr float ROTATE_SPEED{0.2f};		//回転の速度
	static constexpr int DAMAGE_TIME{5};			//ダメージ状態の時間
	static constexpr int INTERPOLATION_FRAME{6};	//モーションの補間カウント
	static constexpr float GRAVITY{0.6f};			//重力の強さ
	static constexpr float SIZE_RADIUS{30.0f};		//サイズの半径
	static constexpr int MAX_MODEL{ 16 };			//読み込むモデルパーツの最大数
	static constexpr int MAX_STRING{ 256 };			//読み込む文字の最大数

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

	//影
	CShadow*& GetShadow() { return m_pShadow; }	//取得

	//モーション
	void SetMotionInfo(const char* motionfilename);								//モーション情報の設定
	void SetMotion(int motion);													//モーションの設定
	int GetMotionState() { return m_MotionState; }								//モーション状態の取得
	void UpdateMotion();														//モーションの更新をする関数
	CModelparts* GetModelParts(int index) { return m_apModel[index]; }			//モデルパーツの取得
	std::vector<CModelparts*> GetModelPartsVector() { return m_apModel; }		//モデルパーツのベクターを取得

	//位置の設定
	void SetPos(D3DXVECTOR3 pos) override
	{
		CObject::SetPos(pos);
		m_OldPos = pos;
	}

private:

	//メンバ関数
	float AddRot(float addrot);										//向きの加算をする関数
	D3DXVECTOR3 RotCalculation(D3DXVECTOR3 goal, D3DXVECTOR3 current);	//モーションの向きの値を算出

	//メンバ変数
	D3DXVECTOR3 m_OldPos;					//前回の位置
	D3DXVECTOR3 m_Move;						//移動量
	D3DXVECTOR3 m_Rot;						//向き
	D3DXVECTOR3 m_GoalRot;					//目的の向き
	D3DXMATRIX m_mtxWorld;					//マトリックス
	CShadow* m_pShadow;						//影のポインタ

	//モーションの変数
	int m_MotionState;						//現在のモーションの状態
	int m_nMotionCount;						//モーションキーのカウント
	float m_fFrameCount;					//モーションフレームのカウント
	bool m_bChangeMotion;					//モーションを切り替えるかの変数
	float m_fInterpolationCount;			//線形補間のカウント
	bool m_bInterpolationEnd;				//線形保管が終わっているか
	std::vector<PartsInfo> m_InterpolationInfo;		//パーツの情報
	std::vector<Motion> m_Motion;			//モーション情報
	std::vector<CModelparts*> m_apModel;	//プレイヤーのパーツ[パーツ数]
	std::vector<PartsInfo> m_PartsInfo;		//パーツの情報
};

#endif