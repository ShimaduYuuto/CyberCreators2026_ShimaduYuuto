//======================================
//
//	���C������[main.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "main.h"
#include "manager.h"

//�}�N����`
#define WINDOW_NAME "SlashAssault" //�E�B���h�E�̖��O�i�L���v�V�����ɕ\���j
#define FPS (1000) //FPS�̊
#define FPS_NUMBER (60) //FPS�̊

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND nWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	//�E�B���h�E�v���V�[�W��
//�ً}
void ToggleFullscreen(HWND hWnd);// �E�B���h�E���t���X�N���[���ɂ���

bool g_isFullscreen = false;// �E�B���h�E��؂�ւ��邽�߂̃t���O
RECT g_windowRect;// �E�B���h�E��؂�ւ��邽�߂̕ϐ�

//===================================
//���C���֐�
//===================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpcmpLine, _In_ int nCmdShow)
{
	//�J�[�\���̔�\��
	ShowCursor(FALSE);

	CManager* pManager = nullptr;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX), //WNDCLASSEX�̃������̃T�C�Y
		CS_CLASSDC,         //�E�B���h�E�̃X�^�C��
		WindowProc,         //�E�B���h�E�v���V�[�W��
		0,                  //0�ɂ���
		0,                  //0�ɂ���
		hInstance,          //�C���X�^���X�n���h��
		LoadIcon(NULL, IDI_APPLICATION), //�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL, IDC_ARROW),     //�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),      //�N���C�A���g�̈�̔w�i�̐F
		NULL,                            //���j���[�o�[
		CLASS_NAME,                      //�E�B���h�E�N���X�̖��O
		LoadIcon(NULL, IDI_APPLICATION)  //�t�@�C���̃A�C�R��
	};

	HWND hWnd;				//�E�B���h�E�n���h��(���ʎq)
	MSG msg;				//���b�Z�[�W���i�[����ϐ�
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }; //��ʃT�C�Y�\����

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);

	//����\��ݒ�
	timeBeginPeriod(1);

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//�����Ə�����
	pManager = CManager::GetInstance();		//�����_���[����
	pManager->Init(hInstance, hWnd, TRUE);	//������

	//�����_���Ői�s���������߂�
	srand((unsigned int)time(NULL));

	DWORD dwCurrentTime = 0;	//���ݎ���
	DWORD dwExecLastTime = timeGetTime();	//�Ō�ɏ�����������
	DWORD dwFrameCount = 0;
	DWORD dwFPSLastTime = timeGetTime();

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windows�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT ���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}
			else
			{//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime(); //���ݎ������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
				//FPS���ϑ�
				int nFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				pManager->SetFPS(nFPS);
				dwFPSLastTime = dwCurrentTime;	//FPS���ϑ�����������ۑ�
				dwFrameCount = 0;				//�t���[���J�E���g���N���A
			}
			if ((dwCurrentTime - dwExecLastTime) >= (FPS / FPS_NUMBER))
			{//60����1�b�o��
				dwExecLastTime = dwCurrentTime;//�����J�n�̎�����ۑ�
				//�X�V����
				pManager->Update();

				//�`�揈��
				pManager->Draw();

				dwFrameCount++;//�t���[���J�E���g�����Z
			}

		}

	}

	//�I������
	pManager->Uninit();
	
	//����\��߂�
	timeEndPeriod(1);

	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;

}

//==========================
//�E�C���h�E�v���V�[�W��
//==========================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;//�Ԃ�l���i�[

	switch (uMsg)
	{
	case WM_DESTROY:
		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:	//�L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE: //[ESC�L�[�������ꂽ
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);
			if (nID == IDYES)
			{
				//�E�B���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�
				DestroyWindow(hWnd);
			}
			break;
		case VK_F11:
			ToggleFullscreen(hWnd);
			break;
		}
		break;

	case WM_CLOSE: //����{�^���������b�Z�[�W
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);
		if (nID == IDYES)
		{
			//�E�B���h�E��j������
			DestroyWindow(hWnd);
		}
		else
		{
			return 0; //0��Ԃ��Ȃ��ƏI�����Ă��܂�
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//************************************************
// �E�B���h�E���t���X�N���[���ɕς��鏈��
//************************************************
void ToggleFullscreen(HWND hWnd)
{
	// ���݂̃E�B���h�E�X�^�C�����擾
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (g_isFullscreen)
	{
		// �E�B���h�E���[�h�ɐ؂�ւ�
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, g_windowRect.left, g_windowRect.top,
			g_windowRect.right - g_windowRect.left, g_windowRect.bottom - g_windowRect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		// �t���X�N���[�����[�h�ɐ؂�ւ�
		GetWindowRect(hWnd, &g_windowRect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}

	g_isFullscreen = !g_isFullscreen;
}