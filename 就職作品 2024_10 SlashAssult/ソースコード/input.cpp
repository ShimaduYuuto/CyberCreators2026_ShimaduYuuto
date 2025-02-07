//======================================
//
//	inputの処理[input.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "input.h"

//*****************************************************************
//CInputクラスの処理
//*****************************************************************

//静的メンバ初期化
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//============================
//インプットのコンストラクタ
//============================
CInput::CInput()
{

}

//============================
//インプットのデストラクタ
//============================
CInput::~CInput()
{

}

//============================
//初期設定(DirectInputの生成)
//============================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//nullポインタかの確認
	if (m_pInput == nullptr)
	{
		//DirectInputオブジェクトの生成
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//============================
//破棄処理(DirectInputの破棄)
//============================
void CInput::Uninit()
{
	//DirectInputオブジェクトの破棄
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}

	//入力デバイスの破棄
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire(); //キーボードへのアクセス権を放棄
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}

//============================
//更新処理
//============================
void CInput::Update()
{

}

//*****************************************************************
//CInputKeyboardクラスの処理
//*****************************************************************

//============================
//キーボードのコンストラクタ
//============================
CInputKeyboard::CInputKeyboard()
{
	//キーの数だけ周回
	for (int i = 0; i < MAX_KEY; i++)
	{
		//キーの状態を初期化
		m_aKeyState[i] = {};
		m_aKeyStateTrigger[i] = {};
		m_aKeyStateRerease[i] = {};
	}
}

//============================
//キーボードのデストラクタ
//============================
CInputKeyboard::~CInputKeyboard()
{

}

//============================
//初期設定(DirectInputの生成)
//============================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(CInput::Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//入力デバイスの生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得
	m_pDevice->Acquire();
	return S_OK;
}

//============================
//破棄処理
//============================
void CInputKeyboard::Uninit()
{
	//DirectInputの破棄
	CInput::Uninit();
}

//============================
//更新処理
//============================
void CInputKeyboard::Update()
{
	BYTE aKeyState[MAX_KEY]; //キーボードの入力情報
	int nCntKey;

	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey]; //キーボードのトリガー情報を保存
			m_aKeyStateRerease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & ~aKeyState[nCntKey]; //キーボードのリリース情報を保存
			m_aKeyState[nCntKey] = aKeyState[nCntKey]; //キーボードのプレス情報を保存
		}
	}
	else
	{
		m_pDevice->Acquire(); //キーボードへのアクセス権
	}
}

//========================================
//キーボードのプレス情報を取得
//========================================
bool CInputKeyboard::GetPress(int nKey)
{
	return((m_aKeyState[nKey] & 0x80) != 0) ? true : false;
}

//========================================
//キーボードのトリガー情報を取得
//========================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return((m_aKeyStateTrigger[nKey] & 0x80) != 0) ? true : false;
}

//========================================
//キーボードのリリース情報を取得
//========================================
bool CInputKeyboard::GetRerease(int nKey)
{
	return((m_aKeyStateRerease[nKey] & 0x80) != 0) ? true : false;
}

//========================================
//キーボードのトリガー情報を取得
//========================================
bool CInputKeyboard::GetAnyTrigger()
{
	for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
	{
		if (GetTrigger(nCntKey))
		{
			return true;
		}
	}

	return false;
}

//*****************************************************************
//CInputJoypadクラスの処理
//*****************************************************************

//============================
//ジョイパッドのコンストラクタ
//============================
CInputJoypad::CInputJoypad()
{
	
}

//============================
//ジョイパッドのデストラクタ
//============================
CInputJoypad::~CInputJoypad()
{

}

//============================
//ジョイパッドのデストラクタ
//============================
HRESULT CInputJoypad::Init()
{
	//メモリのクリア
	memset(&m_aKeyState, 0, sizeof(XINPUT_STATE));
	memset(&m_aKeyStateTrigger, 0, sizeof(XINPUT_STATE));

	//XInputのステート設定(有効にする)
	XInputEnable(true);

	// コントローラーの振動制御の０クリア
	ZeroMemory(&m_joykeyMoter, sizeof(XINPUT_VIBRATION));

	// 振動制御用の初期化
	m_Time = 0;
	m_Strength = 0;

	return S_OK;
}

//============================
//ジョイパッドの終了処理
//============================
void CInputJoypad::Uninit()
{
	//XInputのステートを設定
	XInputEnable(false);
}

