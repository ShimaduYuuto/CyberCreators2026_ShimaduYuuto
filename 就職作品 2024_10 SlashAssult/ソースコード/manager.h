//================================
//
//manager.cpp�ɕK�v�Ȑ錾[manager.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _MANAGER_H_ //���̃}�N����`������Ă��Ȃ�������
#define _MANAGER_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "xfile.h"
#include "fade.h"
#include "scene.h"
#include "time.h"
#include "debugproc.h"

//�}�l�[�W���[�N���X
class CManager
{

private:

	//�����o�֐�
	CManager();								//�R���X�g���N�^

public:

	//�����o�֐�
	~CManager();							//�f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);		//������
	void Uninit();							//�I������
	void Update();							//�X�V����
	void Draw();							//�`�揈��

	//�C���X�^���X�̐���
	static CManager* GetInstance()
	{
		static CManager instance;	//�ÓI�C���X�^���X
		return &instance;
	}

	CRenderer* GetRenderer();		//�����_���[�̎擾
	CSound* GetSound();				//�V�[���̎擾
	CInputKeyboard* GetKeyboard();	//�L�[�{�[�h�̎擾
	CInputJoypad* GetJoypad();		//�W���C�p�b�h�̎擾
	CInputMouse* GetMouse();		//�}�E�X�̎擾
	CCamera* GetCamera();			//�J�����̎擾
	void ChangeCamera(CCamera* camera);	//�J�����̐؂�ւ�
	CLight* GetLight();				//���C�g�̏��
	CTexture* GetTexture();			//�e�N�X�`���̏��
	CXfile* GetXfile();				//X�t�@�C���̎擾
	CFade* GetFade();				//�t�F�[�h�̎擾
	CScene* GetScene();				//�V�[���̎擾
	void SetScene(CScene::MODE mode);//�V�[���̐ݒ�

	template<typename T>
	constexpr T GetRundom(T min, T max)
	{
		// �����Z���k�E�c�C�X�^�[�@�ɂ��[��������������A
		// �n�[�h�E�F�A�������V�[�h�ɂ��ď�����
		std::random_device seed_gen;
		std::mt19937 engine(seed_gen());

		std::uniform_real_distribution<float> Rundom(min, max);
		T Value = Rundom(engine);

		return Value;
	}

	//FPS�̐ݒ�Ǝ擾
	void SetFPS(int fps);			//�ݒ�

private:

	//�����o�ϐ�
	CRenderer* m_pRenderer;				//�����_���[
	CInputKeyboard* m_pKeyboard;		//�L�[�{�[�h
	CInputJoypad* m_pJoypad;			//�W���C�p�b�h
	CInputMouse* m_pMouse;				//�}�E�X
	CSound* m_pSound;					//�T�E���h
	CCamera* m_pCamera;					//�J����
	CLight* m_pLight;					//���C�g
	CTexture* m_pTexture;				//�e�N�X�`��
	CXfile* m_pXfile;					//X�t�@�C��
	CFade* m_pFade;						//�t�F�[�h
	CScene* m_pScene;					//�V�[��
};

#endif