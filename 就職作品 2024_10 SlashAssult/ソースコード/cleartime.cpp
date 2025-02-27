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
#include "colon.h"

//============================
//�N���A�^�C���̃R���X�g���N�^
//============================
CClearTime::CClearTime() : 
	m_fTime(0.0f),	//���݂̎���
	m_Pos()			//�ʒu
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
		//�����œn���p�̕ϐ�
		D3DXVECTOR3 Pos = m_Pos;	//�ʒu

		//���ɉ����ĉ��̈ʒu��ύX
		Pos.x += i * NUM_SPACE;

		//�����Ɛ����Ō��Ԃ�ύX
		if (i >= NUM_FEW)
		{
			Pos.x += FEW_SPACE * 0.5f;
		}
		else
		{
			Pos.x -= FEW_SPACE * 0.5f;
		}

		//�����̃N���G�C�g
		m_pNumber[i] = CNumber::Create(Pos, 0);

		//�R�����̐���
		if (i == NUM_FEW - 1)
		{
			CColon::Create(D3DXVECTOR3(Pos.x + (NUM_SPACE + FEW_SPACE) * 0.5f, Pos.y, 0.0f), { 70.0f, 70.0f, 0.0f });
		}
	}

	//���Ԃ̐ݒ�
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
	int aPosTex[TIME_NUM];				//�e���̐������i�[
	float fClearTime = m_fTime;			//�N���A�^�C��
	int nClearTime = 0;					//�����ɒu���������N���A�^�C��

	//�����_���̌������������������𑝂₷
	for (int i = 0; i < NUM_FEW; i++)
	{
		fClearTime *= 10.0f;
	}

	//�����̌��̕��������炵���l����
	nClearTime = static_cast<int>(fClearTime);

	//�����Ƃɐ��l����
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