//============================
//ジョイパッドの更新処理
//============================
void CInputJoypad::Update()
{
	XINPUT_STATE joykeystate; //ジョイパッドの入力情報

	//ジョイパッドの情報を取得
	if (XInputGetState(0, &joykeystate) == ERROR_SUCCESS)
	{
		//スティックの更新
		UpdateStick(&joykeystate);

		joykeystate.Gamepad.wButtons |= GetJoypadStick(joykeystate.Gamepad.sThumbLX, joykeystate.Gamepad.sThumbLY, JOYPAD_DEADZONE);

		WORD Button = joykeystate.Gamepad.wButtons;
		WORD OldButton = m_joykeyState;

		m_joykeyStateTrigger = Button & ~OldButton;    // トリガー処理
		m_joykeyStateRelease = ~Button & OldButton;    // リリース処理

		// 現在の時間を取得する
		m_joykeyCurrentTime.Gamepad.wButtons = static_cast<WORD>(timeGetTime());

		if (joykeystate.Gamepad.wButtons && ((m_joykeyCurrentTime.Gamepad.wButtons - m_joykeyExecLastTime.Gamepad.wButtons) > SPEED_KEY))
		{
			// 最後に真を返した時間を保存
			m_joykeyExecLastTime.Gamepad.wButtons = m_joykeyCurrentTime.Gamepad.wButtons;

			// キーボードのリピート情報を保存
			m_joykeyStateRepeat = joykeystate.Gamepad.wButtons;
		}
		else
		{
			// キーボードのリピート情報を保存
			m_joykeyStateRepeat = 0;
		}

		m_joykeyState = joykeystate.Gamepad.wButtons;  // プレス処理
	}
}

//============================
//ジョイパッドのプレス情報を取得
//============================
bool CInputJoypad::GetPress(JOYKEY key)
{
	return m_joykeyState & (0x01 << key);
}

//============================
//ジョイパッドのトリガー情報を取得
//============================
bool CInputJoypad::GetTrigger(JOYKEY key)
{
	return m_joykeyStateTrigger & (0x01 << key);
}

//============================
//ジョイパッドのリリース情報を取得
//============================
bool CInputJoypad::GetRerease(JOYKEY key)
{
	return m_joykeyStateRelease & (0x01 << key);
}

//========================================
//ジョイパッドのトリガー情報を取得
//========================================
bool CInputJoypad::GetAnyTrigger()
{
	for (int nCntKey = 0; nCntKey < JOYKEY_MAX; nCntKey++)
	{
		if (GetTrigger(static_cast<JOYKEY>(nCntKey)))
		{
			return true;
		}
	}

	return false;
}

