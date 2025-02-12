//======================================
//
//	�A�j���[�V��������[animation.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "animation.h"

//============================
//�R���X�g���N�^
//============================
CAnimation::CAnimation() :
	m_TextureInfo(),
	m_TextureCount(),
	m_bEnd(false)
{

}

//============================
//�f�X�g���N�^
//============================
CAnimation::~CAnimation()
{

}

//============================
//�A�j���[�V�����̍X�V
//============================
D3DXVECTOR2 CAnimation::UpdateAnim()
{
	//�Ԃ��p�̕ϐ�
	D3DXVECTOR2 UV = { 0.0f, 0.0f };

	UpdateCnt();

	//�v�Z�p�̕ϐ�
	float fHorizontal = 1.0f / m_TextureInfo.nHorizontal;	//������
	float fVertical = 1.0f / m_TextureInfo.nVertical;		//�c����
	UV = D3DXVECTOR2(fHorizontal, fVertical);				//UV���W���Z�o

	return UV;
}

//============================
//�J�E���g�̍X�V
//============================
void CAnimation::UpdateCnt()
{
	//�t���[���̍X�V
	m_TextureCount.nFrameCount++;

	//�J�E���g���X�V����l�܂Ői�񂾂�
	if (m_TextureCount.nFrameCount < m_TextureInfo.nUpdateSpeed)
	{
		return;
	}

	//�J�E���g�̍X�V
	m_TextureCount.nFrameCount = 0;			//�t���[���J�E���g�̏�����
	m_TextureCount.nHorizontalAnimCount++;	//�A�j���[�V�����J�E���g�̃J�E���g�A�b�v

	//���̃A�j���J�E���g���ő�܂Ői�񂾂�
	if (m_TextureCount.nHorizontalAnimCount < m_TextureInfo.nHorizontal)
	{
		return;
	}

	//�J�E���g�̍X�V
	m_TextureCount.nHorizontalAnimCount = 0;	//���̃J�E���g��������
	m_TextureCount.nVerticalAnimCount++;		//�c�̃J�E���g�A�b�v

	//�c�̃J�E���g���ő�܂Ői�񂾂�
	if (m_TextureCount.nVerticalAnimCount < m_TextureInfo.nVertical)
	{
		return;
	}

	//���[�v�������Ȃ�
	if (!m_TextureInfo.bLoop)
	{
		//�I������
		m_bEnd = true;
	}
}
