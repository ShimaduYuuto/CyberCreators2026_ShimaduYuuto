//================================
//
//input.cppに必要な宣言[input.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _INPUT_H_ //このマクロ定義がされていなかったら
#define _INPUT_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"

//入力基底クラス
class CInput
{
public:

	//定数
	static const int MAX_KEY = 256;	//キーの最大

	//メンバ関数
	CInput();
	~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//初期化処理
	virtual void Uninit();		//終了処理
	virtual void Update() = 0;	//入力端末ごとに実装

protected:

	//全入力処理で共有
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

//キーボード入力
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	void Uninit() override;
	void Update() override;

	//キーの入力状態を返す関数
	bool GetPress(int nKey);	//プレス状態取得
	bool GetTrigger(int nKey);	//トリガー状態を取得
	bool GetRerease(int nKey);	//リリース状態を取得
	bool GetRepeate(int nKey);	//リピート状態を取得
	bool GetAnyTrigger();		//トリガー情報を取得

private:
	BYTE m_aKeyState[MAX_KEY];			//キーの状態
	BYTE m_aKeyStateTrigger[MAX_KEY];	//キーの状態(トリガー)
	BYTE m_aKeyStateRerease[MAX_KEY];	//キーの状態(リリース)
};

//ジョイパッド入力
class CInputJoypad : public CInput
{
public:

	//定数
	static const int SPEED_KEY = 14;
	static const int JOYPAD_DEADZONE = 1;

	//キーの種類
	typedef enum
	{
		JOYKEY_UP = 0,
		JOYKEY_DOWN,
		JOYKEY_LEFT,
		JOYKEY_RIGHT,
		JOYKEY_START,
		JOYKEY_BACK,
		JOYKEY_L3,
		JOYKEY_R3,
		JOYKEY_LB,
		JOYKEY_RB,
		JOYKEY_LT,
		JOYKEY_RT,
		JOYKEY_A,
		JOYKEY_B,
		JOYKEY_X,
		JOYKEY_Y,
		JOYKEY_MAX
	}JOYKEY;

	//スティックの番号
	typedef enum
	{
		STICKTYPE_LEFT = 0, // 左スティック
		STICKTYPE_RIGHT,	// 右スティック
		STICKTYPE_MAX
	}STICKTYPE;

	//スティックの方向
	typedef enum
	{
		STICKANGLE_UP = 0, // 上
		STICKANGLE_DOWN,   // 下
		STICKANGLE_LEFT,   // 左
		STICKANGLE_RIGHT,  // 右
		STICKANGLE_MAX,
	}STICKANGLE;

	//スティックの入力情報
	typedef struct
	{
		float afTplDiameter[STICKTYPE_MAX];                      // スティックの倒し具合
		float afAngle[STICKTYPE_MAX];                            // スティックの角度
		bool abAnglePress[STICKTYPE_MAX][STICKANGLE_MAX];        // スティックの方向プレス情報
		bool abAngleTrigger[STICKTYPE_MAX][STICKANGLE_MAX];      // スティックの方向トリガー情報
		bool abAngleRepeat[STICKTYPE_MAX][STICKANGLE_MAX];       // スティックの方向リピート情報
		bool abAngleRelease[STICKTYPE_MAX][STICKANGLE_MAX];      // スティックの方向リリース情報
	}STICKINPUT;

	//基本の処理
	CInputJoypad();
	~CInputJoypad();
	HRESULT Init(void);
	void Uninit() override;
	void Update() override;
	void UpdateStick(XINPUT_STATE* xinput); //スティックの更新処理

	//キーの入力状態を返す関数
	bool GetPress(JOYKEY key);		//プレス状態取得
	bool GetTrigger(JOYKEY key);	//トリガー状態を取得
	bool GetRerease(JOYKEY key);	//リリース状態を取得
	bool GetRepeate(JOYKEY key);	//リピート状態を取得
	bool GetAnyTrigger();			//トリガー情報を取得
	XINPUT_STATE* GetXInputState(); //コントローラーの入力情報の取得
	STICKINPUT GetStick();			//スティックの情報を取得
	WORD GetJoypadStick(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone);

private:

	//メンバ関数
	float FindAngle(D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos); //2点の角度を求める関数

	//メンバ変数
	BYTE m_aKeyState[MAX_KEY];						//キーの状態
	BYTE m_aKeyStateTrigger[MAX_KEY];				//キーの状態(トリガー)
	int m_KeyPressCount;							//キーを押してる時間のカウント
	int m_JoyKeyPressCount;							//キーを押してる時間のカウント
	WORD m_joykeyState;								//ジョイパッドのプレス情報
	WORD m_joykeyStateTrigger;						//ジョイパッドのトリガー情報
	WORD m_joykeyStateRelease;						//ジョイパッドのリリース情報
	WORD m_joykeyStateRepeat;						//ジョイパッドのリピート情報
	int m_Time;										//時間を計る
	WORD m_Strength;								// 振動の強さ (0 ～ 65535)
	D3DXVECTOR3 m_joykeyStickPos;					// スティックの傾き
	bool m_bAngle[STICKTYPE_MAX][STICKANGLE_MAX];	//スティックの入力情報
	DWORD m_aStickCurrentTime[STICKTYPE_MAX][STICKANGLE_MAX]; //スティックの現在の時間
	DWORD m_aStickExecLastTime[STICKTYPE_MAX][STICKANGLE_MAX]; //スティックの現在の時間
	STICKINPUT m_stick;								//スティックの入力情報
	XINPUT_STATE m_XInput;							// 入力情報
	XINPUT_STATE m_joykeyCurrentTime;				// コントローラーの現在の時間
	XINPUT_STATE m_joykeyExecLastTime;				// コントローラーの最後に真を返した時間
	XINPUT_STATE m_joykeyInput;						// コントローラーの入力情報
	XINPUT_VIBRATION m_joykeyMoter;					// コントローラーのモーター
	WORD m_Button;									//ボタンの判定
	WORD m_OldButton;								//古いボタンの判定
};

//マウス入力
class CInputMouse : public CInput
{
public:
	//マウスのボタンの種類列挙型
	typedef enum
	{
		MOUSEBUTTON_LEFT = 0,	//左クリック
		MOUSEBUTTON_RIGHT,		//右クリック
		MOUSEBUTTON_WHEEL,		//ホイール(押し込み)
		MOUSEBUTTON_MAX,		//列挙の最大
	}MOUSEBUTTON;

	//基本の処理
	CInputMouse();
	~CInputMouse();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit() override;
	void Update() override;

	//取得用
	bool GetPress(MOUSEBUTTON nKey);	//プレス
	bool GetTrigger(MOUSEBUTTON nKey);	//トリガー
	bool GetRerease(MOUSEBUTTON nKey);	//リリース
	bool GetAnyTrigger();				//トリガー情報を取得
	D3DXVECTOR3 GetMove();				//移動量
	D3DXVECTOR2 GetPos();				//位置

private:

	DIMOUSESTATE m_zdiMouseState;						//マウス状態
	DIMOUSESTATE m_aMouseState;							//マウスのプレス情報
	DIMOUSESTATE m_aMouseStateTrigger;					//マウスのトリガー情報
	DIMOUSESTATE m_aMouseStateRerease;					//マウスのリリース情報
	POINT m_Point;										//ポイントの保存
};

#endif