//===========================================================================================================================================================================================
//スティックの更新処理
//===========================================================================================================================================================================================
void CInputJoypad::UpdateStick(XINPUT_STATE* xinput)
{
	for (int nCntStick = 0; nCntStick < STICKTYPE_MAX; nCntStick++)
	{
		float fX, fY; //スティックのX軸、Y軸
	
		switch (nCntStick)
		{
		case STICKTYPE_LEFT:
			fX = (xinput->Gamepad.sThumbLX);
			fY = (xinput->Gamepad.sThumbLY);
			break;
		case STICKTYPE_RIGHT:
			fX = (xinput->Gamepad.sThumbRX);
			fY = (xinput->Gamepad.sThumbRY);
			break;
		}
	
		//角度を取得
		m_stick.afAngle[nCntStick] = FindAngle(D3DXVECTOR3(fX, fY, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f)) * -1;
	
		//スティックの倒し具合を取得
		m_stick.afTplDiameter[nCntStick] = fabsf(fX);
	
		if (m_stick.afTplDiameter[nCntStick] < fabsf(fY))
		{
			m_stick.afTplDiameter[nCntStick] = fabsf(fY);
		}
	
		m_stick.afTplDiameter[nCntStick] /= 32768.0f; //倒している状態の初期値
	
		//方向入力フラグを初期化
		for (int nCntAngle = 0; nCntAngle < STICKANGLE_MAX; nCntAngle++)
		{
			m_bAngle[nCntStick][nCntAngle] = false;
		}
	
		if (m_stick.afTplDiameter[nCntStick] > 0.1f)
		{
			//角度が四分割で上に位置する時、上フラグを真にする
			if ((m_stick.afAngle[nCntStick] < D3DX_PI * -0.75) || (m_stick.afAngle[nCntStick] > D3DX_PI * 0.75))
			{
				m_bAngle[nCntStick][STICKANGLE_UP] = true;
			}
	
			//角度が四分割で下に位置する時、下フラグを真にする
			else if ((m_stick.afAngle[nCntStick] > D3DX_PI * -0.25) && (m_stick.afAngle[nCntStick] < D3DX_PI * 0.25))
			{
				m_bAngle[nCntStick][STICKANGLE_DOWN] = true;
			}
	
			//角度が四分割で左に位置する時、左フラグを真にする
			else if ((m_stick.afAngle[nCntStick] > D3DX_PI * -0.75) && (m_stick.afAngle[nCntStick] < D3DX_PI * -0.25))
			{
				m_bAngle[nCntStick][STICKANGLE_LEFT] = true;
			}
	
			//角度が四分割で右に位置する時、右フラグを真にする
			else if ((m_stick.afAngle[nCntStick] > D3DX_PI * 0.25) && (m_stick.afAngle[nCntStick] < D3DX_PI * 0.75))
			{
				m_bAngle[nCntStick][STICKANGLE_RIGHT] = true;
			}
		}
	
		//角度に応じた入力処理
		for (int nCntAngle = 0; nCntAngle < STICKANGLE_MAX; nCntAngle++)
		{
			//スティックのトリガー情報を保存
			m_stick.abAngleTrigger[nCntStick][nCntAngle] = !m_stick.abAnglePress[nCntStick][nCntAngle] && m_bAngle[nCntStick][nCntAngle];
	
			//スティックのリリース情報を保存
			m_stick.abAngleRelease[nCntStick][nCntAngle] = m_stick.abAnglePress[nCntStick][nCntAngle] && !m_bAngle[nCntStick][nCntAngle];
	
			//現在の時間を取得
			m_aStickCurrentTime[nCntStick][nCntAngle] = timeGetTime();
	
			if (m_bAngle[nCntStick][nCntAngle] && ((m_aStickCurrentTime[nCntStick][nCntAngle] - m_aStickExecLastTime[nCntStick][nCntAngle]) > SPEED_KEY))
			{
				//最後に真を返した時間を保存
				m_aStickExecLastTime[nCntStick][nCntAngle] = m_aStickCurrentTime[nCntStick][nCntAngle];
	
				//スティックのリピート情報を保存
				m_stick.abAngleRepeat[nCntStick][nCntAngle] = m_bAngle[nCntStick][nCntAngle];
			}
			else
			{
				//スティックのリピート情報を保存
				m_stick.abAngleRepeat[nCntStick][nCntAngle] = 0;
			}
	
			//スティックのプレス情報を保存
			m_stick.abAnglePress[nCntStick][nCntAngle] = m_bAngle[nCntStick][nCntAngle];
		}
	}
}

//===========================================================================================================================================================================================
//2点の角度を求める
//===========================================================================================================================================================================================
float CInputJoypad::FindAngle(D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos)
{
	float fAngle; //角度

	fAngle = atan2f(TargetPos.y - pos.y, TargetPos.x - pos.x);

	fAngle -= (D3DX_PI * 0.5f);
	fAngle *= -1.0f;

	//-3.14～3.14に補正
	if (fAngle > D3DX_PI)
	{
		fAngle = -D3DX_PI + (fAngle - D3DX_PI);
	}

	return fAngle;
}

//===========================================================================================================================================================================================
// スティックの入力を方向パッドフラグに変換
//===========================================================================================================================================================================================
WORD CInputJoypad::GetJoypadStick(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone)
{
	WORD wButtons = 0;

	if (sThumbY >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_UP;
	}
	else if (sThumbY <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;
	}

	if (sThumbX <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;
	}
	else if (sThumbX >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;
	}

	return wButtons;
}

//==========================================================================================
// コントローラーの入力情報の取得
//==========================================================================================
XINPUT_STATE* CInputJoypad::GetXInputState(void)
{
	return &m_XInput;
}

//==========================================================================================
// スティックの入力情報を取得
//==========================================================================================
CInputJoypad::STICKINPUT CInputJoypad::GetStick(void)
{
	return m_stick;
}

//*****************************************************************
//CInputmouseクラスの処理
//*****************************************************************

//============================
//マウスのコンストラクタ
//============================
CInputMouse::CInputMouse() : 
	m_aMouseState(),
	m_aMouseStateTrigger(),
	m_aMouseStateRerease(),
	m_Point(),
	m_zdiMouseState()
{

}

