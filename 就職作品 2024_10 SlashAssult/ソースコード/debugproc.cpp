//======================================
//
//	�f�o�b�O�v���b�N�̏���[Debugproc.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "Debugproc.h"
#include "manager.h"
#include <tchar.h>

//�萔�̏�����
const std::string CDebugProc::m_apOnOff[DEBUGTYPE_MAX] = 
{//�f�o�b�Oonoff�\�����b�Z�[�W
	"OFF",
	"ON",
};		

const std::string CDebugProc::m_apMode[CScene::MODE_MAX] = 
{//���݂̃V�[���̕\��
	"�^�C�g��",
	"�Q�[��",
	"���U���g",
};	

//============================
//�f�o�b�O�v���b�N�̃R���X�g���N�^
//============================
CDebugProc::CDebugProc()
{
	
}

//============================
//�f�o�b�O�v���b�N�̃f�X�g���N�^
//============================
CDebugProc::~CDebugProc()
{

}

//============================
//�f�o�b�O�v���b�N�̏�����
//============================
HRESULT CDebugProc::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^���擾

	//�f�o�b�O�\���p�t�H���g�̐���
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

	//�f�o�b�O�\�����̃N���A
	memset(&m_aStrDebug[0], NULL, sizeof(m_aStrDebug));

	//�����\���ݒ�
//#if _DEBUG
//	m_bDispDebug = true;
//#else NDEBUG
//	g_bDispDebug = false;
//#endif

	return S_OK;
}

//============================
//�f�o�b�O�v���b�N�̏I������
//============================
void CDebugProc::Uninit()
{
	//�f�o�b�O�\���p�t�H���g�̔p��
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
}

//============================
//�f�o�b�O�v���b�N�̍X�V����
//============================
void CDebugProc::Update()
{
	//��������ݒ�
	SetManual();

	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_F1))
	{//F1�L�[�������ꂽ�Ƃ�
		m_bDispDebug = m_bDispDebug ? false : true;
	}
}

//============================
//�f�o�b�O�v���b�N�̕`�揈��
//============================
void CDebugProc::Draw()
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	if (m_bDispDebug == true)
	{//�f�o�b�N���[�h���I���̎�
	 //�e�L�X�g�̕`��
		m_pFont->DrawText(NULL, &m_aStrDebug[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	}

	//�f�o�b�O�\�����̃N���A
	//memset(&m_aStrDebug[0], NULL, sizeof(m_aStrDebug));
	m_aStrDebug.clear();
}

//==========================================================
//�f�o�b�O�\���̐ݒ菈��
//==========================================================
void CDebugProc::Print(const char *fmt, ...)
{
	// ���[�J���ϐ��錾
	va_list args;
	va_start(args, fmt);

	// �o�͗p�o�b�t�@���m��
	char buffer[1024];
	vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);

	// �f�o�b�O������ɒǉ�
	m_aStrDebug += buffer;
}

//==========================================================
//�f�o�b�O�\���̐ݒ菈��
//==========================================================
const TCHAR* CDebugProc::String(const TCHAR* format, ...)
{
	static TCHAR strBuffer_g[1024];
	va_list args;
	va_start(args, format);

#if _DEBUG
	int len = _vsctprintf(format, args);
	if (len >= static_cast<int>(std::size(strBuffer_g))) {
		_ASSERT(0); // �T�C�Y�I�[�o�[�`�F�b�N
	}
#endif

	_vstprintf(strBuffer_g, format, args);
	va_end(args);

	return strBuffer_g;
}

//==========================================================
//�\������e�L�X�g�ݒ�
//==========================================================
void CDebugProc::SetManual(void)
{
	
}