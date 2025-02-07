//======================================
//
//	�N���A�^�C���̕`��[cleartime.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "cleartime.h"
#include "manager.h"
#include "game.h"
#include "dot.h"

//============================
//�N���A�^�C���̃R���X�g���N�^
//============================
CClearTime::CClearTime() : m_fTime(0.0f), m_Pos()
{
	//�i���o�[�̏�����
	for (int i = 0; i < TIME_NUM; i++)
	{
		m_pNumber[i] = nullptr;
	}
}

//============================
//�N���A�^�C���̃f�X�g���N�^
//============================
CClearTime::~CClearTime()
{

}

//============================
//�N���A�^�C���̏�����
//============================
HRESULT CClearTime::Init()
{
	//�\�����錅�������i���o�[���N���G�C�g
	for (int i = 0; i < TIME_NUM; i++)
	{
		//�����œn���p�̕ϐ�(�ʒu)
		D3DXVECTOR3 Pos = m_Pos;

		//���ɉ����ĉ��̈ʒu��ύX
		Pos.x += i * NUM_SPACE;

		//�����̃N���G�C�g
		m_pNumber[i] = CNumber::Create(Pos, 0);

		/*if (i == 2)
		{
			CDot::Create(D3DXVECTOR3(Pos.x + NUM_SPACE * 0.5f, Pos.y + 30.0f, 0.0f), { 15.0f, 15.0f, 0.0f });
		}*/
	}

	SetTime();

	return S_OK;
}

//============================
//�N���A�^�C���̏I������
//============================
void CClearTime::Uninit()
{
	
}

//============================
//�N���A�^�C���̉��Z����
//============================
void CClearTime::AddTime(float value)
{
	//�N���A�^�C���̉��Z
	m_fTime += value;

	//�N���A�^�C���̐ݒ�
	SetTime();
}

//============================
//�N���A�^�C���̐ݒ�
//============================
void CClearTime::SetTime()
{
	//�v�Z�p�̕ϐ�
	int aPosTex[TIME_NUM]; //�e���̐������i�[
	int nClearTime = m_fTime * 1000.0f;

	for (int nCount = TIME_NUM; nCount > 0; nCount--)
	{
		aPosTex[nCount - 1] = nClearTime % 10;
		nClearTime /= 10;
	}

	//�e�N�X�`���̍��W�̐ݒ�
	for (int nCntClearTime = 0; nCntClearTime < TIME_NUM; nCntClearTime++)
	{
		m_pNumber[nCntClearTime]->SetTexture(aPosTex[nCntClearTime]);
	}

}

//============================
//�N���A�^�C���̃��Z�b�g
//============================
void CClearTime::ResetTime()
{
	//�N���A�^�C���̃��Z�b�g
	m_fTime = 0.0f;
}