//============================
//マウスのデストラクタ
//============================
CInputMouse::~CInputMouse()
{

}

//============================
//マウスの初期化
//============================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT ret = S_FALSE;

	if (m_pInput == NULL)
	{
		return E_FAIL;
	}

	// マウス用にデバイスオブジェクトを作成
	ret = m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL);
	if (FAILED(ret)) {
		// デバイスの作成に失敗
		return E_FAIL;
	}

	// データフォーマットを設定
	ret = m_pDevice->SetDataFormat(&c_dfDIMouse);	// マウス用のデータ・フォーマットを設定
	if (FAILED(ret)) {
		// データフォーマットに失敗
		return E_FAIL;
	}

	// モードを設定（フォアグラウンド＆非排他モード）
	ret = m_pDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(ret)) {
		// モードの設定に失敗
		return E_FAIL;
	}

	// デバイスの設定
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;	// 相対値モードで設定（絶対値はDIPROPAXISMODE_ABS）

	ret = m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph);
	if (FAILED(ret))
	{
		// デバイスの設定に失敗
		return E_FAIL;
	}

	// 入力制御開始
	m_pDevice->Acquire();

	return S_OK;
}

//============================
//マウスの終了処理
//============================
void CInputMouse::Uninit()
{
	//入力デバイスの破棄
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire(); //マウスへのアクセス権を放棄
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//============================
//更新処理
//============================
void CInputMouse::Update()
{
	DIMOUSESTATE aMouseState; //マウスの入力情報
	int nCntKey;

	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aMouseState), &aMouseState)))
	{
		for (nCntKey = 0; nCntKey < MOUSEBUTTON_MAX; nCntKey++)
		{
			m_aMouseStateTrigger.rgbButtons[nCntKey] = (m_aMouseState.rgbButtons[nCntKey] ^ aMouseState.rgbButtons[nCntKey]) & aMouseState.rgbButtons[nCntKey];	//マウスのトリガー情報を保存
			m_aMouseStateRerease.rgbButtons[nCntKey] = (m_aMouseState.rgbButtons[nCntKey] ^ aMouseState.rgbButtons[nCntKey]) & ~aMouseState.rgbButtons[nCntKey];//マウスのリリース情報を保存
			m_aMouseState.rgbButtons[nCntKey] = aMouseState.rgbButtons[nCntKey];																				//マウスのプレス情報を保存
		}

		//マウス情報の更新
		m_aMouseState = aMouseState;
	}
	else
	{
		m_pDevice->Acquire(); //マウスへのアクセス権
	}
}

//========================================
//マウスのプレス情報を取得
//========================================
bool CInputMouse::GetPress(MOUSEBUTTON nKey)
{
	return((m_aMouseState.rgbButtons[nKey] & 0x80) != 0) ? true : false;
}

//========================================
//マウスのトリガー情報を取得
//========================================
bool CInputMouse::GetTrigger(MOUSEBUTTON nKey)
{
	return((m_aMouseStateTrigger.rgbButtons[nKey] & 0x80) != 0) ? true : false;
}

//========================================
//マウスのリリース情報を取得
//========================================
bool CInputMouse::GetRerease(MOUSEBUTTON nKey)
{
	return((m_aMouseStateRerease.rgbButtons[nKey] & 0x80) != 0) ? true : false;
}

//========================================
//マウスのトリガー情報を取得
//========================================
bool CInputMouse::GetAnyTrigger()
{
	for (int nCntKey = 0; nCntKey < MOUSEBUTTON_MAX; nCntKey++)
	{
		if (GetTrigger(static_cast<MOUSEBUTTON>(nCntKey)))
		{
			return true;
		}
	}

	return false;
}

//========================================
//マウスの移動量を取得
//========================================
D3DXVECTOR3 CInputMouse::GetMove()
{
	//移動量の取得
	D3DXVECTOR3 Move = D3DXVECTOR3((float)m_aMouseState.lX, (float)m_aMouseState.lY, (float)m_aMouseState.lZ);
	return Move;
}

//========================================
//マウスの位置を取得
//========================================
D3DXVECTOR2 CInputMouse::GetPos()
{
	//位置の取得
	GetCursorPos(&m_Point);

	// スクリーン座標をクライアント座標に変換する
	ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &m_Point);

	//変数に代入
	D3DXVECTOR2 Pos = D3DXVECTOR2((float)m_Point.x, (float)m_Point.y);
	return Pos;
}