//================================
//
//precompile.cpp�ɕK�v�Ȑ錾[precompile.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _PRECOMPILE_H_ //���̃}�N����`������Ă��Ȃ�������
#define _PRECOMPILE_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

#include <windows.h>
#include"d3dx9.h"	//�`�揈���ɕK�v
#define DIRECTINPUT_VERSION (0x0800) //�r���h���̌x���Ώ��p�}�N��
#include "dinput.h" //���͏����ɕK�v
#include "Xinput.h" //�W���C�p�b�h�����ɕK�v
#include "xaudio2.h" //�T�E���h�����ɕK�v

//���C�u�����̃����N
#pragma comment(lib, "d3d9.lib")	//�`�揈���ɕK�v
#pragma comment(lib, "d3dx9.lib")	//[d3d9.lib]�̊g�����C�u����
#pragma comment(lib, "dxguid.lib")	//DirectX�R���|�[�l���g�i���i�j�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")	//�V�X�e�������擾�ɕK�v
#pragma comment(lib, "dinput8.lib")//���͏����ɕK�v
#pragma comment(lib, "xinput.lib") //�W���C�p�b�h�����ɕK�v

//C++�p�֐��̃C���N���[�h
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <list>
#include <random>
#include <fstream>

//�V�X�e���n�̃C���N���[�h
#include <assert.h>

#endif